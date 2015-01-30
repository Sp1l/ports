--- xioopts.c.orig	2015-01-24 10:15:22 UTC
+++ xioopts.c
@@ -412,7 +412,6 @@ const struct optname optionnames[] = {
 #ifdef ECHOPRT
 	IF_TERMIOS("echoprt",	&opt_echoprt)
 #endif
-	IF_OPENSSL("egd",	&opt_openssl_egd)
 	IF_ANY    ("end-close",	&opt_end_close)
 	IF_TERMIOS("eof",	&opt_veof)
 	IF_TERMIOS("eol",	&opt_veol)
@@ -1102,7 +1101,6 @@ const struct optname optionnames[] = {
 	IF_OPENSSL("openssl-compress",	&opt_openssl_compress)
 #endif
 	IF_OPENSSL("openssl-dhparam",	&opt_openssl_dhparam)
-	IF_OPENSSL("openssl-egd",	&opt_openssl_egd)
 #if WITH_FIPS
 	IF_OPENSSL("openssl-fips",	&opt_openssl_fips)
 #endif
