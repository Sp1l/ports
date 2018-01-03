# $FreeBSD$

PORTNAME=	neopg
PORTVERSION=	0.0.4
DISTVERSIONPREFIX=	v
CATEGORIES=	security

MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	NeoPG PGP implementation

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/license.txt

LIB_DEPENDS=	libboost_system.so:devel/boost-libs \
		libbotan-2.so:security/botan2 \
		libcurl.so:ftp/curl

USES=		cmake:noninja compiler:c11 gettext sqlite
USE_LDCONFIG=	yes
USE_GITHUB=	yes
GH_ACCOUNT=	das-labor google:googletest taocpp:pegtl agauniyal:rang
GH_PROJECT=	PEGTL:pegtl googletest:googletest rang:rang
GH_TAGNAME=	482b27e:pegtl ec44c6c:googletest 866b9ad:rang
GH_SUBDIR=	3rdparty/pegtl:pegtl 3rdparty/googletest:googletest 3rdparty/rang:rang

INSTALL_TARGET=	install/strip

OPTIONS_DEFINE=	DOCS
OPTIONS_SUB=	yes

DOCS_CMAKE_BOOL=	BUILD_DOC
DOCS_BUILD_DEPENDS=	doxygen:devel/doxygen

PLIST_FILES=	bin/neopg \
		share/locale/de/LC_MESSAGES/neopg.mo

post-install:
	${INSTALL_PROGRAM} ${WRKSRC}/src/${PORTNAME} ${STAGEDIR}${LOCALBASE}/bin/${NEOPG}

.include <bsd.port.mk>
