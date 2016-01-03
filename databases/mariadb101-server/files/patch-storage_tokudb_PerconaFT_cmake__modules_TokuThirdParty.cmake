--- storage/tokudb/PerconaFT/cmake_modules/TokuThirdParty.cmake.orig	2015-12-23 16:33:32.000000000 +0100
+++ storage/tokudb/PerconaFT/cmake_modules/TokuThirdParty.cmake	2016-01-03 17:23:42.102122634 +0100
@@ -34,6 +34,13 @@ if (CMAKE_PROJECT_NAME STREQUAL TokuDB)
     endif ()
 endif ()
 
+IF (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
+  include_directories("/usr/include")
+
+  add_library(lzma SHARED IMPORTED)
+  set_target_properties(lzma PROPERTIES IMPORTED_LOCATION
+    "/usr/lib/liblzma.so")
+ELSE()
 ## add lzma with an external project
 set(xz_configure_opts --with-pic --enable-static)
 if (APPLE)
@@ -105,7 +112,7 @@ add_library(lzma STATIC IMPORTED)
 set_target_properties(lzma PROPERTIES IMPORTED_LOCATION
   "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/xz/lib/liblzma.a")
 add_dependencies(lzma build_lzma)
-
+ENDIF()
 
 ## add snappy with an external project
 set(SNAPPY_SOURCE_DIR "${TokuDB_SOURCE_DIR}/third_party/snappy-1.1.2" CACHE FILEPATH "Where to find sources for snappy.")
