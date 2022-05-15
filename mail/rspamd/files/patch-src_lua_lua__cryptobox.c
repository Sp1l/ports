--- src/lua/lua_cryptobox.c.orig	2022-03-26 12:23:26 UTC
+++ src/lua/lua_cryptobox.c
@@ -1001,7 +1001,8 @@ lua_cryptobox_hash_dtor (struct rspamd_lua_cryptobox_h
 		EVP_MD_CTX_destroy (h->content.c);
 	}
 	else if (h->type == LUA_CRYPTOBOX_HASH_HMAC) {
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000)
 		HMAC_CTX_cleanup (h->content.hmac_c);
 		g_free (h->content.hmac_c);
 #else
@@ -1059,7 +1060,8 @@ rspamd_lua_ssl_hmac_create (struct rspamd_lua_cryptobo
 {
 	h->type = LUA_CRYPTOBOX_HASH_HMAC;
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000)
 	h->content.hmac_c = g_malloc0 (sizeof(*h->content.hmac_c));
 #else
 	h->content.hmac_c = HMAC_CTX_new ();
@@ -1461,7 +1463,8 @@ lua_cryptobox_hash_reset (lua_State *L)
 			EVP_DigestInit (h->content.c, EVP_MD_CTX_md (h->content.c));
 			break;
 		case LUA_CRYPTOBOX_HASH_HMAC:
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000)
 			/* Old openssl is awesome... */
 			HMAC_Init_ex (h->content.hmac_c, NULL, 0, h->content.hmac_c->md, NULL);
 #else
