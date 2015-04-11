--- Makefile.PL.orig	2015-04-11 09:17:07 UTC
+++ Makefile.PL
@@ -83,19 +83,22 @@ print STDERR "OpenSSL binary:  $openssl_
 # OpenSSL 0.9.7l 28 Sep 2006
 # OpenSSL 1.0.0a 1 Jun 2010
 my $openssl_version_string = `$openssl_binary version`;
-my ($openssl_version_major, $openssl_version_minor, $openssl_version_fix, $openssl_version_patch);
-if ($openssl_version_string =~ m/\s*OpenSSL\s+(\d+)\.(\d+)\.(\d+)([a-zA-Z]+)/) {
+my ($openssl_version_major, $openssl_version_minor, $openssl_version_fix, $openssl_version_patch, $openssl_version_flavour);
+if ($openssl_version_string =~ m/\s*OpenSSL\s+(\d+)\.(\d+)\.(\d+)([a-zA-Z]+)/i) {
     # OpenSSL 0.9
+    $openssl_version_flavour = 'OpenSSL';
     $openssl_version_major = $1;
     $openssl_version_minor = $2;
     $openssl_version_fix   = $3;
     $openssl_version_patch = $4;
-    print "OpenSSL version: major=$openssl_version_major, minor=$openssl_version_minor, fix=$openssl_version_fix, patch=$openssl_version_patch\n";
-} elsif ($openssl_version_string =~ m/\s*OpenSSL\s+(\d+)\.(\d+)\.(\d+)\s+/) {
+    print "$openssl_version_flavour version: major=$openssl_version_major, minor=$openssl_version_minor, fix=$openssl_version_fix, patch=$openssl_version_patch\n";
+    
+} elsif ($openssl_version_string =~ m/\s*(OpenSSL|LibreSSL)\s+(\d+)\.(\d+)\.(\d+)\s+/) {
     # OpenSSL 1.0
-    $openssl_version_major = $1;
-    $openssl_version_minor = $2;
-    $openssl_version_fix   = $3;
+    $openssl_version_flavour = $1;
+    $openssl_version_major = $2;
+    $openssl_version_minor = $3;
+    $openssl_version_fix   = $4;
     print "OpenSSL version: major=$openssl_version_major, minor=$openssl_version_minor, fix=$openssl_version_fix\n";
 } else {
     print "Problem: malformed openssl version string!\n";
@@ -103,12 +106,22 @@ if ($openssl_version_string =~ m/\s*Open
     exit 1;
 }
 
-# Now make sure version is 0.9.8
-unless ( (($openssl_version_major == 0) &&
-          ($openssl_version_minor == 9) &&
-          ($openssl_version_fix   == 8)) or
-         ($openssl_version_major == 1 &&
-          $openssl_version_minor == 0)) {
+# Warn on old openssl - should work but lacks support for some features 
+if ($openssl_version_major == 0 &&
+    $openssl_version_minor == 9 &&
+    $openssl_version_fix   == 8) {
+
+    print STDERR "Warning: openssl 0.9.8 found - this will work but lacks some features, e.g. server side key generation!";
+              
+} elsif ( $openssl_version_flavour =~ m/LibreSSL/i ) {
+    
+    print STDERR "Warning: LibreSSL found, support for LibreSSL is experimental!";
+    
+} elsif (not 
+    ($openssl_version_flavour =~ m/OpenSSL/i &&
+     $openssl_version_major == 1 &&
+     $openssl_version_minor == 0 )) {
+         
     print STDERR "\n";
     print STDERR "ERROR: OpenSSL 0.9.8  or 1.0 is required.\n";
     print STDERR "Consider setting OPENSSL_PREFIX correctly.\n\n";
@@ -130,7 +143,7 @@ if ( -s '../../VERSION' ) {
     $openxpki_version = `cat ../../VERSION`;
     chomp $openxpki_version;
 } elsif ( -e($vergen) ) {
-    $openxpki_version = `$vergen --format version`;
+    $openxpki_version = "0.27.0";
 
     if ($CHILD_ERROR != 0) {
         $openxpki_version = undef;
