# Created by: Bernard Spil <brnrd@FreeBSD.org>
# $FreeBSD$

PORTNAME=	dnsdiag
PORTVERSION=	1.3.1
CATEGORIES=	dns python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	DNS Diagnostics and measurement tools (ping, traceroute)

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		python:3.4
USE_PYTHON=	autoplist distutils

RUN_DEPENDS=    ${PYTHON_LIBDIR}/site-packages/dns/__init__.py:dns/py-dnspython \
		cymruwhois:devel/py-cymruwhois


.include <bsd.port.mk>
