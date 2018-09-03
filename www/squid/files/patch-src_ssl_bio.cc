Fix build with LibreSSL

--- src/ssl/bio.cc.orig	2018-07-02 03:26:07 UTC
+++ src/ssl/bio.cc
@@ -76,7 +76,11 @@ Ssl::Bio::Create(const int fd, Security:
         BIO_meth_set_create(SquidMethods, squid_bio_create);
         BIO_meth_set_destroy(SquidMethods, squid_bio_destroy);
     }
+#ifdef LIBRESSL_VERSION_NUMBER
+    BIO_METHOD *useMethod = SquidMethods;
+#else
     const BIO_METHOD *useMethod = SquidMethods;
+#endif
 #else
     BIO_METHOD *useMethod = &SquidMethods;
 #endif
