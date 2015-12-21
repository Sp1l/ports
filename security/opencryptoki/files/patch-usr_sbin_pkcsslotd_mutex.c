--- usr/sbin/pkcsslotd/mutex.c.orig	2015-12-04 22:06:36 UTC
+++ usr/sbin/pkcsslotd/mutex.c
@@ -323,7 +323,7 @@ CreateXProcLock(void)
 					goto error;
 				}
 
-				grp = getgrnam("pkcs11");
+				grp = getgrnam(PKCS11GROUP);
 				if (grp != NULL) {
 					if (fchown(xplfd,-1,grp->gr_gid) == -1) {
 						DbgLog(DL0,"%s:fchown(%s):%s\n",
