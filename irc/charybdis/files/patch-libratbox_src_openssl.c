--- libratbox/src/openssl.c.orig	2012-12-31 22:47:31.000000000 +0100
+++ libratbox/src/openssl.c	2015-03-10 14:20:19.799041904 +0100
@@ -577,7 +577,9 @@
 	switch (seed_type)
 	{
 	case RB_PRNG_EGD:
+#ifdef HAVE_RAND_EGD
 		if(RAND_egd(path) == -1)
+#endif
 			return -1;
 		break;
 	case RB_PRNG_FILE:
