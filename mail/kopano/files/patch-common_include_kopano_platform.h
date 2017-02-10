--- common/include/kopano/platform.h.orig	2017-02-10 20:22:53 UTC
+++ common/include/kopano/platform.h
@@ -119,7 +119,7 @@ bool operator <=(const FILETIME &, const
 extern _kc_export time_t operator -(const FILETIME &, const FILETIME &);
 
 /* convert struct tm to time_t in timezone UTC0 (GM time) */
-#ifndef __linux__
+#if !(__linux__) && !defined(__FreeBSD__)
 time_t timegm(struct tm *t);
 #endif
 
