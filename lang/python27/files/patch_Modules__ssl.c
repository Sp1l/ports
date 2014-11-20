--- ./Modules/_ssl.c.orig       2014-06-30 04:05:42.000000000 +0200
+++ ./Modules/_ssl.c            2014-08-07 11:58:48.000000000 +0200
@@ -1604,20 +1604,11 @@
 static PyObject *
 PySSL_RAND_egd(PyObject *self, PyObject *arg)
 {
-    int bytes;
-
-    if (!PyString_Check(arg))
-        return PyErr_Format(PyExc_TypeError,
-                            "RAND_egd() expected string, found %s",
-                            Py_TYPE(arg)->tp_name);
-    bytes = RAND_egd(PyString_AS_STRING(arg));
-    if (bytes == -1) {
-        PyErr_SetString(PySSLErrorObject,
-                        "EGD connection failed or EGD did not return "
-                        "enough data to seed the PRNG");
-        return NULL;
-    }
-    return PyInt_FromLong(bytes);
+
+  PyErr_SetString(PySSLErrorObject,
+                 "EGD connection failed or EGD did not return "
+                 "enough data to seed the PRNG");
+  return NULL;
 }

 PyDoc_STRVAR(PySSL_RAND_egd_doc,
