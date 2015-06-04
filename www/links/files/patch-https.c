--- https.c.orig	2013-09-20 21:17:00 UTC
+++ https.c
@@ -36,7 +36,10 @@ SSL *getSSL(void)
 		unsigned os_pool_size;
 
 		const unsigned char *f = (const unsigned char *)RAND_file_name(cast_char f_randfile, sizeof(f_randfile));
-		if (f && RAND_egd(cast_const_char f) < 0) {
+#ifndef OPENSSL_NO_EGD
+		if (f && RAND_egd(cast_const_char f) < 0) 
+#endif
+		{
 			/* Not an EGD, so read and write to it */
 			if (RAND_load_file(cast_const_char f_randfile, -1))
 				RAND_write_file(cast_const_char f_randfile);
