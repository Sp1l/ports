--- plugins/auth/gssapi_errmsg.c.orig	2017-01-17 12:23:34 UTC
+++ plugins/auth/gssapi_errmsg.c
@@ -26,7 +26,7 @@ ARISING IN ANY WAY OUT OF THE USE OF THI
 POSSIBILITY OF SUCH DAMAGE.
 */
 
-#include <gssapi.h>
+#include <gssapi/gssapi.h>
 #include <string.h>
 void gssapi_errmsg(OM_uint32 major, OM_uint32 minor, char *buf, size_t size)
 {
