Committed upstream https://github.com/bagder/curl/commit/e400a89b18

--- docs/examples/getredirect.c.orig	2016-01-14 15:37:49 UTC
+++ docs/examples/getredirect.c
@@ -48,7 +48,7 @@ int main(void)
     else {
       res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
       if((res == CURLE_OK) &&
-         ((code / 100) != 3)) {
+         ((response_code / 100) != 3)) {
         /* a redirect implies a 3xx response code */
         fprintf(stderr, "Not a redirect.\n");
       }
