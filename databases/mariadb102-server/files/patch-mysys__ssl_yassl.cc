--- mysys_ssl/yassl.cc.orig	2017-02-16 08:28:07 UTC
+++ mysys_ssl/yassl.cc
@@ -24,6 +24,7 @@
 
 #include <openssl/ssl.h>
 #include "aes.hpp"
+#include <my_sys.h>
 
 using yaSSL::yaERR_remove_state;
 
@@ -75,12 +76,26 @@ static void EVP_CIPHER_CTX_init(EVP_CIPH
   ctx->final_used= ctx->buf_len= ctx->flags= 0;
 }
 
+static EVP_CIPHER_CTX *EVP_CIPHER_CTX_new()
+{
+  EVP_CIPHER_CTX *ctx= (EVP_CIPHER_CTX *)my_malloc(sizeof(EVP_CIPHER_CTX), MYF(0));
+  if (ctx)
+    EVP_CIPHER_CTX_init(ctx);
+  return ctx;
+}
+
 static int EVP_CIPHER_CTX_cleanup(EVP_CIPHER_CTX *ctx)
 {
   TAO(ctx)->~AES();
   return 1;
 }
 
+static void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *ctx)
+{
+  EVP_CIPHER_CTX_cleanup(ctx);
+  my_free(ctx);
+}
+
 static int EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX *ctx, int pad)
 {
   if (pad)
