--- usr/lib/pkcs11/common/utility.c.orig	2015-12-04 22:06:36 UTC
+++ usr/lib/pkcs11/common/utility.c
@@ -295,6 +295,27 @@
 #include <pwd.h>
 #include <grp.h>
 
+#include <fcntl.h>
+
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
 #include "pkcs11types.h"
 #include "defs.h"
 #include "host_defs.h"
@@ -587,7 +608,7 @@ CK_RV CreateXProcLock(void)
 					goto err;
 				}
 
-				grp = getgrnam("pkcs11");
+				grp = getgrnam(PKCS11GROUP);
 				if (grp != NULL) {
 					if (fchown(spinxplfd, -1, grp->gr_gid)
 					    == -1) {
@@ -1131,7 +1152,7 @@ CK_RV check_user_and_group()
 	 * when forked). So we need to get the group information.
 	 * Really need to take the uid and map it to a name.
 	 */
-	grp = getgrnam("pkcs11");
+	grp = getgrnam(PKCS11GROUP);
 	if (grp == NULL) {
 		OCK_SYSLOG(LOG_ERR, "getgrnam() failed: %s\n", strerror(errno));
 		goto error;
