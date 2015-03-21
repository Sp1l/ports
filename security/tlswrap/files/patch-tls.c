--- tls.c.orig	2015-03-21 13:23:17 UTC
+++ tls.c
@@ -73,10 +73,12 @@ void tls_init(char *egd_sock) {
 		printf("egd_sock is %s\n", egd_sock);
 #ifdef HAVE_RAND_STATUS
 	if (RAND_status() != 1) {
+#ifdef HAVE_RAND_EGD
 		if ( RAND_egd(egd_sock) == -1 ) {
 			fprintf(stderr, "egd_sock is %s\n", egd_sock);
 			sys_err("RAND_egd failed\n");
 		}
+#endif
 		if (RAND_status() != 1)
 			sys_err("ssl_init: System without /dev/urandom, PRNG seeding must be done manually.\r\n");
 	}
