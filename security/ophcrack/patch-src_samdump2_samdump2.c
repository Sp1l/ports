--- src/samdump2/samdump2.c.orig	2015-02-28 16:01:54.751900000 +0100
+++ src/samdump2/samdump2.c	2015-02-28 16:08:38.049462876 +0100
@@ -71,7 +71,7 @@
 	for (i=0;i<8;i++) {
 		key[i] = (key[i]<<1);
 	}
-	des_set_odd_parity((des_cblock *)key);
+	DES_set_odd_parity((DES_cblock *)key);
 }
 
 /*
@@ -209,8 +209,8 @@
   unsigned char hbootkey[0x20];
   
   /* Des */
-  des_key_schedule ks1, ks2;
-  des_cblock deskey1, deskey2;
+  DES_key_schedule ks1, ks2;
+  DES_cblock deskey1, deskey2;
   
   int i, j;
   
@@ -418,15 +418,15 @@
       
       /* Get the two decrpt keys. */
       sid_to_key1(rid,(unsigned char *)deskey1);
-      des_set_key_checked((des_cblock *)deskey1,ks1);
+      DES_set_key_checked((DES_cblock *)deskey1,&ks1);
       sid_to_key2(rid,(unsigned char *)deskey2);
-      des_set_key_unchecked((des_cblock *)deskey2,ks2);
+      DES_set_key_unchecked((DES_cblock *)deskey2,&ks2);
       
       /* Decrypt the lanman password hash as two 8 byte blocks. */
-      des_ecb_encrypt((des_cblock *)obfkey,
-		      (des_cblock *)fb, ks1, DES_DECRYPT);
-      des_ecb_encrypt((des_cblock *)(obfkey + 8),
-		      (des_cblock *)&fb[8], ks2, DES_DECRYPT);
+      DES_ecb_encrypt((DES_cblock *)obfkey,
+		      (DES_cblock *)fb, &ks1, DES_DECRYPT);
+      DES_ecb_encrypt((DES_cblock *)(obfkey + 8),
+		      (DES_cblock *)&fb[8], &ks2, DES_DECRYPT);
       
       
       
@@ -471,16 +471,16 @@
       if (lm_size != 0x14) {
 	/* Get the two decrpt keys. */
 	sid_to_key1(rid,(unsigned char *)deskey1);
-	des_set_key((des_cblock *)deskey1,ks1);
+	DES_set_key((DES_cblock *)deskey1,&ks1);
 	sid_to_key2(rid,(unsigned char *)deskey2);
-	des_set_key((des_cblock *)deskey2,ks2);
+	DES_set_key((DES_cblock *)deskey2,&ks2);
       }
 
       /* Decrypt the NT md4 password hash as two 8 byte blocks. */
-      des_ecb_encrypt((des_cblock *)obfkey,
-		      (des_cblock *)fb, ks1, DES_DECRYPT);
-      des_ecb_encrypt((des_cblock *)(obfkey + 8),
-		      (des_cblock *)&fb[8], ks2, DES_DECRYPT);
+      DES_ecb_encrypt((DES_cblock *)obfkey,
+		      (DES_cblock *)fb, &ks1, DES_DECRYPT);
+      DES_ecb_encrypt((DES_cblock *)(obfkey + 8),
+		      (DES_cblock *)&fb[8], &ks2, DES_DECRYPT);
       
       /* sf27 wrap to sf25 */
       //sf27( obfkey, (int*)&rid, fb );
