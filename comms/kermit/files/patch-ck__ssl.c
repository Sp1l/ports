--- ck_ssl.c.orig	2015-02-05 21:11:08 UTC
+++ ck_ssl.c
@@ -1054,11 +1054,15 @@ ssl_display_comp(SSL * ssl)
     if (ssl == NULL)
         return;
 
+#ifndef OPENSSL_NO_COMP
     if (ssl->expand == NULL || ssl->expand->meth == NULL)
+#endif
         printf("Compression: None\r\n");
+#ifndef OPENSSL_NO_COMP
     else {
         printf("Compression: %s\r\n",ssl->expand->meth->name);
     }
+#endif
 }
 
 int
@@ -1508,12 +1512,14 @@ the build.\r\n\r\n");
         }
         debug(F110,"ssl_rnd_file",ssl_rnd_file,0);
 
+#ifndef OPENSSL_NO_EGD
         rc1 = RAND_egd(ssl_rnd_file);
         debug(F111,"ssl_once_init","RAND_egd()",rc1);
         if ( rc1 <= 0 ) {
             rc2 = RAND_load_file(ssl_rnd_file, -1);
             debug(F111,"ssl_once_init","RAND_load_file()",rc1);
         }
+#endif
 
         if ( rc1 <= 0 && !rc2 )
         {
@@ -1604,7 +1610,9 @@ ssl_tn_init(mode) int mode;
             /* This can fail because we do not have RSA available */
             if ( !ssl_ctx ) {
                 debug(F110,"ssl_tn_init","SSLv23_client_method failed",0);
+#ifndef OPENSSL_NO_SSL3
                 ssl_ctx=(SSL_CTX *)SSL_CTX_new(SSLv3_client_method());
+#endif
             }
             if ( !ssl_ctx ) {
                 debug(F110,"ssl_tn_init","SSLv3_client_method failed",0);
@@ -1630,7 +1638,9 @@ ssl_tn_init(mode) int mode;
                     debug(F110,"ssl_tn_init","SSLv23_client_method OK",0);
                 } else {
                     debug(F110,"ssl_tn_init","SSLv23_client_method failed",0);
+#ifndef OPENSSL_NO_SSL3
                     tls_ctx=(SSL_CTX *)SSL_CTX_new(SSLv3_client_method());
+#endif
                     if ( !tls_ctx ) {
                         debug(F110,
                               "ssl_tn_init","TLSv1_client_method failed",0);
@@ -1651,7 +1661,9 @@ ssl_tn_init(mode) int mode;
             /* This can fail because we do not have RSA available */
             if ( !ssl_ctx ) {
                 debug(F110,"ssl_tn_init","SSLv23_server_method failed",0);
+#ifndef OPENSSL_NO_SSL3
                 ssl_ctx=(SSL_CTX *)SSL_CTX_new(SSLv3_server_method());
+#endif
             }
             if ( !ssl_ctx ) {
                 debug(F110,"ssl_tn_init","SSLv3_server_method failed",0);
