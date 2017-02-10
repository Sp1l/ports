--- common/ECLogger.cpp.orig	2017-02-06 15:39:23 UTC
+++ common/ECLogger.cpp
@@ -26,6 +26,9 @@
 #include <zlib.h>
 #include <kopano/stringutil.h>
 #include "charset/localeutil.h"
+#if defined(__OpenBSD__) || defined(__FreeBSD__)
+#include <signal.h>
+#endif
 #include "config.h"
 #include <poll.h>
 #if HAVE_SYSLOG_H
@@ -59,9 +62,11 @@ static ECLogger *ec_log_target = &ec_log
 
 ECLogger::ECLogger(int max_ll) {
 	max_loglevel = max_ll;
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	// get system locale for time, NULL is returned if locale was not found.
 	timelocale = createlocale(LC_TIME, "C");
 	datalocale = createUTF8Locale();
+#endif
 	prefix = LP_NONE;
 	m_ulRef = 1;
 }
@@ -70,11 +75,13 @@ ECLogger::~ECLogger() {
 	if (ec_log_target == this)
 		ec_log_set(NULL);
 
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	if (timelocale)
 		freelocale(timelocale);
 
 	if (datalocale)
 		freelocale(datalocale);
+#endif
 }
 
 void ECLogger::SetLoglevel(unsigned int max_ll) {
@@ -88,9 +95,11 @@ std::string ECLogger::MakeTimestamp() {
 	localtime_r(&now, &local);
 	char buffer[_LOG_TSSIZE];
 
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	if (timelocale)
 		strftime_l(buffer, sizeof buffer, "%c", &local, timelocale);
 	else
+#endif
 		strftime(buffer, sizeof buffer, "%c", &local);
 
 	return buffer;
@@ -151,7 +160,11 @@ int ECLogger::snprintf(char *str, size_t
 	int len = 0;
 
 	va_start(va, format);
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	len = _vsnprintf_l(str, size, format, datalocale, va);
+#else
+	len = _vsnprintf_l(str, size, format, va);
+#endif
 	va_end(va);
 
 	return len;
@@ -390,7 +403,11 @@ void ECLogger_File::Log(unsigned int log
 
 void ECLogger_File::LogVA(unsigned int loglevel, const char *format, va_list& va) {
 	char msgbuffer[_LOG_BUFSIZE];
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	_vsnprintf_l(msgbuffer, sizeof msgbuffer, format, datalocale, va);
+#else
+	_vsnprintf_l(msgbuffer, sizeof msgbuffer, format, va);
+#endif
 
 	Log(loglevel, std::string(msgbuffer));
 }
@@ -449,7 +466,11 @@ void ECLogger_Syslog::LogVA(unsigned int
 	vsyslog(levelmap[loglevel & EC_LOGLEVEL_MASK], format, va);
 #else
 	char msgbuffer[_LOG_BUFSIZE];
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	_vsnprintf_l(msgbuffer, sizeof msgbuffer, format, datalocale, va);
+#else
+	_vsnprintf_l(msgbuffer, sizeof msgbuffer, format, va);
+#endif
 	syslog(levelmap[loglevel & EC_LOGLEVEL_MASK], "%s", msgbuffer);
 #endif
 }
@@ -524,7 +545,12 @@ void ECLogger_Tee::Log(unsigned int logl
 void ECLogger_Tee::LogVA(unsigned int loglevel, const char *format, va_list &va)
 {
 	char msgbuffer[_LOG_BUFSIZE];
+
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	_vsnprintf_l(msgbuffer, sizeof msgbuffer, format, datalocale, va);
+#else
+	_vsnprintf_l(msgbuffer, sizeof msgbuffer, format, va);
+#endif
 
 	for (auto log : m_loggers)
 		log->Log(loglevel, std::string(msgbuffer));
@@ -571,7 +597,7 @@ void ECLogger_Pipe::Log(unsigned int log
 	off += 1;
 
 	if (prefix == LP_TID)
-		len = snprintf(msgbuffer + off, sizeof msgbuffer - off, "[0x%08x] ", (unsigned int)pthread_self());
+		len = snprintf(msgbuffer + off, sizeof msgbuffer - off, "[0x%08lx] ", (unsigned long)pthread_self());
 	else if (prefix == LP_PID)
 		len = snprintf(msgbuffer + off, sizeof msgbuffer - off, "[%5d] ", getpid());
 
@@ -615,7 +641,7 @@ void ECLogger_Pipe::LogVA(unsigned int l
 	off += 1;
 
 	if (prefix == LP_TID)
-		len = snprintf(msgbuffer + off, sizeof msgbuffer - off, "[0x%08x] ", (unsigned int)pthread_self());
+		len = snprintf(msgbuffer + off, sizeof msgbuffer - off, "[0x%08lx] ", (unsigned long)pthread_self());
 	else if (prefix == LP_PID)
 		len = snprintf(msgbuffer + off, sizeof msgbuffer - off, "[%5d] ", getpid());
 
@@ -625,7 +651,11 @@ void ECLogger_Pipe::LogVA(unsigned int l
 		off += len;
 
 	// return value is what WOULD have been written if enough space were available in the buffer
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	len = _vsnprintf_l(msgbuffer + off, sizeof msgbuffer - off - 1, format, datalocale, va);
+#else
+	len = _vsnprintf_l(msgbuffer + off, sizeof msgbuffer - off - 1, format, va);
+#endif
 	// -1 can be returned on formatting error (eg. %ls in C locale)
 	if (len < 0)
 		len = 0;
@@ -995,8 +1025,12 @@ void generic_sigsegv_handler(ECLogger *l
 	ec_log_bt(EC_LOGLEVEL_CRIT, "Backtrace:");
 	ec_log_crit("Signal errno: %s, signal code: %d", strerror(si->si_errno), si->si_code);
 	ec_log_crit("Sender pid: %d, sender uid: %d, si_status: %d", si->si_pid, si->si_uid, si->si_status);
+#ifndef __FreeBSD__
 	ec_log_crit("User time: %ld, system time: %ld, signal value: %d", si->si_utime, si->si_stime, si->si_value.sival_int);
 	ec_log_crit("Faulting address: %p, affected fd: %d", si->si_addr, si->si_fd);
+#else
+	ec_log_crit("Faulting address: %p", si->si_addr);
+#endif
 	lpLogger->Log(EC_LOGLEVEL_FATAL, "When reporting this traceback, please include Linux distribution name (and version), system architecture and Kopano version.");
 	/* Reset to DFL to avoid recursion */
 	if (signal(signr, SIG_DFL) < 0)
