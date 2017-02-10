--- common/platform.cpp.orig	2017-02-06 15:39:23 UTC
+++ common/platform.cpp
@@ -350,19 +350,23 @@ bool force_buffers_to_disk(const int fd)
 
 void my_readahead(const int fd)
 {
+#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
 	struct stat st;
 
 	if (fstat(fd, &st) == 0)
 		(void)readahead(fd, 0, st.st_size);
+#endif
 }
 
 void give_filesize_hint(const int fd, const off_t len)
 {
+#ifndef __OpenBSD__
 	// this helps preventing filesystem fragmentation as the
 	// kernel can now look for the best disk allocation
 	// pattern as it knows how much date is going to be
 	// inserted
 	posix_fallocate(fd, 0, len);
+#endif
 }
 
 } /* namespace */
