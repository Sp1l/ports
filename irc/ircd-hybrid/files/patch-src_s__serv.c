--- src/s_serv.c.orig	2013-06-23 19:49:22.000000000 +0200
+++ src/s_serv.c	2015-03-10 20:12:43.301585509 +0100
@@ -25,6 +25,7 @@
 #include "stdinc.h"
 #ifdef HAVE_LIBCRYPTO
 #include <openssl/rsa.h>
+#include <openssl/comp.h>
 #include "rsa.h"
 #endif
 #include "list.h"
