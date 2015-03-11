--- lib/krb5/crypto-rand.c.orig	2012-12-09 23:06:44.000000000 +0100
+++ lib/krb5/crypto-rand.c	2015-03-11 19:01:30.449923193 +0100
@@ -66,6 +66,7 @@
 	krb5_context context;
 	const char *p;
 
+#ifdef HAVE_RAND_EGD
 	/* Try using egd */
 	if (!krb5_init_context(&context)) {
 	    p = krb5_config_get_string(context, NULL, "libdefaults",
@@ -74,6 +75,7 @@
 		RAND_egd_bytes(p, ENTROPY_NEEDED);
 	    krb5_free_context(context);
 	}
+#endif
 #else
 	/* TODO: Once a Windows CryptoAPI RAND method is defined, we
 	   can use that and failover to another method. */
