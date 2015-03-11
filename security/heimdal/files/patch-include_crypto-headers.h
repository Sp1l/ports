--- include/crypto-headers.h.orig	2012-12-09 23:06:44.000000000 +0100
+++ include/crypto-headers.h	2015-03-11 19:50:53.148719459 +0100
@@ -28,6 +28,11 @@
 #ifndef BN_is_negative
 #define BN_set_negative(bn, flag) ((bn)->neg=(flag)?1:0)
 #define BN_is_negative(bn) ((bn)->neg != 0)
+
+#ifndef LIBRESSL_VERSION_NUMBER
+#define HAVE_RAND_EGD
+#endif
+
 #endif
 
 #else /* !HAVE_OPENSSL */
