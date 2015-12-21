--- usr/lib/pkcs11/common/loadsave.c.orig	2015-12-04 22:06:36 UTC
+++ usr/lib/pkcs11/common/loadsave.c
@@ -637,7 +637,7 @@ void set_perm(int file)
 		// Set absolute permissions or rw-rw-r--
 		fchmod(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
 
-		grp = getgrnam("pkcs11");	// Obtain the group id
+		grp = getgrnam(PKCS11GROUP);	// Obtain the group id
 		if (grp) {
 			// set ownership to root, and pkcs11 group
 			if (fchown(file, getuid(), grp->gr_gid) != 0) {
