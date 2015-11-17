--- include/my_global.h.orig	2015-07-20 16:55:08.000000000 +0430
+++ include/my_global.h	2015-11-16 00:13:41.000000000 +0330
@@ -25,7 +25,7 @@
   differences are mitigated.
 */
 
-#include "my_config.h"
+#include "../../.build/include/my_config.h"
 
 #define __STDC_LIMIT_MACROS	/* Enable C99 limit macros */
 #define __STDC_FORMAT_MACROS	/* Enable C99 printf format macros */
@@ -566,7 +566,7 @@
 
 #define MY_HOW_OFTEN_TO_WRITE	1000	/* How often we want info on screen */
 
-#include <my_byteorder.h>
+#include "my_byteorder.h"
 
 #ifdef HAVE_CHARSET_utf8
 #define MYSQL_UNIVERSAL_CLIENT_CHARSET "utf8"
@@ -628,7 +628,7 @@
 #define MYSQL_PLUGIN_IMPORT
 #endif
 
-#include <my_dbug.h>
+#include "my_dbug.h"
 
 #ifdef EMBEDDED_LIBRARY
 #define NO_EMBEDDED_ACCESS_CHECKS
