--- include/mariadb/ma_io.h.orig	2017-01-17 12:23:34 UTC
+++ include/mariadb/ma_io.h
@@ -37,11 +37,11 @@ typedef struct 
 
 #ifdef HAVE_REMOTEIO
 struct st_rio_methods {
-  MA_FILE *(*open)(const char *url, const char *mode);
-  int (*close)(MA_FILE *ptr);
-  int (*feof)(MA_FILE *file);
-  size_t (*read)(void *ptr, size_t size, size_t nmemb, MA_FILE *file);
-  char * (*gets)(char *ptr, size_t size, MA_FILE *file);
+  MA_FILE *(*mopen)(const char *url, const char *mode);
+  int (*mclose)(MA_FILE *ptr);
+  int (*mfeof)(MA_FILE *file);
+  size_t (*mread)(void *ptr, size_t size, size_t nmemb, MA_FILE *file);
+  char * (*mgets)(char *ptr, size_t size, MA_FILE *file);
 };
 #endif
 
