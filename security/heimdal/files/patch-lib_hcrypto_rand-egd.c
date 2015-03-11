--- lib/hcrypto/rand-egd.c.orig	2012-12-09 23:06:44.000000000 +0100
+++ lib/hcrypto/rand-egd.c	2015-03-11 18:59:17.067934065 +0100
@@ -33,6 +33,8 @@
 
 #include <config.h>
 
+#ifdef HAVE_RAND_EGD
+
 #include <sys/types.h>
 #ifdef HAVE_SYS_UN_H
 #include <sys/un.h>
@@ -258,3 +260,5 @@
 
     return 1;
 }
+
+#endif
