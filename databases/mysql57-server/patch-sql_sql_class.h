--- sql/sql_class.h.orig	2015-07-20 16:55:10.000000000 +0430
+++ sql/sql_class.h	2015-11-16 00:28:46.000000000 +0330
@@ -18,13 +18,13 @@
 
 /* Classes in mysql */
 
-#include "my_global.h"
+#include "../include/my_global.h"
 
-#include "dur_prop.h"                     // durability_properties
-#include "mysql/mysql_lex_string.h"       // LEX_STRING
-#include "mysql_com.h"                    // Item_result
-#include "mysql_com_server.h"             // NET_SERVER
-#include "auth/sql_security_ctx.h"        // Security_context
+#include "../include/dur_prop.h"                     // durability_properties
+#include "../include/mysql/mysql_lex_string.h"       // LEX_STRING
+#include "../include/mysql_com.h"                    // Item_result
+#include "../include/mysql_com_server.h"             // NET_SERVER
+#include "sql_security_ctx.h"        // Security_context
 #include "derror.h"                       // ER_THD
 #include "discrete_interval.h"            // Discrete_interval
 #include "handler.h"                      // KEY_CREATE_INFO
