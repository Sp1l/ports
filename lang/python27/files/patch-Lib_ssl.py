--- Lib/ssl.py.orig	2014-06-30 04:05:31.000000000 +0200
+++ Lib/ssl.py	2014-11-27 22:49:55.973755982 +0100
@@ -62,7 +62,10 @@
 from _ssl import OPENSSL_VERSION_NUMBER, OPENSSL_VERSION_INFO, OPENSSL_VERSION
 from _ssl import SSLError
 from _ssl import CERT_NONE, CERT_OPTIONAL, CERT_REQUIRED
-from _ssl import RAND_status, RAND_egd, RAND_add
+try:
+     from _ssl import RAND_status, RAND_egd, RAND_add
+except ImportError:
+     from _ssl import RAND_status, RAND_add
 from _ssl import \
      SSL_ERROR_ZERO_RETURN, \
      SSL_ERROR_WANT_READ, \
