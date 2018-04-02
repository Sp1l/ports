--- modules/ssl/ssl_private.h.orig	2018-03-30 15:43:58 UTC
+++ modules/ssl/ssl_private.h
@@ -132,13 +132,14 @@
         SSL_CTX_ctrl(ctx, SSL_CTRL_SET_MIN_PROTO_VERSION, version, NULL)
 #define SSL_CTX_set_max_proto_version(ctx, version) \
         SSL_CTX_ctrl(ctx, SSL_CTRL_SET_MAX_PROTO_VERSION, version, NULL)
-#endif
-/* LibreSSL declares OPENSSL_VERSION_NUMBER == 2.0 but does not include most
- * changes from OpenSSL >= 1.1 (new functions, macros, deprecations, ...), so
- * we have to work around this...
+#elif LIBRESSL_VERSION_NUMBER < 0x2070000f
+/* LibreSSL before 2.7 declares OPENSSL_VERSION_NUMBER == 2.0 but does not
+ * include most changes from OpenSSL >= 1.1 (new functions, macros, 
+ * deprecations, ...), so we have to work around this...
  */
 #define MODSSL_USE_OPENSSL_PRE_1_1_API (1)
-#else
+#endif /* LIBRESSL_VERSION_NUMBER < 0x2060000f */
+#else /* defined(LIBRESSL_VERSION_NUMBER) */
 #define MODSSL_USE_OPENSSL_PRE_1_1_API (OPENSSL_VERSION_NUMBER < 0x10100000L)
 #endif
 
@@ -238,7 +239,8 @@ void init_bio_methods(void);
 void free_bio_methods(void);
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10002000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10002000L || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x2070000f)
 #define X509_STORE_CTX_get0_store(x) (x->ctx)
 #endif
 
