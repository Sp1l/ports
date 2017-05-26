--- mysys_ssl/my_md5.cc.orig	2017-02-16 08:28:07 UTC
+++ mysys_ssl/my_md5.cc
@@ -27,6 +27,8 @@
 #include <my_md5.h>
 #include <stdarg.h>
 
+#define MA_HASH_CTX_SIZE 512
+
 #if defined(HAVE_YASSL)
 #include "md5.hpp"
 
@@ -57,11 +59,18 @@ static void md5_result(MD5_CONTEXT *cont
 }
 
 #elif defined(HAVE_OPENSSL)
+
+
 #include <openssl/evp.h>
+
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#define EVP_MD_CTX_reset(X) EVP_MD_CTX_cleanup(X)
+#endif
 typedef EVP_MD_CTX MD5_CONTEXT;
 
 static void md5_init(MD5_CONTEXT *context)
 {
+  memset(context, 0, my_md5_context_size());
   EVP_MD_CTX_init(context);
 #ifdef EVP_MD_CTX_FLAG_NON_FIPS_ALLOW
   /* Ok to ignore FIPS: MD5 is not used for crypto here */
@@ -83,7 +92,7 @@ static void md5_input(MD5_CONTEXT *conte
 static void md5_result(MD5_CONTEXT *context, uchar digest[MD5_HASH_SIZE])
 {
   EVP_DigestFinal_ex(context, digest, NULL);
-  EVP_MD_CTX_cleanup(context);
+  EVP_MD_CTX_reset(context);
 }
 
 #endif /* HAVE_YASSL */
@@ -99,11 +108,14 @@ static void md5_result(MD5_CONTEXT *cont
 */
 void my_md5(uchar *digest, const char *buf, size_t len)
 {
+#ifdef HAVE_YASSL
   MD5_CONTEXT md5_context;
-
-  md5_init_fast(&md5_context);
-  md5_input(&md5_context, (const uchar *)buf, len);
-  md5_result(&md5_context, digest);
+#else
+  unsigned char md5_context[MA_HASH_CTX_SIZE];
+#endif
+  md5_init_fast((MD5_CONTEXT *)&md5_context);
+  md5_input((MD5_CONTEXT *)&md5_context, (const uchar *)buf, len);
+  md5_result((MD5_CONTEXT *)&md5_context, digest);
 }
 
 
@@ -122,22 +134,25 @@ void my_md5(uchar *digest, const char *b
 void my_md5_multi(uchar *digest, ...)
 {
   va_list args;
-  va_start(args, digest);
-
-  MD5_CONTEXT md5_context;
   const uchar *str;
+#ifdef HAVE_YASSL
+  MD5_CONTEXT md5_context;
+#else
+  unsigned char md5_context[MA_HASH_CTX_SIZE];
+#endif
+  va_start(args, digest);
 
-  md5_init_fast(&md5_context);
+  md5_init_fast((MD5_CONTEXT *)&md5_context);
   for (str= va_arg(args, const uchar*); str; str= va_arg(args, const uchar*))
-    md5_input(&md5_context, str, va_arg(args, size_t));
+    md5_input((MD5_CONTEXT *)&md5_context, str, va_arg(args, size_t));
 
-  md5_result(&md5_context, digest);
+  md5_result((MD5_CONTEXT *)&md5_context, digest);
   va_end(args);
 }
 
 size_t my_md5_context_size()
 {
-  return sizeof(MD5_CONTEXT);
+  return MA_HASH_CTX_SIZE;
 }
 
 void my_md5_init(void *context)
