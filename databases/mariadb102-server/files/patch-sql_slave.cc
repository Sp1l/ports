--- sql/slave.cc.orig	2017-02-16 08:28:07 UTC
+++ sql/slave.cc
@@ -60,6 +60,11 @@
 #include "debug_sync.h"
 #include "rpl_parallel.h"
 
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#define ERR_remove_state(X)
+#elif defined(HAVE_ERR_remove_thread_state)
+#define ERR_remove_state(X) ERR_remove_thread_state(NULL)
+#endif
 
 #define FLAGSTR(V,F) ((V)&(F)?#F" ":"")
 
@@ -4662,7 +4667,11 @@ err_during_init:
   DBUG_LEAVE;                                   // Must match DBUG_ENTER()
   my_thread_end();
 #ifdef HAVE_OPENSSL
+#if OPENSSL_VERSION_NUMBER < 0x10000000L
   ERR_remove_state(0);
+#elif OPENSSL_VERSION_NUMBER < 0x10100000L
+  ERR_remove_thread_state(0);
+#endif
 #endif
   pthread_exit(0);
   return 0;                                     // Avoid compiler warnings
@@ -5320,7 +5329,11 @@ err_during_init:
   DBUG_LEAVE;                                   // Must match DBUG_ENTER()
   my_thread_end();
 #ifdef HAVE_OPENSSL
+#if OPENSSL_VERSION_NUMBER < 0x10000000L
   ERR_remove_state(0);
+#elif OPENSSL_VERSION_NUMBER < 0x10100000L
+  ERR_remove_thread_state(0);
+#endif
 #endif
   pthread_exit(0);
   return 0;                                     // Avoid compiler warnings
