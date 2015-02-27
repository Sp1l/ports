# Types of failures

EGD -> uses RAND_egd methods that no longer exist in LibreSSL 
SSLv2 -> Uses SSLv2 methods that no longer exist in LibreSSL 
PSK -> Uses PSK methods
DES -> Uses deprecated des_ methods (replaced by DES_ methods)

Most have been discovered  by the EDGE build of PC-BSD

# TODO
mail/courier (SSLv2)
security/nessus-libnasl (SSLv2)
devel/dcmtk (EGD)
net/mosquitto (PSK)

# Fixed
irc/unreal (EGD)
devel/ice (EGD)
security/opencryptoki (deprecated des_* methods to DES_)
databases/virtuoso (deprecated des_ methods to DES_*) NOT BUILD-TESTED!!!
