--- include/ma_global.h.orig	2017-01-17 12:23:34 UTC
+++ include/ma_global.h
@@ -185,9 +185,6 @@ double my_ulonglong2double(unsigned long
 #ifdef HAVE_FCNTL_H
 #include <fcntl.h>
 #endif
-#ifdef HAVE_SYS_TIMEB_H
-#include <sys/timeb.h>				/* Avoid warnings on SCO */
-#endif
 #if TIME_WITH_SYS_TIME
 # include <sys/time.h>
 # include <time.h>
