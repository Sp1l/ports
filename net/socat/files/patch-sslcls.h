--- sslcls.h.orig	2015-01-24 10:15:22 UTC
+++ sslcls.h
@@ -47,7 +47,6 @@ X509 *sycSSL_get_peer_certificate(SSL *s
 int sycSSL_shutdown(SSL *ssl);
 void sycSSL_CTX_free(SSL_CTX *ctx);
 void sycSSL_free(SSL *ssl);
-int sycRAND_egd(const char *path);
 
 DH *sycPEM_read_bio_DHparams(BIO *bp, DH **x, pem_password_cb *cb, void *u);
 
@@ -55,7 +54,7 @@ BIO *sycBIO_new_file(const char *filenam
 
 int sycFIPS_mode_set(int onoff);
 
-#if OPENSSL_VERSION_NUMBER >= 0x00908000L
+#if OPENSSL_VERSION_NUMBER >= 0x00908000L && !defined(OPENSSL_NO_COMP)
 const COMP_METHOD *sycSSL_get_current_compression(SSL *ssl);
 const COMP_METHOD *sycSSL_get_current_expansion(SSL *ssl);
 const char *sycSSL_COMP_get_name(const COMP_METHOD *comp);
@@ -98,7 +97,6 @@ const char *sycSSL_COMP_get_name(const C
 #define sycSSL_shutdown(s) SSL_shutdown(s)
 #define sycSSL_CTX_free(c) SSL_CTX_free(c)
 #define sycSSL_free(s) SSL_free(s)
-#define sycRAND_egd(p) RAND_egd(p)
 
 #define sycPEM_read_bio_DHparams(b,x,p,u) PEM_read_bio_DHparams(b,x,p,u)
 
