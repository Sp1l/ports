--- get.c.orig	2000-06-21 21:15:41.000000000 +0200
+++ get.c	2015-03-07 23:55:19.316239812 +0100
@@ -176,20 +176,26 @@ get(char *loc, NETPORT port, char *url, 
 			}
 			D_PRINTF( "SSL version = SSLv23\n" );
 		}
-		else if(ssl_version != NULL && strcasecmp(ssl_version, "SSLv2") == 0) {
+		else
+#ifdef OPENSSL_NO_SSL2
+		if(ssl_version != NULL && strcasecmp(ssl_version, "SSLv2") == 0) {
 			if((ctx = SSL_CTX_new(SSLv2_client_method())) == NULL) {
 				ERR_print_errors_fp(stderr);
 				goto error;
 			}
 			D_PRINTF( "SSL version = SSLv2\n" );
 		}
-		else {
+		else
+#endif
+#ifndef OPENSSL_NO_SSL3
+		{
 			if((ctx = SSL_CTX_new(SSLv3_client_method())) == NULL) {
 				ERR_print_errors_fp(stderr);
 				goto error;
 			}
 			D_PRINTF( "SSL version = SSLv3\n" );
 		}
+#endif
 		
 		/* set preferred cipher */
 		if(ssl_cipher != NULL && strlen(ssl_cipher) > 0) {
