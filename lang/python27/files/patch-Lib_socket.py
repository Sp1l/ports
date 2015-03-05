--- Lib/socket.py.orig	2014-12-10 15:59:40 UTC
+++ Lib/socket.py
@@ -67,7 +67,6 @@ else:
     from _ssl import SSLError as sslerror
     from _ssl import \
          RAND_add, \
-         RAND_egd, \
          RAND_status, \
          SSL_ERROR_ZERO_RETURN, \
          SSL_ERROR_WANT_READ, \
@@ -78,6 +77,14 @@ else:
          SSL_ERROR_WANT_CONNECT, \
          SSL_ERROR_EOF, \
          SSL_ERROR_INVALID_ERROR_CODE
+### Fix build with LibreSSL (does not have RAND_egd)
+### PR192511, http://bugs.python.org/issue21356
+    try:
+         from _ssl import RAND_egd
+         # LibreSSL does not provide RAND_egd
+    except ImportError:
+         pass
+### End PR192511
 
 import os, sys, warnings
 
