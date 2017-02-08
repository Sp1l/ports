# $FreeBSD$

PORTNAME=	kopanocore
PORTVERSION=	8.3.0~718
CATEGORIES=	mail
MASTER_SITES=	https://download.kopano.io/community/core:/sourcecode/

MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	thoroughly modern communication stack.

LICENSE=	AGPLv3

BUILD_DEPENDS=	soapcpp2:devel/gsoap
LIB_DEPENDS=	libcurl.so:ftp/curl \
		libicuuc.so:devel/icu \
		libvmime.so:mail/libvmime

USES=		gmake php ssl
USE_GNOME=	libxml++26
GNU_CONFIGURE=	yes

OPTIONS_DEFINE=	PHP
PHP_DESC=	Build PHP components

CONFIGURE_ARGS=	--with-mapi-configdir=${PREFIX}/etc/mapi

# To make cURL detection work in configure
LDFLAGS+=	-L/usr/local/lib

PHP_CONFIGURE_ON=	--with-php-config=${PREFIX}/bin/php-config

.include <bsd.port.mk>

