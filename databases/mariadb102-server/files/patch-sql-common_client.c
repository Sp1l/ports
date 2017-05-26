--- sql-common/client.c.orig	2017-02-16 08:28:07 UTC
+++ sql-common/client.c
@@ -104,6 +104,10 @@ my_bool	net_flush(NET *net);
 #define CONNECT_TIMEOUT 0
 #endif
 
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER) || defined(HAVE_YASSL)
+#define ASN1_STRING_get0_data(X) ASN1_STRING_data(X)
+#endif
+
 #include "client_settings.h"
 #include <sql_common.h>
 #include <mysql/client_plugin.h>
@@ -1842,7 +1846,7 @@ static int ssl_verify_server_cert(Vio *v
     goto error;
   }
 
-  cn= (char *) ASN1_STRING_data(cn_asn1);
+  cn= (char *) ASN1_STRING_get0_data(cn_asn1);
 
   if ((size_t)ASN1_STRING_length(cn_asn1) != strlen(cn))
   {
