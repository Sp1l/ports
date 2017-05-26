--- sql/mysqld.cc.orig	2017-02-16 08:28:07 UTC
+++ sql/mysqld.cc
@@ -111,6 +111,7 @@
 #endif
 
 #include <my_systemd.h>
+#include <my_crypt.h>
 
 #define mysqld_charset &my_charset_latin1
 
@@ -120,6 +121,7 @@
 #define HAVE_CLOSE_SERVER_SOCK 1
 #endif
 
+
 extern "C" {					// Because of SCO 3.2V4.2
 #include <sys/stat.h>
 #ifndef __GNU_LIBRARY__
@@ -1496,6 +1498,8 @@ scheduler_functions *thread_scheduler= &
 #ifdef HAVE_OPENSSL
 #include <openssl/crypto.h>
 #ifndef HAVE_YASSL
+
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 typedef struct CRYPTO_dynlock_value
 {
   mysql_rwlock_t lock;
@@ -1507,6 +1511,7 @@ static void openssl_dynlock_destroy(open
 static void openssl_lock_function(int, int, const char *, int);
 static void openssl_lock(int, openssl_lock_t *, const char *, int);
 #endif
+#endif
 char *des_key_file;
 #ifndef EMBEDDED_LIBRARY
 struct st_VioSSLFd *ssl_acceptor_fd;
@@ -2325,9 +2330,11 @@ static void clean_up_mutexes()
 #ifdef HAVE_OPENSSL
   mysql_mutex_destroy(&LOCK_des_key_file);
 #ifndef HAVE_YASSL
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
   for (int i= 0; i < CRYPTO_num_locks(); ++i)
     mysql_rwlock_destroy(&openssl_stdlocks[i].lock);
   OPENSSL_free(openssl_stdlocks);
+#endif
 #endif /* HAVE_YASSL */
 #endif /* HAVE_OPENSSL */
 #ifdef HAVE_REPLICATION
@@ -4706,6 +4713,7 @@ static int init_thread_environment()
   mysql_mutex_init(key_LOCK_des_key_file,
                    &LOCK_des_key_file, MY_MUTEX_INIT_FAST);
 #ifndef HAVE_YASSL
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
   openssl_stdlocks= (openssl_lock_t*) OPENSSL_malloc(CRYPTO_num_locks() *
                                                      sizeof(openssl_lock_t));
   for (int i= 0; i < CRYPTO_num_locks(); ++i)
@@ -4716,6 +4724,7 @@ static int init_thread_environment()
   CRYPTO_set_locking_callback(openssl_lock_function);
 #endif
 #endif
+#endif
   mysql_rwlock_init(key_rwlock_LOCK_sys_init_connect, &LOCK_sys_init_connect);
   mysql_rwlock_init(key_rwlock_LOCK_sys_init_slave, &LOCK_sys_init_slave);
   mysql_rwlock_init(key_rwlock_LOCK_grant, &LOCK_grant);
@@ -4750,6 +4759,7 @@ static int init_thread_environment()
 
 
 #if defined(HAVE_OPENSSL) && !defined(HAVE_YASSL)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 static openssl_lock_t *openssl_dynlock_create(const char *file, int line)
 {
   openssl_lock_t *lock= new openssl_lock_t;
@@ -4809,6 +4819,7 @@ static void openssl_lock(int mode, opens
     abort();
   }
 }
+#endif
 #endif /* HAVE_OPENSSL */
 
 
@@ -4838,8 +4849,9 @@ static void init_ssl()
       while ((err= ERR_get_error()))
         sql_print_warning("SSL error: %s", ERR_error_string(err, NULL));
     }
-    else
+    else {
       ERR_remove_state(0);
+    }
   }
   else
   {
