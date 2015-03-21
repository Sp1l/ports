--- cpp/src/IceGrid/RegistryI.cpp.orig	2013-10-04 15:48:14 UTC
+++ cpp/src/IceGrid/RegistryI.cpp
@@ -41,6 +41,7 @@
 #include <fstream>
 
 #include <openssl/des.h> // For crypt() passwords
+#include <openssl/opensslv.h>
 
 #include <sys/types.h>
 
