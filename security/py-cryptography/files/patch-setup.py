--- setup.py.orig	2022-03-15 21:36:12 UTC
+++ setup.py
@@ -10,23 +10,7 @@ import sys
 
 from setuptools import setup
 
-try:
-    from setuptools_rust import RustExtension
-except ImportError:
-    print(
-        """
-        =============================DEBUG ASSISTANCE==========================
-        If you are seeing an error here please try the following to
-        successfully install cryptography:
 
-        Upgrade to the latest pip and try again. This will fix errors for most
-        users. See: https://pip.pypa.io/en/stable/installing/#upgrading-pip
-        =============================DEBUG ASSISTANCE==========================
-        """
-    )
-    raise
-
-
 base_dir = os.path.dirname(__file__)
 src_dir = os.path.join(base_dir, "src")
 
@@ -40,20 +24,6 @@ try:
         cffi_modules=[
             "src/_cffi_src/build_openssl.py:ffi",
         ],
-        rust_extensions=[
-            RustExtension(
-                "_rust",
-                "src/rust/Cargo.toml",
-                py_limited_api=True,
-                # Enable abi3 mode if we're not using PyPy.
-                features=(
-                    []
-                    if platform.python_implementation() == "PyPy"
-                    else ["pyo3/abi3-py36"]
-                ),
-                rust_version=">=1.41.0",
-            )
-        ],
     )
 except:  # noqa: E722
     # Note: This is a bare exception that re-raises so that we don't interfere
@@ -83,7 +53,7 @@ except:  # noqa: E722
     )
     print(f"    Python: {'.'.join(str(v) for v in sys.version_info[:3])}")
     print(f"    platform: {platform.platform()}")
-    for dist in ["pip", "setuptools", "setuptools_rust"]:
+    for dist in ["pip", "setuptools"]:
         try:
             version = pkg_resources.get_distribution(dist).version
         except pkg_resources.DistributionNotFound:
