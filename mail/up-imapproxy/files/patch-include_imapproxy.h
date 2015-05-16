--- include/imapproxy.h.orig	2010-07-26 07:21:19 UTC
+++ include/imapproxy.h
@@ -161,6 +161,7 @@
 
 #if HAVE_LIBSSL
 #include <openssl/ssl.h>
+#include <openssl/md5.h>
 #include <openssl/rand.h>
 #include <limits.h>
 #endif
