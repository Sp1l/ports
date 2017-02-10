--- common/platform.linux.cpp.orig	2017-02-06 15:39:23 UTC
+++ common/platform.linux.cpp
@@ -36,6 +36,8 @@
 #include <cerrno>
 #include <climits>
 
+#include <signal.h>
+
 #include <string>
 #include <map>
 #include <vector>
@@ -45,7 +47,7 @@
 #else
 #	include <uuid.h>
 #endif
-#if defined(__linux__) && defined(__GLIBC__)
+#if defined(__linux__) && defined(__GLIBC__) || defined (__OpenBSD__) || defined (__FreeBSD__)
 #	include <cxxabi.h>
 #	include <execinfo.h>
 #endif
@@ -54,9 +56,9 @@
 #ifdef __APPLE__
 // bsd
 #define ICONV_CONST const
-#elif OPENBSD
+#elif defined(__OpenBSD__) || defined(__FreeBSD__)
 // bsd
-#define ICONV_CONST const
+#define ICONV_CONST
 #else
 // linux
 #define ICONV_CONST
@@ -79,22 +81,10 @@ HRESULT CoCreateGuid(LPGUID pNewGUID) {
 		return MAPI_E_INVALID_PARAMETER;
 
 #if HAVE_UUID_CREATE
-#ifdef OPENBSD
-	uuid_t *g = NULL;
-	void *vp = NULL;
-	size_t n = 0;
-	// error codes are not checked!
-	uuid_create(&g);
-	uuid_make(g, UUID_MAKE_V1);
-	uuid_export(g, UUID_FMT_BIN, &vp, &n);
-	memcpy(pNewGUID, &vp, UUID_LEN_BIN);
-	uuid_destroy(g);
-#else
 	uuid_t g;
 	uint32_t uid_ret;
 	uuid_create(&g, &uid_ret);
 	memcpy(pNewGUID, &g, sizeof(g));
-#endif // OPENBSD
 #else
 	uuid_t g;
 	uuid_generate(g);
