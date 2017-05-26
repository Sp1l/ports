--- mysys_ssl/my_crypt.cc.orig	2017-02-16 08:28:07 UTC
+++ mysys_ssl/my_crypt.cc
@@ -17,7 +17,6 @@
 
 #include <my_global.h>
 #include <string.h>
-#include <my_crypt.h>
 
 #ifdef HAVE_YASSL
 #include "yassl.cc"
@@ -26,43 +25,51 @@
 #include <openssl/evp.h>
 #include <openssl/aes.h>
 #include <openssl/err.h>
+#include <openssl/rand.h>
 
-#ifdef HAVE_ERR_remove_thread_state
-#define ERR_remove_state(X) ERR_remove_thread_state(NULL)
 #endif
+#include <my_crypt.h>
 
-#endif
+#define MY_CIPHER_CTX_SIZE 384
 
 class MyCTX
 {
 public:
-  EVP_CIPHER_CTX ctx;
-  MyCTX() { EVP_CIPHER_CTX_init(&ctx); }
-  virtual ~MyCTX() { EVP_CIPHER_CTX_cleanup(&ctx); ERR_remove_state(0); }
+  EVP_CIPHER_CTX *ctx;
+  const uchar *key;
+  unsigned int klen;
+  MyCTX() {
+            ctx= EVP_CIPHER_CTX_new();
+          }
+  virtual ~MyCTX() {
+                     EVP_CIPHER_CTX_free(ctx);
+                     ERR_remove_state(0);
+                    }
 
   virtual int init(const EVP_CIPHER *cipher, int encrypt, const uchar *key,
                    uint klen, const uchar *iv, uint ivlen)
   {
+    compile_time_assert(MY_AES_CTX_SIZE >= sizeof(MyCTX));
     if (unlikely(!cipher))
       return MY_AES_BAD_KEYSIZE;
 
-    if (!EVP_CipherInit_ex(&ctx, cipher, NULL, key, iv, encrypt))
+    if (!EVP_CipherInit_ex(ctx, cipher, NULL, key, iv, encrypt))
       return MY_AES_OPENSSL_ERROR;
 
-    DBUG_ASSERT(EVP_CIPHER_CTX_key_length(&ctx) == (int)klen);
-    DBUG_ASSERT(EVP_CIPHER_CTX_iv_length(&ctx) <= (int)ivlen);
+    DBUG_ASSERT(EVP_CIPHER_CTX_key_length(ctx) == (int)klen);
+    DBUG_ASSERT(EVP_CIPHER_CTX_iv_length(ctx) <= (int)ivlen);
 
     return MY_AES_OK;
   }
   virtual int update(const uchar *src, uint slen, uchar *dst, uint *dlen)
   {
-    if (!EVP_CipherUpdate(&ctx, dst, (int*)dlen, src, slen))
+    if (!EVP_CipherUpdate(ctx, dst, (int*)dlen, src, slen))
       return MY_AES_OPENSSL_ERROR;
     return MY_AES_OK;
   }
   virtual int finish(uchar *dst, uint *dlen)
   {
-    if (!EVP_CipherFinal_ex(&ctx, dst, (int*)dlen))
+    if (!EVP_CipherFinal_ex(ctx, dst, (int*)dlen))
       return MY_AES_BAD_DATA;
     return MY_AES_OK;
   }
@@ -71,11 +78,9 @@ public:
 class MyCTX_nopad : public MyCTX
 {
 public:
-  const uchar *key;
-  int klen;
-
   MyCTX_nopad() : MyCTX() { }
   ~MyCTX_nopad() { }
+  unsigned int buf_len;
 
   int init(const EVP_CIPHER *cipher, int encrypt, const uchar *key, uint klen,
            const uchar *iv, uint ivlen)
@@ -83,16 +88,39 @@ public:
     compile_time_assert(MY_AES_CTX_SIZE >= sizeof(MyCTX_nopad));
     this->key= key;
     this->klen= klen;
+    this->buf_len= 0;
+    /* FIX-ME:
+       For the sake of backward compatibility we do some strange hack here:
+       Since ECB doesn't need an IV (and therefore is considered kind of
+       insecure) we need to store the specified iv.
+       The last nonpadding block will be encrypted with an additional
+       expensive crypt_call in ctr mode instead
+       of encrypting the entire plain text in ctr-mode */
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
+    const unsigned char *oiv= EVP_CIPHER_CTX_original_iv(ctx);
+#else
+    const unsigned char *oiv= ctx->oiv;
+#endif
+    memcpy((char *)oiv, iv, ivlen);
+
     int res= MyCTX::init(cipher, encrypt, key, klen, iv, ivlen);
-    memcpy(ctx.oiv, iv, ivlen); // in ECB mode OpenSSL doesn't do that itself
-    EVP_CIPHER_CTX_set_padding(&ctx, 0);
+
+    EVP_CIPHER_CTX_set_padding(ctx, 0);
     return res;
   }
 
+  int update(const uchar *src, uint slen, uchar *dst, uint *dlen)
+  {
+    buf_len= slen % MY_AES_BLOCK_SIZE;
+    return MyCTX::update(src, slen, dst, dlen);
+  }
+
   int finish(uchar *dst, uint *dlen)
   {
-    if (ctx.buf_len)
+    if (buf_len)
     {
+      const uchar *org_iv;
+      unsigned char *buf;
       /*
         Not much we can do, block ciphers cannot encrypt data that aren't
         a multiple of the block length. At least not without padding.
@@ -101,14 +129,22 @@ public:
       uchar mask[MY_AES_BLOCK_SIZE];
       uint mlen;
 
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
+      org_iv= EVP_CIPHER_CTX_original_iv(ctx);
+      buf= EVP_CIPHER_CTX_buf_noconst(ctx);
+#else
+      org_iv= ctx->oiv;
+      buf= ctx->buf;
+#endif
+
       my_aes_crypt(MY_AES_ECB, ENCRYPTION_FLAG_ENCRYPT | ENCRYPTION_FLAG_NOPAD,
-                   ctx.oiv, sizeof(mask), mask, &mlen, key, klen, 0, 0);
+                   org_iv, sizeof(mask), mask, &mlen, key, klen, 0, 0);
       DBUG_ASSERT(mlen == sizeof(mask));
 
-      for (int i=0; i < ctx.buf_len; i++)
-        dst[i]= ctx.buf[i] ^ mask[i];
+      for (uint i=0; i < buf_len; i++)
+        dst[i]= buf[i] ^ mask[i];
     }
-    *dlen= ctx.buf_len;
+    *dlen= buf_len;
     return MY_AES_OK;
   }
 };
@@ -142,8 +178,9 @@ make_aes_dispatcher(gcm)
 class MyCTX_gcm : public MyCTX
 {
 public:
-  const uchar *aad;
+  const uchar *aad= NULL;
   int aadlen;
+  my_bool encrypt;
   MyCTX_gcm() : MyCTX() { }
   ~MyCTX_gcm() { }
 
@@ -152,9 +189,10 @@ public:
   {
     compile_time_assert(MY_AES_CTX_SIZE >= sizeof(MyCTX_gcm));
     int res= MyCTX::init(cipher, encrypt, key, klen, iv, ivlen);
-    int real_ivlen= EVP_CIPHER_CTX_iv_length(&ctx);
+    int real_ivlen= EVP_CIPHER_CTX_iv_length(ctx);
     aad= iv + real_ivlen;
     aadlen= ivlen - real_ivlen;
+    this->encrypt= encrypt;
     return res;
   }
 
@@ -166,18 +204,18 @@ public:
       before decrypting the data. it can encrypt data piecewise, like, first
       half, then the second half, but it must decrypt all at once
     */
-    if (!ctx.encrypt)
+    if (!this->encrypt)
     {
       /* encrypted string must contain authenticaton tag (see MDEV-11174) */
       if (slen < MY_AES_BLOCK_SIZE)
         return MY_AES_BAD_DATA;
       slen-= MY_AES_BLOCK_SIZE;
-      if(!EVP_CIPHER_CTX_ctrl(&ctx, EVP_CTRL_GCM_SET_TAG, MY_AES_BLOCK_SIZE,
+      if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, MY_AES_BLOCK_SIZE,
                               (void*)(src + slen)))
         return MY_AES_OPENSSL_ERROR;
     }
-    int unused;
-    if (aadlen && !EVP_CipherUpdate(&ctx, NULL, &unused, aad, aadlen))
+    int unused= 0;
+    if (aadlen && !EVP_CipherUpdate(ctx, NULL, &unused, aad, aadlen))
       return MY_AES_OPENSSL_ERROR;
     aadlen= 0;
     return MyCTX::update(src, slen, dst, dlen);
@@ -185,14 +223,14 @@ public:
 
   int finish(uchar *dst, uint *dlen)
   {
-    int fin;
-    if (!EVP_CipherFinal_ex(&ctx, dst, &fin))
+    int fin= 0;
+    if (!EVP_CipherFinal_ex(ctx, dst, &fin))
       return MY_AES_BAD_DATA;
     DBUG_ASSERT(fin == 0);
 
-    if (ctx.encrypt)
+    if (this->encrypt)
     {
-      if(!EVP_CIPHER_CTX_ctrl(&ctx, EVP_CTRL_GCM_GET_TAG, MY_AES_BLOCK_SIZE, dst))
+      if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, MY_AES_BLOCK_SIZE, dst))
         return MY_AES_OPENSSL_ERROR;
       *dlen= MY_AES_BLOCK_SIZE;
     }
@@ -260,12 +298,20 @@ int my_aes_crypt(enum my_aes_mode mode, 
 {
   void *ctx= alloca(MY_AES_CTX_SIZE);
   int res1, res2;
-  uint d1, d2;
+  uint d1= 0, d2= 0;
   if ((res1= my_aes_crypt_init(ctx, mode, flags, key, klen, iv, ivlen)))
     return res1;
   res1= my_aes_crypt_update(ctx, src, slen, dst, &d1);
   res2= my_aes_crypt_finish(ctx, dst + d1, &d2);
   *dlen= d1 + d2;
+  /* in case of failure clear error queue */
+#ifndef HAVE_YASSL
+  /* since we don't check the crypto error messages we need to
+     clear the error queue - otherwise subsequent crypto or tls/ssl
+     calls will fail */
+  if (!*dlen)
+    ERR_clear_error();
+#endif
   return res1 ? res1 : res2;
 }
 
@@ -278,7 +324,6 @@ int my_random_bytes(uchar* buf, int num)
   return MY_AES_OK;
 }
 #else
-#include <openssl/rand.h>
 
 int my_random_bytes(uchar *buf, int num)
 {
@@ -288,7 +333,7 @@ int my_random_bytes(uchar *buf, int num)
     instead of whatever random engine is currently set in OpenSSL. That way
     we are guaranteed to have a non-blocking random.
   */
-  RAND_METHOD *rand = RAND_SSLeay();
+  RAND_METHOD *rand = RAND_OpenSSL();
   if (rand == NULL || rand->bytes(buf, num) != 1)
     return MY_AES_OPENSSL_ERROR;
   return MY_AES_OK;
