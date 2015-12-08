--- plugin/password_validation/validate_password.cc.orig	2015-10-12 09:51:33.000000000 +0330
+++ plugin/password_validation/validate_password.cc	2015-11-29 02:04:32.000000000 +0330
@@ -18,6 +18,8 @@
 #include <mysql/plugin_validate_password.h>
 #include <mysql/service_my_plugin_log.h>
 #include <mysql/service_mysql_string.h>
+/* solve clash between libc++ bitset::test() and test macro from my_global.h */
+#undef test
 #include <set>
 #include <iostream>
 #include <fstream>
