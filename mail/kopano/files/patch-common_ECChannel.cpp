--- common/ECChannel.cpp.orig	2017-02-06 15:39:23 UTC
+++ common/ECChannel.cpp
@@ -33,6 +33,9 @@
 #ifdef LINUX
 #include <linux/rtnetlink.h>
 #endif
+#ifdef __FreeBSD__
+#include <netinet/tcp_fastopen.h>
+#endif
 
 #include <cerrno>
 #include <mapicode.h>
@@ -837,10 +840,15 @@ int zcp_bindtodevice(int fd, const char 
 	if (i == NULL || strcmp(i, "any") == 0 || strcmp(i, "all") == 0 ||
 	    strcmp(i, "") == 0)
 		return 0;
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, i, strlen(i)) >= 0)
 		return 0;
 	ec_log_err("Unable to bind to interface %s: %s", i, strerror(errno));
 	return -errno;
+#else
+	ec_log_err("Unable to bind to interface %s: %s", i, strerror(errno));
+	return -1;
+#endif
 }
 
 HRESULT HrListen(const char *szBind, uint16_t ulPort, int *lpulListenSocket)
@@ -957,7 +965,7 @@ HRESULT HrAccept(int ulListenFD, ECChann
 		ec_log_err("HrAccept: invalid parameters");
 		return MAPI_E_INVALID_PARAMETER;
 	}
-#ifdef TCP_FASTOPEN
+#if defined(TCP_FASTOPEN) && !defined(__FreeBSD__)
 	static const int qlen = SOMAXCONN;
 	if (setsockopt(ulListenFD, SOL_TCP, TCP_FASTOPEN, &qlen, sizeof(qlen)) < 0)
 		/* ignore - no harm in not having fastopen */;
