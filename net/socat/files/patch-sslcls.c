--- sslcls.c.orig	2015-01-24 10:15:22 UTC
+++ sslcls.c
@@ -331,14 +331,6 @@ void sycSSL_free(SSL *ssl) {
    return;
 }
 
-int sycRAND_egd(const char *path) {
-   int result;
-   Debug1("RAND_egd(\"%s\")", path);
-   result = RAND_egd(path);
-   Debug1("RAND_egd() -> %d", result);
-   return result;
-}
-
 DH *sycPEM_read_bio_DHparams(BIO *bp, DH **x, pem_password_cb *cb, void *u) {
    DH *result;
    Debug4("PEM_read_bio_DHparams(%p, %p, %p, %p)",
@@ -375,7 +367,7 @@ int sycFIPS_mode_set(int onoff) {
 }
 #endif /* WITH_FIPS */
 
-#if OPENSSL_VERSION_NUMBER >= 0x00908000L
+#if OPENSSL_VERSION_NUMBER >= 0x00908000L && !defined(OPENSSL_NO_COMP)
 const COMP_METHOD *sycSSL_get_current_compression(SSL *ssl) {
    const COMP_METHOD *result;
    Debug1("SSL_get_current_compression(%p)", ssl);
