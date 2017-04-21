--- src/libstrongswan/plugins/openssl/openssl_rsa_public_key.h.orig	2016-04-22 20:01:35 UTC
+++ src/libstrongswan/plugins/openssl/openssl_rsa_public_key.h
@@ -21,6 +21,101 @@
 #ifndef OPENSSL_RSA_PUBLIC_KEY_H_
 #define OPENSSL_RSA_PUBLIC_KEY_H_
 
+#if OPENSSL_VERSION_NUMBER < 0x10100000L
+/**
+ * OpenSSL compat functions
+ * From https://wiki.openssl.org/index.php/OpenSSL_1.1.0_Changes
+*/
+
+#include <string.h>
+#include <openssl/engine.h>
+
+int RSA_set0_key(RSA *r, BIGNUM *n, BIGNUM *e, BIGNUM *d)
+{
+   /* If the fields n and e in r are NULL, the corresponding input
+    * parameters MUST be non-NULL for n and e.  d may be
+    * left NULL (in case only the public key is used).
+    */
+   if ((r->n == NULL && n == NULL)
+       || (r->e == NULL && e == NULL))
+       return 0;
+
+   if (n != NULL) {
+       BN_free(r->n);
+       r->n = n;
+   }
+   if (e != NULL) {
+       BN_free(r->e);
+       r->e = e;
+   }
+   if (d != NULL) {
+       BN_free(r->d);
+       r->d = d;
+   }
+
+   return 1;
+}
+
+int RSA_set0_factors(RSA *r, BIGNUM *p, BIGNUM *q)
+{
+   /* If the fields p and q in r are NULL, the corresponding input
+    * parameters MUST be non-NULL.
+    */
+   if ((r->p == NULL && p == NULL)
+       || (r->q == NULL && q == NULL))
+       return 0;
+
+   if (p != NULL) {
+       BN_free(r->p);
+       r->p = p;
+   }
+   if (q != NULL) {
+       BN_free(r->q);
+       r->q = q;
+   }
+
+   return 1;
+}
+
+int RSA_set0_crt_params(RSA *r, BIGNUM *dmp1, BIGNUM *dmq1, BIGNUM *iqmp)
+{
+   /* If the fields dmp1, dmq1 and iqmp in r are NULL, the corresponding input
+    * parameters MUST be non-NULL.
+    */
+   if ((r->dmp1 == NULL && dmp1 == NULL)
+       || (r->dmq1 == NULL && dmq1 == NULL)
+       || (r->iqmp == NULL && iqmp == NULL))
+       return 0;
+
+   if (dmp1 != NULL) {
+       BN_free(r->dmp1);
+       r->dmp1 = dmp1;
+   }
+   if (dmq1 != NULL) {
+       BN_free(r->dmq1);
+       r->dmq1 = dmq1;
+   }
+   if (iqmp != NULL) {
+       BN_free(r->iqmp);
+       r->iqmp = iqmp;
+   }
+
+   return 1;
+}
+
+void RSA_get0_key(const RSA *r,
+                  const BIGNUM **n, const BIGNUM **e, const BIGNUM **d)
+{
+   if (n != NULL)
+       *n = r->n;
+   if (e != NULL)
+       *e = r->e;
+   if (d != NULL)
+       *d = r->d;
+}
+
+#endif
+
 typedef struct openssl_rsa_public_key_t openssl_rsa_public_key_t;
 
 #include <credentials/keys/public_key.h>
