--- Lib/distutils/command/build_scripts.py.orig	2014-12-10 15:59:34 UTC
+++ Lib/distutils/command/build_scripts.py
@@ -126,6 +126,9 @@ class build_scripts (Command):
                                  file, oldmode, newmode)
                         os.chmod(file, newmode)
 
+        # XXX should we modify self.outfiles?
+        return outfiles
+
     # copy_scripts ()
 
 # class build_scripts
