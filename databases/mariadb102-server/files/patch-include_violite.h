--- include/violite.h.orig	2017-02-16 08:28:05 UTC
+++ include/violite.h
@@ -146,14 +146,15 @@ typedef my_socket YASSL_SOCKET_T;
 #include <openssl/ssl.h>
 #include <openssl/err.h>
 
-#ifdef HAVE_ERR_remove_thread_state
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
+#define ERR_remove_state(X)
+#elif defined(HAVE_ERR_remove_thread_state)
 #define ERR_remove_state(X) ERR_remove_thread_state(NULL)
 #endif
-
 enum enum_ssl_init_error
 {
-  SSL_INITERR_NOERROR= 0, SSL_INITERR_CERT, SSL_INITERR_KEY, 
-  SSL_INITERR_NOMATCH, SSL_INITERR_BAD_PATHS, SSL_INITERR_CIPHERS, 
+  SSL_INITERR_NOERROR= 0, SSL_INITERR_CERT, SSL_INITERR_KEY,
+  SSL_INITERR_NOMATCH, SSL_INITERR_BAD_PATHS, SSL_INITERR_CIPHERS,
   SSL_INITERR_MEMFAIL, SSL_INITERR_DH, SSL_INITERR_LASTERR
 };
 const char* sslGetErrString(enum enum_ssl_init_error err);
