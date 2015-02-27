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

### Uses removed EGD methods

WIP net-mgmt/xymon-server

? net-p2p/twister (RAND_add...?)

### Uses removed SSL compression

comms/kermit? error: no member named 'expand' in 'struct ssl_st'

### Uses deprecated des_ methods
1. security/chntpw
1. net-mgmt/ettercap 
1. ftp/pavuk
1. security/hydra
1. security/sectok

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
1. www/mod_spdy (SSL_CTX_use_certificate_chain overlap -> apache22)
1. security/tor-devel

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

