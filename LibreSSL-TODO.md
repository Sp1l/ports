## Types of failures

* EGD -> uses RAND_egd methods that no longer exist in LibreSSL 
* SSLv2 -> Uses SSLv2 methods that no longer exist in LibreSSL 
* PSK -> Uses PSK methods
* DES -> Uses deprecated des_ methods (replaced by DES_ methods)
* CMS -> S/MIME?
* COMP -> Wants SSL compression
* arc4random -> conflict in FreeBSD/LibreSSL libs

Most have been discovered  by the EDGE build of PC-BSD

## TODO

### Uses remopved SSLv2 methods
1. mail/courier
2. security/nessus-libnasl
3. security/sslscan
4. net/pipsecd
5. security/sslwrap
6. misc/linm
7. www/webstone-ssl

### Uses removed EGD methods
1. WIP net-mgmt/xymon-server
3. irc/charybdis
4. russian/ircd-hybrid
5. www/elinks
6. www/links-hacked
7. security/heimdal
9. security/tlswrap
10. lang/pypy3-devel

### Uses removed SSL compression

comms/kermit? error: no member named 'expand' in 'struct ssl_st'

### Uses deprecated des_ methods
1. security/chntpw
1. net-mgmt/ettercap 
1. ftp/pavuk
1. security/hydra
1. security/sectok
2. security/isakmpd
3. deskutils/growl-for-linux
4. sysutils/condor
5. net/gq
6. security/john ???
7. security/ophcrack
8. security/pidentd

### Conflicts with FreeBSD arc4random function
1. sysutils/bacula5-client-static
1. sysutils/bacula-client-static
1. devel/subversion-static
1. sysutils/webjob

### Other
1. net/mosquitto (PSK)
1. security/krb5-111 (CMS)
1. security/krb5-112 (CMS)
1. security/p5-Business-PayPal-EWP (Checks agains OpenSSL version STRING!)
1. security/pond (curve25519, poly1305)
1. dns/knot (GOST overlap)
2. security/softhsm2 (GOST)
1. www/mod_spdy (SSL_CTX_use_certificate_chain overlap -> apache22)
2. mail/opensmtpd-devel conflicting types for 'SSL_CTX_use_certificate_chain'
3. www/tomcat-native conflicting types for 'SSL_CTX_use_certificate_chain'
1. security/tor-devel
2. ? net-p2p/twister (Does not include <openssl/rand.h>)
3. security/openssl_tpm_engine Will that work with LibreSSL at all?
4. security/p5-Crypt-SMIME Hard require OpenSSL-port
5. security/p5-openxpki OPENSSL_PREFIX
6. security/proxytunnel MD5_Final 


## Fixed, needs cleanup for PR and/or upstreaming
1. devel/ice (EGD)
1. devel/dcmtk (EGD)
1. security/opencryptoki (DES)
1. databases/virtuoso (*) NOT BUILD-TESTED!!!
1. irc/unreal (EGD)
1. irc/ircd-ratbox (EGD)
1. irc/ircd-ratbox-devel (EGD)
1. irc/ircd-hybrid (COMP+EGD)
1. irc/znc
1. www/links
1. lang/pypy-devel (patch test only, no build-test!)
1. devel/ace
1. net-mgmt/xymon-server (patched, NOT BUILD-TESTED!!!)

