--- plugins/pvio/pvio_socket.c.orig	2017-01-17 12:23:34 UTC
+++ plugins/pvio/pvio_socket.c
@@ -48,6 +48,7 @@
 #include <fcntl.h>
 #endif
 #include <netinet/in_systm.h>
+#include <netinet/in.h>
 #include <netinet/ip.h>
 #include <netdb.h>
 #include <netinet/tcp.h>
