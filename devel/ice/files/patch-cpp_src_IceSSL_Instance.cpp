--- cpp/src/IceSSL/Instance.cpp.orig	2013-10-04 15:48:14 UTC
+++ cpp/src/IceSSL/Instance.cpp
@@ -31,6 +31,7 @@
 
 #include <openssl/rand.h>
 #include <openssl/err.h>
+#include <openssl/opensslv.h>
 
 #include <IceUtil/DisableWarnings.h>
 
@@ -266,7 +267,7 @@ IceSSL::Instance::Instance(const Communi
                     }
                 }
             }
-#ifndef _WIN32
+#if !defined(_WIN32) && !defined(LIBRESSL_VERSION_NUMBER)
             //
             // The Entropy Gathering Daemon (EGD) is not available on Windows.
             // The file should be a Unix domain socket for the daemon.
