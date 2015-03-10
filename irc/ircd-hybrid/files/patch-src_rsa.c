--- src/rsa.c.orig	2013-06-23 19:49:22.000000000 +0200
+++ src/rsa.c	2015-03-10 20:19:06.002564940 +0100
@@ -68,11 +68,13 @@
 int
 get_randomness(unsigned char *buf, int length)
 {
+#ifdef HAVE_RAND_EGD
   /* Seed OpenSSL PRNG with EGD enthropy pool -kre */
   if (ConfigFileEntry.use_egd &&
       ConfigFileEntry.egdpool_path)
     if (RAND_egd(ConfigFileEntry.egdpool_path) == -1)
       return -1;
+#endif
 
   if (RAND_status())
     return RAND_bytes(buf, length);
