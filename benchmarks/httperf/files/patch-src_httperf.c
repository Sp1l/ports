--- src/httperf.c.orig	2007-04-07 07:01:56 UTC
+++ src/httperf.c
@@ -78,6 +78,10 @@
 #include <conn.h>
 #include <timer.h>
 
+#ifdef __FreeBSD__
+#include <machine/floatingpoint.h>
+#endif
+
 #ifdef HAVE_SSL
 #  include <openssl/rand.h>
 #endif
@@ -808,7 +812,12 @@ main (int argc, char **argv)
       SSLeay_add_ssl_algorithms ();
 
       /* for some strange reason, SSLv23_client_method () doesn't work here */
+#ifndef OPENSSL_NO_SSL3
       ssl_ctx = SSL_CTX_new (SSLv3_client_method ());
+#else
+      ssl_ctx = SSL_CTX_new (SSLv23_client_method ());
+      SSL_CTX_set_options (ssl_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 );
+#endif
       if (!ssl_ctx)
 	{
 	  ERR_print_errors_fp (stderr);
