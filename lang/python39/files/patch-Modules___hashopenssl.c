Index: Modules/_hashopenssl.c
--- Modules/_hashopenssl.c.orig
+++ Modules/_hashopenssl.c
@@ -43,7 +43,8 @@
 #  error "OPENSSL_THREADS is not defined, Python requires thread-safe OpenSSL"
 #endif
 
-#if (OPENSSL_VERSION_NUMBER < 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
+#if (OPENSSL_VERSION_NUMBER < 0x10100000L) || \
+    (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x2070000fL)
 /* OpenSSL < 1.1.0 */
 #define EVP_MD_CTX_new EVP_MD_CTX_create
 #define EVP_MD_CTX_free EVP_MD_CTX_destroy
