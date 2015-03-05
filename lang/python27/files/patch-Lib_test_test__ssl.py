--- Lib/test/test_ssl.py.orig	2014-12-10 15:59:47 UTC
+++ Lib/test/test_ssl.py
@@ -169,8 +169,12 @@ class BasicSocketTests(unittest.TestCase
             sys.stdout.write("\n RAND_status is %d (%s)\n"
                              % (v, (v and "sufficient randomness") or
                                 "insufficient randomness"))
-        self.assertRaises(TypeError, ssl.RAND_egd, 1)
-        self.assertRaises(TypeError, ssl.RAND_egd, 'foo', 1)
+### Fix build with LibreSSL (does not have RAND_egd)
+### PR192511, http://bugs.python.org/issue21356        
+        if hasattr(ssl, 'RAND_egd'):
+            self.assertRaises(TypeError, ssl.RAND_egd, 1)
+            self.assertRaises(TypeError, ssl.RAND_egd, 'foo', 1)
+### End PR192511
         ssl.RAND_add("this is a random string", 75.0)
 
     def test_parse_cert(self):
