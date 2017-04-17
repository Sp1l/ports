# $FreeBSD$

PORTNAME=	mariadb
PORTVERSION=	2.0.14
CATEGORIES=	databases ipv6
MASTER_SITES=	http://ftp.osuosl.org/pub/${SITESDIR}/ \
		http://mirrors.supportex.net/${SITESDIR}/ \
		http://mirror2.hs-esslingen.de/pub/Mirrors/${SITESDIR}/ \
		http://gd.tuwien.ac.at/db/${SITESDIR}/ \
		http://mirrors.fe.up.pt/pub/${SITESDIR}/ \
		http://mirror.de.gsnw.de:56431/${SITESDIR}/ \
		http://mirror.layerjet.com/${SITESDIR}/ \
		http://mirror.switch.ch/mirror/${SITESDIR}/
PKGNAMESUFFIX=	-connector-odbc
DISTNAME=	${PORTNAME}${PKGNAMESUFFIX}-${PORTVERSION}-ga-src

MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	MariaDB database connector for C

LICENSE=	LGPL21
LICENSE_FILE=	${WRKSRC}/COPYING

CONFLICTS_INSTALL=	mariadb[0-9]*-client-* \
			mariadb102-server-* \
			mysql[0-9]*-client-* \
			percona[0-9]*-client-*

USES=		cmake
USE_LDCONFIG=	${PREFIX}/lib/mariadbconnector-odbc
SITESDIR=	${PORTNAME}/connector-odbc-${PORTVERSION}/source
DOCSDIR=	${PREFIX}/share/doc/mysql

BUILD_DEPENDS=  unixODBC>=2.2.14_1:databases/unixODBC \
		mariadbconnector-c>=2.3.0:databases/mariadb-connector-c
LIB_DEPENDS=    libodbc.so:databases/unixODBC
RUN_DEPENDS=	mariadbconnector-c>=2.3.0:databases/mariadb-connector-c

CMAKE_ARGS+=	-DCOMPILATION_COMMENT="FreeBSD Ports"

PLIST_FILES=	lib/libmaodbc.so

post-install:
	${RM} -r ${STAGEDIR}${PREFIX}/share/doc/mariadb_connector_odbc

.include <bsd.port.mk>
