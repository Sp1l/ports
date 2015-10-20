--- include/mysql/service_encryption.h.orig	2015-10-15 17:43:37.000000000 +0200
+++ include/mysql/service_encryption.h	2015-10-20 14:05:44.029525238 +0200
@@ -35,9 +35,9 @@ extern "C" {
 #define inline __inline
 #endif
-#else
+#elif !defined (__FreeBSD__)
 #include <alloca.h>
 #endif
 #endif
 
 /* returned from encryption_key_get_latest_version() */
 #define ENCRYPTION_KEY_VERSION_INVALID        (~(unsigned int)0)
