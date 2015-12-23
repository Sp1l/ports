--- ckcftp.c.orig	2015-02-05 20:08:09 UTC
+++ ckcftp.c
@@ -10210,9 +10210,11 @@ ssl_auth() {
     if (ftp_bug_use_ssl_v2) {
         /* allow SSL 2.0 or later */
         client_method = SSLv23_client_method();
+#ifndef OPENSSL_NO_SSL3
     } else if (ftp_bug_use_ssl_v3) {
         /* allow SSL 3.0 ONLY - previous default */
         client_method = SSLv3_client_method();
+#endif
     } else {
         /* default - allow TLS 1.0 or later */
         client_method = TLSv1_client_method();
