--- usr/lib/pkcs11/api/apiutil.c.orig	2015-12-04 22:06:36 UTC
+++ usr/lib/pkcs11/api/apiutil.c
@@ -298,10 +298,10 @@
 #include <string.h>
 #include <strings.h>
 #include <unistd.h>
-#include <alloca.h>
 #include <dlfcn.h>
 #include <errno.h>
 #include <sys/syslog.h>
+#include <limits.h>
 
 #include <sys/ipc.h>
 
@@ -314,10 +314,28 @@
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
-#include <sys/file.h>
 
 static int xplfd = -1;
 
+#ifdef __sun
+#define        LOCK_EX F_LOCK
+#define        LOCK_UN F_ULOCK
+#define        flock(fd, func) lockf(fd, func, 0)
+#endif
+
+#ifndef        LOCK_SH
+#define        LOCK_SH 1       /* shared lock */
+#endif
+#ifndef        LOCK_EX
+#define        LOCK_EX 2       /* exclusive lock */
+#endif
+#ifndef        LOCK_NB
+#define        LOCK_NB 4       /* don't block when locking */
+#endif
+#ifndef        LOCK_UN
+#define        LOCK_UN 8       /* unlock */
+#endif
+
 #include <libgen.h>
 
 #define LIBLOCATION  LIB_PATH
