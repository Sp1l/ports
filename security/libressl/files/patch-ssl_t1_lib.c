--- ssl/t1_lib.c.orig   2014-10-11 02:54:57.000000000 +0200
+++ ssl/t1_lib.c        2014-10-16 10:06:19.029340051 +0200
@@ -1,4 +1,4 @@
-/* $OpenBSD: t1_lib.c,v 1.60 2014/10/03 13:58:18 jsing Exp $ */
+/* $OpenBSD: t1_lib.c,v 1.64 2014/10/15 14:02:16 jsing Exp $ */
 /* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
  * All rights reserved.
  *
@@ -458,9 +458,6 @@
        if (ec == NULL)
                return (0);

-       if (EC_KEY_get0_public_key(ec) == NULL)
-               return (0);
-
        /* Determine if it is a prime field. */
        if ((grp = EC_KEY_get0_group(ec)) == NULL)
                return (0);
@@ -484,6 +481,9 @@

        /* Specify the compression identifier. */
        if (comp_id != NULL) {
+               if (EC_KEY_get0_public_key(ec) == NULL)
+                       return (0);
+
                if (EC_KEY_get_conv_form(ec) == POINT_CONVERSION_COMPRESSED) {
                        *comp_id = is_prime ?
                            TLSEXT_ECPOINTFORMAT_ansiX962_compressed_prime :
