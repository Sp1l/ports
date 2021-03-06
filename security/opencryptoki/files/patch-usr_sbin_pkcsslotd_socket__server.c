--- usr/sbin/pkcsslotd/socket_server.c.orig	2015-12-04 22:06:36 UTC
+++ usr/sbin/pkcsslotd/socket_server.c
@@ -337,7 +337,7 @@ int CreateListenerSocket (void) {
 
 	// make socket file part of the pkcs11 group, and write accessable
 	// for that group
-	grp = getgrnam("pkcs11");
+	grp = getgrnam(PKCS11GROUP);
 	if (!grp) {
 		ErrLog("Group PKCS#11 does not exist");
 		DetachSocketListener(socketfd);
