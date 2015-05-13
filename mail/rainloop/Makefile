# $FreeBSD: head/mail/rainloop/Makefile 385562 2015-05-06 20:34:12Z rodrigo $

PORTNAME=	rainloop
PORTVERSION=	1.9.0
CATEGORIES?=	mail www
MASTER_SITES=	http://repository.rainloop.net/v2/webmail/${PORTVERSION}/
DISTNAME=	${PORTNAME}${EDITION}-${PORTVERSION}.${RBUILD}-${RHASH}
RBUILD=		325

MAINTAINER=	loic.blot@unix-experience.fr
COMMENT=	Modern and interactive webmail

.if !defined(EDITION)
LICENSE=	CCbyNCSA3
LICENSE_NAME=	Attribution-NonCommercial-ShareAlike 3.0 Unported
LICENSE_TEXT=	License can be found at: https://github.com/RainLoop/rainloop-webmail/blob/master/LICENSE
LICENSE_PERMS=	dist-mirror pkg-mirror auto-accept
# Refresh using info from http://repository.rainloop.net/v2/core.stable.json
RHASH=		0e55c0364faafb6f550fd4b186acfe6e
.endif

.if defined(EDITION)
LICENSE=	AGPLv3
EDITION=	-community
# Refresh using info from http://repository.rainloop.net/v2/core.open.json
RHASH=		9486e0b169cbb489dd5904d3414affce
RBUILD=		325
.endif

USES=		zip
NO_BUILD=	yes
NO_WRKSUBDIR=	yes
WANT_PHP_WEB=	yes
USE_PHP=	curl iconv json xml dom openssl pcre spl zlib
RVER=		${PORTVERSION}.${RBUILD}
PLIST_SUB=	VER="${RVER}" WWWOWN="${WWWOWN}" WWWGRP="${WWWGRP}"

OPTIONS_RADIO=		DB
OPTIONS_RADIO_DB=	MYSQL PGSQL SQLITE
OPTIONS_DEFAULT=	SQLITE

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MMYSQL}
USE_PHP+=	pdo_mysql
.endif

.if ${PORT_OPTIONS:MPGSQL}
USE_PHP+=	pdo_pgsql
.endif

.if ${PORT_OPTIONS:MSQLITE}
USE_PHP+=	pdo_sqlite
.endif

do-install:
	@${MKDIR} ${STAGEDIR}${WWWDIR}/data
	${INSTALL_DATA} ${WRKSRC}/data/* ${STAGEDIR}${WWWDIR}/data
	${INSTALL_DATA} ${WRKSRC}/index.php ${STAGEDIR}${WWWDIR}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} rainloop ${STAGEDIR}${WWWDIR})

.include <bsd.port.mk>
