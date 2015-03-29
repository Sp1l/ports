--- libtorrent/include/libtorrent/pe_crypto.hpp.orig	2014-11-29 15:20:43 UTC
+++ libtorrent/include/libtorrent/pe_crypto.hpp
@@ -43,6 +43,7 @@ POSSIBILITY OF SUCH DAMAGE.
 #include <openssl/rc4.h>
 #include <openssl/evp.h>
 #include <openssl/aes.h>
+#include <openssl/rand.h>
 #else
 // RC4 state from libtomcrypt
 struct rc4 {
