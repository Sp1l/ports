--- plugin/password_validation/validate_password.cc.orig	2015-07-20 16:55:08.000000000 +0430
+++ plugin/password_validation/validate_password.cc	2015-11-14 15:14:39.000000000 +0330
@@ -16,6 +16,8 @@
 #include <my_sys.h>
 #include <string>
 #include <mysql/plugin_validate_password.h>
+/* solve clash between libc++ bitset::test() and test macro from my_global.h */
+#undef test
 #include <mysql/service_my_plugin_log.h>
 #include <mysql/service_mysql_string.h>
 #include <set>
