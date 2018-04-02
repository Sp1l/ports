--- modules/md/md_crypt.c.orig	2018-03-30 15:43:58 UTC
+++ modules/md/md_crypt.c
@@ -471,7 +471,7 @@ apr_status_t md_pkey_gen(md_pkey_t **ppk
     }
 }
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x2070000f)
 
 #ifndef NID_tlsfeature
 #define NID_tlsfeature          1020
