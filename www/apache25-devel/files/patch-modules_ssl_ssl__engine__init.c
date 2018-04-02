--- modules/ssl/ssl_engine_init.c.orig	2018-03-30 15:43:58 UTC
+++ modules/ssl/ssl_engine_init.c
@@ -542,7 +542,8 @@ static apr_status_t ssl_init_ctx_tls_ext
 }
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20800000L)
 /*
  * Enable/disable SSLProtocol. If the mod_ssl enables protocol
  * which is disabled by default by OpenSSL, show a warning.
@@ -660,7 +661,8 @@ static apr_status_t ssl_init_ctx_protoco
 
     SSL_CTX_set_options(ctx, SSL_OP_ALL);
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L  || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20800000L)
     /* always disable SSLv2, as per RFC 6176 */
     SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
 
