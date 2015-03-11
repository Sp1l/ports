--- xymonnet/contest.c.orig	2014-01-10 10:29:38.000000000 +0100
+++ xymonnet/contest.c	2015-03-11 15:49:20.218730976 +0100
@@ -460,11 +460,13 @@
 			/* load entropy from files */
 			RAND_load_file(RAND_file_name(path, sizeof (path)), -1);
 
+#ifndef BSD 
 			/* load entropy from egd sockets */
 			RAND_egd("/var/run/egd-pool");
 			RAND_egd("/dev/egd-pool");
 			RAND_egd("/etc/egd-pool");
 			RAND_egd("/var/spool/prngd/pool");
+#endif
 
 			/* shuffle $RANDFILE (or ~/.rnd if unset) */
 			RAND_write_file(RAND_file_name(path, sizeof (path)));
