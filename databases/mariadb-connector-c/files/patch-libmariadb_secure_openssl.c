--- libmariadb/secure/openssl.c.orig	2017-01-17 12:23:34 UTC
+++ libmariadb/secure/openssl.c
@@ -53,7 +53,7 @@ extern unsigned int mariadb_deinitialize
 #define MAX_SSL_ERR_LEN 100
 
 static pthread_mutex_t LOCK_openssl_config;
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 static pthread_mutex_t *LOCK_crypto= NULL;
 #endif
 #if OPENSSL_USE_BIOMETHOD
@@ -85,14 +85,13 @@ static void ma_tls_set_error(MYSQL *mysq
   return;
 }
 
-
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 /* 
    thread safe callbacks for OpenSSL 
    Crypto call back functions will be
    set during ssl_initialization
  */
-#if OPENSSL_VERSION_NUMBER < 0x10000000L
+#if OPENSSL_VERSION_NUMBER < 0x10000000L || defined(LIBRESSL_VERSION_NUMBER)
 static unsigned long my_cb_threadid(void)
 {
   /* cast pthread_t to unsigned long */
@@ -209,7 +208,7 @@ static void ma_tls_remove_session_cb(SSL
 }
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 static void my_cb_locking(int mode, int n, 
                           const char *file __attribute__((unused)),
                           int line __attribute__((unused)))
@@ -287,7 +286,7 @@ int ma_tls_start(char *errmsg __attribut
   /* lock mutex to prevent multiple initialization */
   pthread_mutex_init(&LOCK_openssl_config, NULL);
   pthread_mutex_lock(&LOCK_openssl_config);
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
   if (!OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL))
     goto end;
 #else
@@ -669,7 +668,7 @@ int ma_tls_verify_server_cert(MARIADB_TL
   if (!(cn_asn1 = X509_NAME_ENTRY_get_data(cn_entry)))
     goto error;
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
   cn_str = (char *)ASN1_STRING_data(cn_asn1);
 #else
   cn_str = (char *)ASN1_STRING_get0_data(cn_asn1);
