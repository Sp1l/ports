--- modules/ssl/ssl_engine_rand.c.orig  2011-12-05 01:08:01.000000000 +0100
+++ modules/ssl/ssl_engine_rand.c       2014-09-29 10:01:56.288593799 +0200
@@ -81,15 +81,6 @@
                 nDone += ssl_rand_feedfp(p, fp, pRandSeed->nBytes);
                 ssl_util_ppclose(s, p, fp);
             }
-            else if (pRandSeed->nSrc == SSL_RSSRC_EGD) {
-                /*
-                 * seed in contents provided by the external
-                 * Entropy Gathering Daemon (EGD)
-                 */
-                if ((n = RAND_egd(pRandSeed->cpPath)) == -1)
-                    continue;
-                nDone += n;
-            }
             else if (pRandSeed->nSrc == SSL_RSSRC_BUILTIN) {
                 struct {
                     time_t t;
