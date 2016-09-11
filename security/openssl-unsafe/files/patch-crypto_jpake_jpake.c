--- crypto/jpake/jpake.c.orig	2016-08-22 09:21:00.000000000 +0200
+++ crypto/jpake/jpake.c	2016-09-11 14:01:24.931692000 +0200
@@ -154,7 +154,7 @@ static void hashbn(SHA_CTX *sha, const B
     unsigned char *bin = OPENSSL_malloc(l);
 
     if (bin == NULL)
-        return NULL;
+        return;
     hashlength(sha, l);
     BN_bn2bin(bn, bin);
     SHA1_Update(sha, bin, l);
