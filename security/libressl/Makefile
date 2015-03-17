# Created by: Vsevolod Stakhov <vsevolod@FreeBSD.org>
# $FreeBSD: head/security/libressl/Makefile 380424 2015-03-04 09:34:25Z vsevolod $

PORTNAME=	libressl
PORTVERSION=	2.1.5
CATEGORIES=	security devel
MASTER_SITES=	${MASTER_SITE_OPENBSD}
MASTER_SITE_SUBDIR=	LibreSSL

MAINTAINER=	vsevolod@FreeBSD.org
COMMENT=	Free version of the SSL/TLS protocol forked from OpenSSL

LICENSE=	BSD4CLAUSE
CPE_VENDOR=	openbsd

CONFLICTS?=	openssl-*

GNU_CONFIGURE=	yes
USES=	libtool pkgconfig pathfix cpe
USE_LDCONFIG=	yes

INSTALL_TARGET=	install-strip

test: build
	cd ${WRKSRC} && ${MAKE} check

.include <bsd.port.mk>
