--- libmariadb/ma_io.c.orig	2017-01-17 12:23:34 UTC
+++ libmariadb/ma_io.c
@@ -123,7 +123,7 @@ remote:
     MYSQL mysql;
     if (rio_plugin ||(rio_plugin= (struct st_mysql_client_plugin_REMOTEIO *)
                       mysql_client_find_plugin(&mysql, NULL, MARIADB_CLIENT_REMOTEIO_PLUGIN)))
-      return rio_plugin->methods->open(location, mode);
+      return rio_plugin->methods->mopen(location, mode);
     return NULL;
   }
 #endif
@@ -144,7 +144,7 @@ int ma_close(MA_FILE *file)
     break;
 #ifdef HAVE_REMOTEIO
   case MA_FILE_REMOTE:
-    rc= rio_plugin->methods->close(file);
+    rc= rio_plugin->methods->mclose(file);
     break;
 #endif
   default:
@@ -154,6 +154,7 @@ int ma_close(MA_FILE *file)
 }
 /* }}} */
 
+
 /* {{{ ma_feof */
 int ma_feof(MA_FILE *file)
 {
@@ -166,7 +167,7 @@ int ma_feof(MA_FILE *file)
     break;
 #ifdef HAVE_REMOTEIO
   case MA_FILE_REMOTE:
-    return rio_plugin->methods->feof(file);
+    return rio_plugin->methods->mfeof(file);
     break;
 #endif
   default:
@@ -189,7 +190,7 @@ size_t ma_read(void *ptr, size_t size, s
     break;
 #ifdef HAVE_REMOTEIO
   case MA_FILE_REMOTE:
-    return rio_plugin->methods->read(ptr, size, nmemb, file);
+    return rio_plugin->methods->mread(ptr, size, nmemb, file);
     break;
 #endif
   default:
@@ -210,7 +211,7 @@ char *ma_gets(char *ptr, size_t size, MA
     break;
 #ifdef HAVE_REMOTEIO
   case MA_FILE_REMOTE:
-    return rio_plugin->methods->gets(ptr, size, file);
+    return rio_plugin->methods->mgets(ptr, size, file);
     break;
 #endif
   default:
