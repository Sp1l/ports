--- SSLeay.xs.orig	2022-01-10 19:05:48 UTC
+++ SSLeay.xs
@@ -6208,7 +6208,8 @@ RSA_generate_key(bits,ee,perl_cb=&PL_sv_undef,perl_dat
         SV* perl_cb
         SV* perl_data
     PREINIT:
-        simple_cb_data_t* cb_data = NULL;
+        
+	simple_cb_data_t* cb_data = NULL;
     CODE:
        /* openssl 0.9.8 deprecated RSA_generate_key. */
        /* This equivalent was contributed by Brian Fraser for Android, */
@@ -6231,7 +6232,7 @@ RSA_generate_key(bits,ee,perl_cb=&PL_sv_undef,perl_dat
 	   BN_free(e);
            croak("Net::SSLeay: RSA_generate_key perl function could not create RSA structure.\n");
        }
-#if (OPENSSL_VERSION_NUMBER >= 0x10100001L && !defined(LIBRESSL_VERSION_NUMBER)) || (LIBRESSL_VERSION_NUMBER >= 0x2070000fL)
+#if (OPENSSL_VERSION_NUMBER >= 0x10100001L && !defined(LIBRESSL_VERSION_NUMBER)) || LIBRESSL_VERSION_NUMBER >= 0x2070000fL
        BN_GENCB *new_cb;
        new_cb = BN_GENCB_new();
        if(!new_cb) {
@@ -6278,7 +6279,8 @@ RSA_generate_key(bits,e,perl_cb=&PL_sv_undef,perl_data
 
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
+	(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000L)
 
 void
 RSA_get_key_parameters(rsa)
@@ -7197,7 +7199,8 @@ ASN1_OBJECT *
 P_X509_get_signature_alg(x)
         X509 * x
     CODE:
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && \
+	!(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000L)
         RETVAL = (X509_get0_tbs_sigalg(x)->algorithm);
 #else
         RETVAL = (x->cert_info->signature->algorithm);
@@ -7690,7 +7693,8 @@ OCSP_response_results(rsp,...)
 		if (!idsv) {
 		    /* getall: create new SV with OCSP_CERTID */
 		    unsigned char *pi,*pc;
-#if OPENSSL_VERSION_NUMBER >= 0x10100003L && !defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER >= 0x10100003L && \
+	!(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000L)
 		    int len = i2d_OCSP_CERTID((OCSP_CERTID *)OCSP_SINGLERESP_get0_id(sir),NULL);
 #else
 		    int len = i2d_OCSP_CERTID(sir->certId,NULL);
@@ -7699,7 +7703,8 @@ OCSP_response_results(rsp,...)
 		    Newx(pc,len,unsigned char);
 		    if (!pc) croak("out of memory");
 		    pi = pc;
-#if OPENSSL_VERSION_NUMBER >= 0x10100003L && !defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER >= 0x10100003L && \
+	!(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x30500000L)
 		    i2d_OCSP_CERTID((OCSP_CERTID *)OCSP_SINGLERESP_get0_id(sir),&pi);
 #else
 		    i2d_OCSP_CERTID(sir->certId,&pi);
