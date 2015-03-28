--- types.c.orig	2013-01-23 04:42:08 UTC
+++ types.c
@@ -857,7 +857,8 @@ unsigned char *get_content_type_by_exten
 			ext = NULL;
 		}
 	if (ext) while (ext[extl] && ext[extl] != '.' && !dir_sep(ext[extl]) && !end_of_dir(url, ext[extl])) extl++;
-	if ((extl == 3 && !casecmp(ext, cast_uchar "htm", 3)) ||
+	if (force_html || 
+	    (extl == 3 && !casecmp(ext, cast_uchar "htm", 3)) ||
 	    (extl == 4 && !casecmp(ext, cast_uchar "html", 4))) return stracpy(cast_uchar "text/html");
 	foreach(e, extensions) {
 		unsigned char *fname = NULL;
