--- Lib/distutils/unixccompiler.py.orig	2014-12-10 15:59:34 UTC
+++ Lib/distutils/unixccompiler.py
@@ -228,6 +228,8 @@ class UnixCCompiler(CCompiler):
         if sys.platform[:6] == "darwin":
             # MacOSX's linker doesn't understand the -R flag at all
             return "-L" + dir
+        elif sys.platform[:7] == "freebsd":
+            return "-Wl,-rpath=" + dir
         elif sys.platform[:5] == "hp-ux":
             if self._is_gcc(compiler):
                 return ["-Wl,+s", "-L" + dir]
