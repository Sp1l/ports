--- usr/lib/pkcs11/common/tok_spec_struct.h.orig	2015-12-04 22:06:36 UTC
+++ usr/lib/pkcs11/common/tok_spec_struct.h
@@ -303,10 +303,10 @@
 
 struct token_specific_struct {
 	// Used to be in the token_local.h as a #def
-	CK_BYTE token_directory[PATH_MAX];
+	CK_BYTE *token_directory;
 
 	// Subdirectory
-	CK_BYTE token_subdir[PATH_MAX];
+	CK_BYTE *token_subdir;
 
 	// Set to keysize for secure key tokens
 	int token_keysize;		
