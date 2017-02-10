--- m4lcommon/CommonUtil.cpp.orig	2017-02-10 22:46:37 UTC
+++ m4lcommon/CommonUtil.cpp
@@ -56,7 +56,9 @@
 
 #include <sys/types.h>
 #include <sys/socket.h>
+#include <netinet/in.h>
 #include <netdb.h>
+#include <pthread.h>
 
 using namespace std;
 using namespace KCHL;
