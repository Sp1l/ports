--- cf/crypto.m4.orig	2012-12-09 23:06:44.000000000 +0100
+++ cf/crypto.m4	2015-04-10 22:22:32.902931044 +0200
@@ -143,6 +143,7 @@
 			break;
 		fi
 	done
+	AC_CHECK_LIB(crypto, RAND_egd, AC_DEFINE(HAVE_RAND_EGD, 1, [Define if the libcrypto has RAND_egd]))
 	CFLAGS="$save_CFLAGS"
 	LIBS="$save_LIBS"
 fi
