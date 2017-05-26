--- mysql-test/include/require_openssl_client.inc.orig	2017-03-20 12:18:14 UTC
+++ mysql-test/include/require_openssl_client.inc
@@ -0,0 +1,5 @@
+if ($CLIENT_TLS_LIBRARY != "OpenSSL") {
+  if ($CLIENT_TLS_LIBRARY != "LibreSSL") {
+    skip "Test requires Connector/C with OpenSSL library";
+  }
+}
