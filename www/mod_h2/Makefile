# Created by: Bernard Spil <brnrd@FreeBSD.org>
# $FreeBSD$

PORTNAME=	mod_h2
PORTVERSION=	0.9.6
CATEGORIES=	www
MASTER_SITES=	https://github.com/${GH_ACCOUNT}/${PORTNAME}/releases/download/v${PORTVERSION}/
#DISTNAME=	${PORT_NAME}-${PORTVERSION}.tar.gz
# https://github.com/icing/mod_h2/releases/download/v0.9.6/mod_h2-0.9.6.tar.gz
MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	HTTP/2 module for Apache httpd (EXPERIMENTAL)

LICENSE=	APACHE20

BUILD_DEPENDS=	nghttp2>=1.2:${PORTSDIR}/www/nghttp2
LIB_DEPENDS=	libnghttp2.so:${PORTSDIR}/www/nghttp2
RUN_DEPENDS:=	${BUILD_DEPENDS}

#USE_GITHUB=	no
GH_ACCOUNT=	icing
#GH_PROJECT=	mod_h2
#GH_TAGNAME=	e25881a26e

USES=		autoreconf
GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=	--disable-silent-rules CONFIG_SHELL=/bin/sh
CONFIGURE_ENV+=	CONFIG_SHELL=/bin/sh

USE_APACHE=	24+
MODULENAME=	mod_h2

CFLAGS+=	-I${LOCALBASE}/include

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/${APACHEMODDIR}/mod_h2.so.0.0.0

.include <bsd.port.mk>
