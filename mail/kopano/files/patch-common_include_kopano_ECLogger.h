--- common/include/kopano/ECLogger.h.orig	2017-02-06 15:39:23 UTC
+++ common/include/kopano/ECLogger.h
@@ -106,8 +106,10 @@ class _kc_export ECLogger {
 		_kc_hidden std::string MakeTimestamp(void);
 
 		unsigned int max_loglevel;
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 		locale_t timelocale;
 		locale_t datalocale;
+#endif
 		logprefix prefix;
 
 		/**
