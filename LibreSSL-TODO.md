## Types of failures

EGD -> uses RAND_egd methods that no longer exist in LibreSSL 

SSLv2 -> Uses SSLv2 methods that no longer exist in LibreSSL 

PSK -> Uses PSK methods

DES -> Uses deprecated des_ methods (replaced by DES_ methods)

CMS -> S/MIME?

COMP -> Wants SSL compression

arc4random -> conflict in FreeBSD/LibreSSL libs

Most have been discovered  by the EDGE build of PC-BSD

## TODO

### Uses remopved SSLv2 methods
mail/courier (SSLv2)

security/nessus-libnasl (SSLv2)

sslscan/work

### Uses removed EGD methods

lang/pypy-devel

devel/ace

net-mgmt/xymon-server

? net-p2p/twister (RAND_add...?)

### Uses removed SSL compression

comms/kermit? error: no member named 'expand' in 'struct ssl_st'

### Uses deprecated des_ methods
security/chntpw (DES_)

net-mgmt/ettercap 

ftp/pavuk

security/hydra

security/sectok

### Conflicts with FreeBSD arc4random function
sysutils/bacula5-client-static (arc4)

sysutils/bacula-client-static

devel/subversion-static (arc4)

sysutils/webjob

### Other
net/mosquitto (PSK)

security/krb5-111 (CMS)

security/krb5-112 (CMS)

security/p5-Business-PayPal-EWP (Checks agains OpenSSL version STRING!)

security/pond (curve25519, poly1305)

dns/knot (GOST overlap)

www/mod_spdy (SSL_CTX_use_certificate_chain overlap -> apache22)

security/tor-devel

## Fixed
irc/unreal (EGD)

devel/ice (EGD)

devel/dcmtk (EGD)

security/opencryptoki (deprecated des_* methods to DES_)

databases/virtuoso (deprecated des_ methods to DES_*) NOT BUILD-TESTED!!!

irc/ircd-ratbox (EGD)

irc/ircd-ratbox-devel (EGD)

irc/ircd-hybrid (COMP+EGD)

irc/znc

www/links


