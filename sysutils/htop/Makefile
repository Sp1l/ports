# Created by: Tony Shadwick <tshadwick@oss-solutions.com>
# $FreeBSD: head/sysutils/htop/Makefile 408275 2016-02-05 22:29:42Z pi $

PORTNAME=	htop
PORTVERSION=	2.0.0
CATEGORIES=	sysutils

MAINTAINER=	gaod@hychen.org
COMMENT=	Better top(1) - interactive process viewer

LICENSE=	GPLv2

NOT_FOR_ARCHS=	ia64 powerpc sparc64

GNU_CONFIGURE=	yes
CPPFLAGS+=	-I${LOCALBASE}/include
LIBS+=		-L${LOCALBASE}/lib -lexecinfo

CONFIGURE_ARGS=	--enable-unicode
USES=		autoreconf ncurses libtool execinfo python:2,build
USE_GITHUB=	yes
GH_ACCOUNT=	hishamhm

post-patch:
	@${REINPLACE_CMD} -e 's:/usr/bin/python:${PYTHON_CMD}:' ${WRKSRC}/scripts/MakeHeader.py

.include <bsd.port.mk>
