--- src/cryptography/hazmat/bindings/openssl/ssl.py.orig	2015-04-21 08:58:58 UTC
+++ src/cryptography/hazmat/bindings/openssl/ssl.py
@@ -526,7 +526,7 @@ static const long Cryptography_HAS_NEXTP
 #endif
 
 /* ALPN was added in OpenSSL 1.0.2. */
-#if OPENSSL_VERSION_NUMBER < 0x10002001L
+#if OPENSSL_VERSION_NUMBER < 0x10002001L && !defined(LIBRESSL_VERSION_NUMBER)
 int (*SSL_CTX_set_alpn_protos)(SSL_CTX *,
                                const unsigned char *,
                                unsigned) = NULL;
