--- ckupty.h.orig	2010-02-10 21:43:13.000000000 +0100
+++ ckupty.h	2015-12-23 21:18:05.471654259 +0100
@@ -40,6 +40,7 @@
 #ifndef SUNOS41
 #include <sys/ioctl.h>
 #endif	/* SUNOS41 */
+typedef unsigned int u_int;
 #include <sys/file.h>
 #include <sys/time.h>
 #include <ctype.h>
