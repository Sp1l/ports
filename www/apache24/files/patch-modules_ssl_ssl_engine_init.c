--- modules/ssl/ssl_engine_init.c.orig  2014-07-14 14:29:22.000000000 +0200
+++ modules/ssl/ssl_engine_init.c       2014-09-29 09:53:18.935633125 +0200
@@ -353,9 +353,11 @@
             return ssl_die(s);
         }

+#ifdef ENGINE_CTRL_CHIL_SET_FORKCHECK
         if (strEQ(mc->szCryptoDevice, "chil")) {
             ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
         }
+#endif

         if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01889)
