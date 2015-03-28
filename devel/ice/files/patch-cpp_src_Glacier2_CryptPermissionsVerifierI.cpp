--- cpp/src/Glacier2/CryptPermissionsVerifierI.cpp.orig	2013-10-04 15:48:14 UTC
+++ cpp/src/Glacier2/CryptPermissionsVerifierI.cpp
@@ -9,6 +9,7 @@
 
 #include <Glacier2/CryptPermissionsVerifierI.h>
 #include <openssl/des.h>
+#include <openssl/opensslv.h>
 
 using namespace std;
 using namespace Ice;
