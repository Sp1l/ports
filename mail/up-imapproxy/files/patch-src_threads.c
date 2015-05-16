--- src/threads.c.orig	2010-07-25 09:11:36 UTC
+++ src/threads.c
@@ -51,6 +51,9 @@
 
 #define OPENSSL_THREAD_DEFINES
 #include <openssl/opensslconf.h>
+#if defined(THREADS)
+#define OPENSSL_THREADS
+#endif
 #if defined(OPENSSL_THREADS)
 
 
