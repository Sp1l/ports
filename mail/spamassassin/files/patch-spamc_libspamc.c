--- spamc/libspamc.c.orig	2015-04-28 19:56:59 UTC
+++ spamc/libspamc.c
@@ -1216,7 +1216,7 @@ int message_filter(struct transport *tp,
 	if (flags & SPAMC_TLSV1) {
 	    meth = TLSv1_client_method();
 	} else {
-	    meth = SSLv3_client_method(); /* default */
+	    meth = SSLv23_client_method(); /* default */
 	}
 	SSL_load_error_strings();
 	ctx = SSL_CTX_new(meth);
@@ -1604,7 +1604,7 @@ int message_tell(struct transport *tp, c
     if (flags & SPAMC_USE_SSL) {
 #ifdef SPAMC_SSL
 	SSLeay_add_ssl_algorithms();
-	meth = SSLv3_client_method();
+	meth = SSLv23_client_method();
 	SSL_load_error_strings();
 	ctx = SSL_CTX_new(meth);
 #else
