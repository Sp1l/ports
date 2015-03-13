--- Modules/_ssl.c.orig	2014-12-10 15:59:53 UTC
+++ Modules/_ssl.c
@@ -3301,6 +3301,7 @@ Returns 1 if the OpenSSL PRNG has been s
 It is necessary to seed the PRNG with RAND_add() on some platforms before\n\
 using the ssl() function.");
 
+#ifdef HAVE_RAND_EGD
 static PyObject *
 PySSL_RAND_egd(PyObject *self, PyObject *arg)
 {
@@ -3326,6 +3327,7 @@ PyDoc_STRVAR(PySSL_RAND_egd_doc,
 Queries the entropy gather daemon (EGD) on the socket named by 'path'.\n\
 Returns number of bytes read.  Raises SSLError if connection to EGD\n\
 fails or if it does not provide enough data to seed PRNG.");
+#endif /* HAVE_RAND_EGD */
 
 #endif /* HAVE_OPENSSL_RAND */
 
@@ -3720,8 +3722,10 @@ static PyMethodDef PySSL_methods[] = {
 #ifdef HAVE_OPENSSL_RAND
     {"RAND_add",            PySSL_RAND_add, METH_VARARGS,
      PySSL_RAND_add_doc},
+#ifdef HAVE_RAND_EGD
     {"RAND_egd",            PySSL_RAND_egd, METH_VARARGS,
      PySSL_RAND_egd_doc},
+#endif /* HAVE_RAND_EGD */
     {"RAND_status",         (PyCFunction)PySSL_RAND_status, METH_NOARGS,
      PySSL_RAND_status_doc},
 #endif
