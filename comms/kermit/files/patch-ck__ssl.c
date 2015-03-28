--- ck_ssl.c.orig	2011-07-06 13:03:32 UTC
+++ ck_ssl.c
@@ -1054,11 +1054,15 @@ ssl_display_comp(SSL * ssl)
     if (ssl == NULL)
         return;
 
+#ifndef NO_COMP
     if (ssl->expand == NULL || ssl->expand->meth == NULL)
+#endif
         printf("Compression: None\r\n");
+#ifndef NO_COMP
     else {
         printf("Compression: %s\r\n",ssl->expand->meth->name);
     }
+#endif
 }
 
 int
@@ -1483,9 +1487,13 @@ the build.\r\n\r\n");
         }
         debug(F110,"ssl_rnd_file",ssl_rnd_file,0);
 
+#ifndef NO_EGD
         rc1 = RAND_egd(ssl_rnd_file);
         debug(F111,"ssl_once_init","RAND_egd()",rc1);
-        if ( rc1 <= 0 ) {
+        if ( rc1 <= 0 ) 
+#endif
+	{
+
             rc2 = RAND_load_file(ssl_rnd_file, -1);
             debug(F111,"ssl_once_init","RAND_load_file()",rc1);
         }
