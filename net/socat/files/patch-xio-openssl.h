--- xio-openssl.h.orig	2015-01-24 10:15:22 UTC
+++ xio-openssl.h
@@ -21,7 +21,6 @@ extern const struct optdesc opt_openssl_
 extern const struct optdesc opt_openssl_dhparam;
 extern const struct optdesc opt_openssl_cafile;
 extern const struct optdesc opt_openssl_capath;
-extern const struct optdesc opt_openssl_egd;
 extern const struct optdesc opt_openssl_pseudo;
 #if OPENSSL_VERSION_NUMBER >= 0x00908000L
 extern const struct optdesc opt_openssl_compress;
