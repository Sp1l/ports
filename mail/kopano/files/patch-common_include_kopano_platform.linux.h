--- common/include/kopano/platform.linux.h.orig	2017-02-06 15:39:23 UTC
+++ common/include/kopano/platform.linux.h
@@ -25,6 +25,10 @@
 #include <kopano/zcdefs.h>
 #include <vector>
 #include <cstdio>
+#ifdef __FreeBSD__
+#include <stdio.h>
+#include <xlocale.h>
+#endif
 #include <cstdlib>
 
 #include <pthread.h>
@@ -33,8 +37,19 @@
 #include <dlfcn.h>
 #include <cstddef>
 #include <libgen.h>
+#if defined(__OpenBSD__) || defined(__FreeBSD__)
+#include <sys/param.h>
+#ifndef MAX_PATH
+  #define MAX_PATH PATH_MAX
+#endif
+#include <sys/endian.h>
+#else
 #include <byteswap.h>
 #include <endian.h>
+#endif
+#ifdef __FreeBSD__
+#define __bswap_64 __bswap64
+#endif
 #include <cerrno>
 #include <clocale>
 
@@ -56,8 +71,10 @@
 
 #include <cassert>
 #define _vsnprintf vsnprintf
-#ifdef HAVE_VSNPRINTF_L
+#if defined(HAVE_VSNPRINTF_L) && !defined(__FreeBSD__)
 #define _vsnprintf_l vsnprintf_l
+#elif defined(__OpenBSD__) || defined(__FreeBSD__)
+#define _vsnprintf_l vsnprintf
 #else
 inline int _vsnprintf_l(char *str, size_t size, const char *format, locale_t locale, va_list ap) {
 	locale_t prev = uselocale(locale);
@@ -596,7 +613,7 @@ extern _kc_export time_t GetProcessTime(
 #endif
 
 #define OutputDebugStringA(dstr) fprintf(stderr,"%s",dstr)
-#define GetCurrentThreadId() (int)pthread_self()
+#define GetCurrentThreadId() (unsigned long)pthread_self()
 #define GetTickCount() 0L
 
 #define TICKS_PER_SEC (sysconf(_SC_CLK_TCK))
