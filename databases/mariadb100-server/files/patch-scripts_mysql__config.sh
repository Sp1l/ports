--- scripts/mysql_config.sh.orig	2015-05-18 18:46:28 UTC
+++ scripts/mysql_config.sh
@@ -109,8 +109,11 @@ fi
 # We intentionally add a space to the beginning and end of lib strings, simplifies replace later
 libs=" $ldflags -L$pkglibdir @RPATH_OPTION@ -lmysqlclient @ZLIB_DEPS@ @NON_THREADED_LIBS@"
 libs="$libs @openssl_libs@ @STATIC_NSS_FLAGS@ "
+libs="$libs -L/usr/local/lib "
 libs_r=" $ldflags -L$pkglibdir  @RPATH_OPTION@ -lmysqlclient_r @ZLIB_DEPS@ @CLIENT_LIBS@ @openssl_libs@ "
+libs_r="$libs_r -L/usr/local/lib "
 embedded_libs=" $ldflags -L$pkglibdir @RPATH_OPTION@ -lmysqld @LIBDL@ @ZLIB_DEPS@ @LIBS@ @WRAPLIBS@ @openssl_libs@ "
+embedded_libs="$embedded_libs -L/usr/local/lib "
 
 if [ -r "$pkglibdir/libmygcc.a" ]; then
   # When linking against the static library with a different version of GCC
