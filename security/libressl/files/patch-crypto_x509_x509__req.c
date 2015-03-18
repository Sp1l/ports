# Backport of CVE-2015-0288 vuln mitigation
# Check public key is not NULL.
#
# CVE-2015-0288
# PR#3708

--- crypto/x509/x509_req.c.orig	2014-12-06 23:15:50 UTC
+++ crypto/x509/x509_req.c
@@ -95,6 +95,8 @@ X509_to_X509_REQ(X509 *x, EVP_PKEY *pkey
 		goto err;
 
 	pktmp = X509_get_pubkey(x);
+	if (pktmp == NULL)
+		goto err;
 	i = X509_REQ_set_pubkey(ret, pktmp);
 	EVP_PKEY_free(pktmp);
 	if (!i)
