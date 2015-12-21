--- usr/sbin/pkcsconf/pkcsconf.c.orig	2015-12-04 22:06:36 UTC
+++ usr/sbin/pkcsconf/pkcsconf.c
@@ -777,6 +777,8 @@ display_pkcs11_info(void){
    printf("\tLibrary Version %d.%d \n", CryptokiInfo.libraryVersion.major,
          CryptokiInfo.libraryVersion.minor);
 
+   cleanup();
+
    return rc;
 }
 
