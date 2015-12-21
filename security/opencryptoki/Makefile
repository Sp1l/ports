# Created by: Ralf Meister
# $FreeBSD: head/security/opencryptoki/Makefile 384225 2015-04-18 12:58:34Z tijl $

PORTNAME=	opencryptoki
PORTVERSION=	3.4.1
CATEGORIES=	security
MASTER_SITES=	SF/${PORTNAME}/${PORTNAME}/3.4
DISTNAME=	${PORTNAME}-v${PORTVERSION}

MAINTAINER=	hrs@FreeBSD.org
COMMENT=	Open PKCS\#11 implementation library

LICENSE=	CPL
LICENSE_NAME=	Common Public License
LICENSE_FILE=	${WRKSRC}/LICENSE
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

LIB_DEPENDS=	libtspi.so:${PORTSDIR}/security/trousers


WRKSRC=		${WRKDIR}/${PORTNAME}

USES=		alias autoreconf gmake libtool tar:tgz
USE_LDCONFIG=	${PREFIX}/lib/opencryptoki
INSTALL_TARGET=	install-strip
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--enable-swtok --enable-tpmtok \
		--disable-crtok --disable-aeptok \
		--disable-ccatok --disable-bcomtok \
		--disable-pkcscca_migrate \
		--localstatedir=/var \
		--with-pkcs11user=${USERS} \
		--with-pkcs11group=${GROUPS}
CFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
USE_RC_SUBR=	pkcsslotd
SUB_FILES=	pkg-message
SUB_LIST=	USERS=${USERS} GROUPS=${GROUPS}
USERS=		_pkcs11
GROUPS=		_pkcs11

.include <bsd.port.mk>
