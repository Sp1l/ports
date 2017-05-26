--- cmake/ssl.cmake.orig	2017-02-16 08:28:05 UTC
+++ cmake/ssl.cmake
@@ -119,55 +119,19 @@ MACRO (MYSQL_CHECK_SSL)
          WITH_SSL STREQUAL "yes" OR
          WITH_SSL_PATH
          )
-    # First search in WITH_SSL_PATH.
-    FIND_PATH(OPENSSL_ROOT_DIR
-      NAMES include/openssl/ssl.h
-      NO_CMAKE_PATH
-      NO_CMAKE_ENVIRONMENT_PATH
-      HINTS ${WITH_SSL_PATH}
-    )
-    # Then search in standard places (if not found above).
-    FIND_PATH(OPENSSL_ROOT_DIR
-      NAMES include/openssl/ssl.h
-    )
-
-    FIND_PATH(OPENSSL_INCLUDE_DIR
-      NAMES openssl/ssl.h
-      HINTS ${OPENSSL_ROOT_DIR}/include
-    )
-
-    IF (WIN32)
-      FIND_FILE(OPENSSL_APPLINK_C
-        NAMES openssl/applink.c
-        HINTS ${OPENSSL_ROOT_DIR}/include
-      )
-      MESSAGE_ONCE(OPENSSL_APPLINK_C "OPENSSL_APPLINK_C ${OPENSSL_APPLINK_C}")
-    ENDIF()
-
-    # On mac this list is <.dylib;.so;.a>
-    # We prefer static libraries, so we revert it here.
-    IF (WITH_SSL_PATH)
-      LIST(REVERSE CMAKE_FIND_LIBRARY_SUFFIXES)
-    ENDIF()
-    FIND_LIBRARY(OPENSSL_SSL_LIBRARY
-                 NAMES ssl ssleay32 ssleay32MD
-                 HINTS ${OPENSSL_ROOT_DIR}/lib)
-    FIND_LIBRARY(OPENSSL_CRYPTO_LIBRARY
-                 NAMES crypto libeay32
-                 HINTS ${OPENSSL_ROOT_DIR}/lib)
-    MARK_AS_ADVANCED(OPENSSL_CRYPTO_LIBRARY OPENSSL_SSL_LIBRARY OPENSSL_ROOT_DIR
-      OPENSSL_INCLUDE_DIR)
-    IF (WITH_SSL_PATH)
-      LIST(REVERSE CMAKE_FIND_LIBRARY_SUFFIXES)
+    IF(NOT OPENSSL_ROOT_DIR)
+      IF(WITH_SSL_PATH)
+        SET(OPENSSL_ROOT_DIR ${WITH_SSL_PATH})
+      ENDIF()
     ENDIF()
-
-    INCLUDE(CheckSymbolExists)
-    SET(CMAKE_REQUIRED_INCLUDES ${OPENSSL_INCLUDE_DIR})
-    CHECK_SYMBOL_EXISTS(SHA512_DIGEST_LENGTH "openssl/sha.h" 
-                        HAVE_SHA512_DIGEST_LENGTH)
-    SET(CMAKE_REQUIRED_INCLUDES)
-    IF(OPENSSL_INCLUDE_DIR AND OPENSSL_SSL_LIBRARY   AND
-       OPENSSL_CRYPTO_LIBRARY AND HAVE_SHA512_DIGEST_LENGTH)
+    Find_Package(OpenSSL)
+    IF(OPENSSL_FOUND)
+      SET(OPENSSL_LIBRARY ${OPENSSL_SSL_LIBRARY})
+      INCLUDE(CheckSymbolExists)
+      SET(CMAKE_REQUIRED_INCLUDES ${OPENSSL_INCLUDE_DIR})
+      CHECK_SYMBOL_EXISTS(SHA512_DIGEST_LENGTH "openssl/sha.h"
+                          HAVE_SHA512_DIGEST_LENGTH)
+      SET(CMAKE_REQUIRED_INCLUDES)
       SET(SSL_SOURCES "")
       SET(SSL_LIBRARIES ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
       IF(CMAKE_SYSTEM_NAME MATCHES "SunOS")
@@ -177,16 +141,6 @@ MACRO (MYSQL_CHECK_SSL)
         SET(SSL_LIBRARIES ${SSL_LIBRARIES} ${LIBDL})
       ENDIF()
 
-      # Verify version number. Version information looks like:
-      #   #define OPENSSL_VERSION_NUMBER 0x1000103fL
-      # Encoded as MNNFFPPS: major minor fix patch status
-      FILE(STRINGS "${OPENSSL_INCLUDE_DIR}/openssl/opensslv.h"
-           OPENSSL_VERSION_TEXT
-           REGEX "^# *define[\t ]+OPENSSL_VERSION_TEXT[\t ]+")
-      STRING(REGEX REPLACE
-             "^.*OPENSSL_VERSION_TEXT[\t ]+\"OpenSSL ([-0-9a-z.]+).*$" "\\1"
-             OPENSSL_VERSION "${OPENSSL_VERSION_TEXT}")
-
       MESSAGE_ONCE(OPENSSL_INCLUDE_DIR "OPENSSL_INCLUDE_DIR = ${OPENSSL_INCLUDE_DIR}")
       MESSAGE_ONCE(OPENSSL_SSL_LIBRARY "OPENSSL_SSL_LIBRARY = ${OPENSSL_SSL_LIBRARY}")
       MESSAGE_ONCE(OPENSSL_CRYPTO_LIBRARY "OPENSSL_CRYPTO_LIBRARY = ${OPENSSL_CRYPTO_LIBRARY}")
