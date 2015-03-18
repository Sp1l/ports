# Backport of CVE-2015-0209 vuln mitigation
# Fix a failure to NULL a pointer freed on error.
#
# Inspired by BoringSSL commit 517073cd4b by Eric Roman <eroman@chromium.org>
# CVE-2015-0209

--- crypto/ec/ec_asn1.c.orig	2015-02-10 14:54:46 UTC
+++ crypto/ec/ec_asn1.c
@@ -1043,13 +1043,8 @@ d2i_ECPrivateKey(EC_KEY ** a, const unsi
 	EC_KEY *ret = NULL;
 	EC_PRIVATEKEY *priv_key = NULL;
 
-	if ((priv_key = EC_PRIVATEKEY_new()) == NULL) {
-		ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_MALLOC_FAILURE);
-		return NULL;
-	}
-	if ((priv_key = d2i_EC_PRIVATEKEY(&priv_key, in, len)) == NULL) {
+	if ((priv_key = d2i_EC_PRIVATEKEY(NULL, in, len)) == NULL) {
 		ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_EC_LIB);
-		EC_PRIVATEKEY_free(priv_key);
 		return NULL;
 	}
 	if (a == NULL || *a == NULL) {
@@ -1058,8 +1053,6 @@ d2i_ECPrivateKey(EC_KEY ** a, const unsi
 			    ERR_R_MALLOC_FAILURE);
 			goto err;
 		}
-		if (a)
-			*a = ret;
 	} else
 		ret = *a;
 
@@ -1109,10 +1102,12 @@ d2i_ECPrivateKey(EC_KEY ** a, const unsi
 			goto err;
 		}
 	}
+	if (a)
+		*a = ret;
 	ok = 1;
 err:
 	if (!ok) {
-		if (ret)
+		if (ret && (a == NULL || *a != ret))
 			EC_KEY_free(ret);
 		ret = NULL;
 	}
