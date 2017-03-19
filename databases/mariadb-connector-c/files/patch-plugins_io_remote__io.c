--- plugins/io/remote_io.c.orig	2017-01-17 12:23:34 UTC
+++ plugins/io/remote_io.c
@@ -156,7 +156,7 @@ static size_t rio_write_callback(char *b
       size= free_bytes;
     else {
       curl_file->length+= size - free_bytes;
-      curl_file->buffer= tmp;
+      curl_file->buffer= (unsigned char *)tmp;
     }
   }
 
