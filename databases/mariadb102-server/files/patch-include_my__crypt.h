--- include/my_crypt.h.orig	2017-02-16 08:28:05 UTC
+++ include/my_crypt.h
@@ -24,6 +24,21 @@
 extern "C" {
 #endif
 
+/* OpenSSL version specific definitions */
+#if !defined(HAVE_YASSL) && defined(OPENSSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
+#define ERR_remove_state(X)
+#else
+#define EVP_CIPHER_CTX_reset(X) EVP_CIPHER_CTX_cleanup(X)
+#define RAND_OpenSSL() RAND_SSLeay();
+#if defined(HAVE_ERR_remove_thread_state)
+#define ERR_remove_state(X) ERR_remove_thread_state(NULL)
+#endif
+#endif
+#elif defined(HAVE_YASSL)
+#define EVP_CIPHER_CTX_reset(X) EVP_CIPHER_CTX_cleanup(X)
+#endif /* !defined(HAVE_YASSL) */
+
 /* return values from my_aes_encrypt/my_aes_decrypt functions */
 #define MY_AES_OK               0
 #define MY_AES_BAD_DATA         -100
