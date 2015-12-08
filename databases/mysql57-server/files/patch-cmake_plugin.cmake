--- cmake/plugin.cmake.orig	2015-10-12 09:51:33.000000000 +0330
+++ cmake/plugin.cmake	2015-11-29 01:11:43.000000000 +0330
@@ -236,9 +236,6 @@
     MYSQL_INSTALL_TARGETS(${target}
       DESTINATION ${INSTALL_PLUGINDIR}
       COMPONENT ${INSTALL_COMPONENT})
-    INSTALL_DEBUG_TARGET(${target}
-      DESTINATION ${INSTALL_PLUGINDIR}/debug
-      COMPONENT ${INSTALL_COMPONENT})
     # Add installed files to list for RPMs
     FILE(APPEND ${CMAKE_BINARY_DIR}/support-files/plugins.files
             "%attr(755, root, root) %{_prefix}/${INSTALL_PLUGINDIR}/${ARG_MODULE_OUTPUT_NAME}.so\n"
