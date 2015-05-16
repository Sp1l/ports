--- src/main.c.orig	2010-07-26 07:21:19 UTC
+++ src/main.c
@@ -472,7 +472,9 @@ int main( int argc, char *argv[] )
 	    ssl_thread_setup(fn);
 	    
             /* Need to seed PRNG, too! */
+#ifdef HAVE_RAND_EGD
             if ( RAND_egd( ( RAND_file_name( f_randfile, sizeof( f_randfile ) ) == f_randfile ) ? f_randfile : "/.rnd" ) ) 
+#endif
 	    {
                 /* Not an EGD, so read and write it. */
                 if ( RAND_load_file( f_randfile, -1 ) )
