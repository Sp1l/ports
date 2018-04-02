# $FreeBSD: head/www/apache24/Makefile 450116 2017-09-19 12:21:17Z zi $

PORTNAME=	apache
PORTVERSION=	2.5.1.20180330
MASTER_SITES=	https://dist.apache.org/repos/dist/dev/httpd/
CATEGORIES=	www ipv6
DISTNAME=	httpd-${DISTVERSION}
PKGNAMESUFFIX=	25-devel

MAINTAINER=	apache@FreeBSD.org
COMMENT=	Version 2.5.x of Apache web server

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libexpat.so:textproc/expat2 \
		libapr-1.so:devel/apr1 \
		libpcre.so:devel/pcre

CONFLICTS_INSTALL=	caudium14-* apache22-2* apache24-2*

USES=		apache:server,2.6 autoreconf cpe gmake iconv libtool perl5 tar:bzip2
USE_PERL5=	run
USE_RC_SUBR=	apache25 htcacheclean
GNU_CONFIGURE=	yes

CPE_VENDOR=	apache
CPE_PRODUCT=	http_server

PORTDOCS=	*
SUB_FILES=	pkg-install pkg-deinstall

# Fallback MPM after switching from static to modular MPM
SUB_LIST+=	MPMF="000_mpm_prefork_fallback.conf"

USERS=		www
GROUPS=		www

WITH_HTTP_PORT?=	80
WITH_SSL_PORT?=		443

USE_GITHUB=	yes
GH_PROJECT=	httpd
GH_TAGNAME=	02dc1ff

.if !defined(WITH_DEBUG)
#EXTRA_PATCHES+=	${FILESDIR}/extra-patch-server_buildmark.c
.endif

.include "./Makefile.options"
.include "./Makefile.options.desc"
OPTIONS_SUB=	yes

SERF_BROKEN=	mod_serf requires serf-0 where we have serf-1

# http://httpd.apache.org/docs/2.4/bind.html
IPV4_MAPPED_CONFIGURE_ENABLE=	v4-mapped

BROTLI_CONFIGURE_WITH=		brotli=${LOCALBASE}
AUTHNZ_LDAP_CONFIGURE_ENABLE=	authnz-ldap
AUTHNZ_LDAP_USE=		openldap=yes
BROTLI_LIB_DEPENDS=		libbrotlicommon.so:archivers/brotli
HTTP2_CONFIGURE_WITH=		nghttp2=${LOCALBASE}
HTTP2_LIB_DEPENDS=		libnghttp2.so:www/libnghttp2
LDAP_CONFIGURE_ENABLE=		ldap=shared
LDAP_USE=			openldap=yes
LUAJIT_LIB_DEPENDS=		libluajit-5.1.so:lang/luajit
LUA_CONFIGURE_ENV=		LUA_CFLAGS="-I${LUA_INCDIR}" \
				LUA_LIBS="-L${LUA_LIBDIR} -llua-${LUA_VER}"
LUA_CONFIGURE_WITH=		lua=${PREFIX}
LUA_USES=			lua
MD_CONFIGURE_WITH=		jansson=${LOCALBASE} curl=${LOCALBASE}
MD_LIB_DEPENDS=			libcurl.so:ftp/curl \
				libjansson.so:devel/jansson
.for mod in event motorz prefork simple worker
MPM_${mod:tu}_CONFIGURE_ON=	--with-mpm=${mod}
.endfor
MPM_SHARED_CONFIGURE_ON=	--enable-mpms-shared=all
PROXY_HTML_USE=			gnome=libxml2
PROXY_HTML_CONFIGURE_WITH=	libxml2=${LOCALBASE}/include/libxml2
PROXY_HTTP2_CONFIGURE_WITH=	${HTTP2_CONFIGURE_WITH}
PROXY_HTTP2_LIB_DEPENDS=	${HTTP2_LIB_DEPENDS}
SERF_CONFIGURE_WITH=		serf=${LOCALBASE}
SERF_LIB_DEPENDS=		libserf-1.so:www/serf
SOCACHE_DC_CONFIGURE_WITH=	distcache=${LOCALBASE}
SOCACHE_DC_LIB_DEPENDS=		libdistcache.so:security/distcache
SSL_CONFIGURE_WITH=		ssl=${OPENSSLBASE}
SSL_USES=			ssl
SSL_CT_USES=			shebangfix python
SHEBANG_FILES=			support/ctlogconfig support/ctauditscts
SHEBANG_LANG=			python
python_OLD_CMD=			"/usr/bin/env python"
XML2ENC_USE=			${PROXY_HTML_USE}
XML2ENC_CONFIGURE_WITH=		${PROXY_HTML_CONFIGURE_WITH}
.for mod in ${EXAMPLE_DISABLED_MODULES}
${mod}_VARS=			with-devmods=yes
.endfor

ETCDIR=			${PREFIX}/etc/${PORTNAME}25
ETC_SUBDIRS=		Includes envvars.d extra modules.d
DATADIR=		${PREFIX}/share/${PORTNAME}25

APR_CONFIG?=		${LOCALBASE}/bin/apr-1-config
APU_CONFIG?=		${LOCALBASE}/bin/apu-1-config
# APU module used by AUTHNZ_LDAP LDAP
APU_LDAP?=		${LOCALBASE}/lib/apr-util-1/apr_ldap.so
# APU module used by SESSION_CRYPTO
APU_CRYPTO_OPENSSL?=	${LOCALBASE}/lib/apr-util-1/apr_crypto_openssl.so
APU_CRYPTO_NSS?=	${LOCALBASE}/lib/apr-util-1/apr_crypto_nss.so

PREFIX_RELDEST=	${PREFIX:S,^${DESTDIR},,}

CONFIGURE_ARGS+=--prefix=${PREFIX_RELDEST} \
		--enable-layout=FreeBSD \
		--with-port=${WITH_HTTP_PORT} \
		--with-sslport=${WITH_SSL_PORT} \
		--with-expat=${LOCALBASE} \
		--with-iconv=${ICONV_PREFIX} \
		--enable-http \
		--with-pcre=${LOCALBASE} \
		--with-apr=${APR_CONFIG} \
		--with-apr-util=${APU_CONFIG}

CONFIGURE_ENV+=	LOCALBASE="${LOCALBASE}" \
		CONFIG_SHELL="${SH}"

MAKE_ENV+=	EXPR_COMPAT=yes \
		INSTALL_MAN="${INSTALL_MAN}" \
		DATADIR=${DATADIR}

#=====================================================
# CONFIGURE_ARGS will be handled in Makefile.modules,
# here we do only OPTIONS fixups

.include <bsd.port.pre.mk>
.include "./Makefile.modules"

.if ${OPSYS} == FreeBSD && ${OSVERSION} < 1100085 && ${OPENSSLBASE} == /usr && \
	(${PORT_OPTION:MSSL} || ${PORT_OPTION:MHTTP2})
IGNORE=	requires OpenSSL from ports on 10.x
.endif

post-extract:
# make sure the configure script contains our patches, preserve the original script for comparsion
	-${MV} -v ${WRKSRC}/configure ${WRKSRC}/configure.upstream
	${CP} ${PATCHDIR}/config.sub ${WRKSRC}/build/

post-patch:
	${REINPLACE_CMD} -e 's," PLATFORM ",FreeBSD,' ${WRKSRC}/server/core.c
	${REINPLACE_CMD} -e 's|logs/error_log|/var/log/httpd-error.log|' \
		${WRKSRC}/include/httpd.h
	${REINPLACE_CMD} -e 's|perlbin=.*|perlbin=${PERL}|' \
		${WRKSRC}/configure.in
	${INSTALL_DATA} ${WRKSRC}/NOTICE ${WRKSRC}/docs/manual

pre-configure::
# silence autotools
	-${MV} -v ${WRKSRC}/configure.in ${WRKSRC}/configure.ac

post-configure:
	@FTPUSERS=`${EGREP} -v '^#' /etc/ftpusers| ${TR} -s "\n" " "` ;\
		${REINPLACE_CMD} -e "s,%%FTPUSERS%%,$${FTPUSERS}," \
			${WRKSRC}/docs/conf/extra/httpd-userdir.conf
	${REINPLACE_CMD} -e "s,%%WWWOWN%%,${WWWOWN}," -e "s,%%WWWGRP%%,${WWWGRP}," \
		${WRKSRC}/docs/conf/httpd.conf
	${REINPLACE_CMD} -e "s,%%PREFIX%%,${PREFIX}," ${WRKSRC}/support/envvars-std

post-install:
	${MV} ${STAGEDIR}${WWWDIR}25 ${STAGEDIR}${WWWDIR}
	@${RM} -rv ${STAGEDIR}/${WWWDIR}/cgi-bin/printenv.vbs \
		${STAGEDIR}/${WWWDIR}/cgi-bin/printenv.wsf \
		${STAGEDIR}${DOCSDIR}/style/lang ${STAGEDIR}${DOCSDIR}/style/xsl
	@${MKDIR} ${ETC_SUBDIRS:S|^|${STAGEDIR}${ETCDIR}/|}
	${MV} ${STAGEDIR}${WWWDIR}/data ${STAGEDIR}${DATADIR}/misc
	${MKDIR} ${STAGEDIR}${WWWDIR}/data
	${INSTALL_DATA} ${FILESDIR}/no-accf.conf ${STAGEDIR}${ETCDIR}/Includes/
# place for 3rd party module configuration
	${INSTALL_DATA} ${FILESDIR}/README_modules.d ${STAGEDIR}${ETCDIR}/modules.d/
# strip returns an error for non binary files, but we have a big mix
	-${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/* 2>/dev/null
	-${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/*
	-${STRIP_CMD} ${STAGEDIR}${PREFIX}/libexec/apache25/mod_*.so

post-install-LOG_FORENSIC-on:
	${INSTALL_SCRIPT} ${WRKSRC}/support/check_forensic ${STAGEDIR}${PREFIX}/sbin

post-install-SSL_CT-off:
	${RM} ${STAGEDIR}${PREFIX}/sbin/ctlogconfig

# maintainer only, check for new modules
modlist: extract
	@${AWK} '/: checking whether to enable mod_/ \
		{printf "%%%%%s%%%%libexec/apache24/%s.so\n", \
		toupper($$8), $$8}' ${WRKSRC}/configure.upstream \
		| ${TR} -d '"' \
		| ${SORT} -u \
		| ${GREP} -E -v '^%%MOD_(HTTP|ISAPI|LOG_CONFIG|PRIVILEGES|SO|UNIXD)%%'

.include <bsd.port.post.mk>
