# Created by: Dirk Froemberg <dirk@FreeBSD.org>
# $FreeBSD: head/security/openssl/Makefile 421025 2016-08-28 16:19:16Z dinoex $

PORTNAME=	openssl
PORTVERSION=	1.0.2
CATEGORIES=	security devel
#MASTER_SITES=	http://www.openssl.org/source/ \
#		ftp://ftp.openssl.org/source/ \
#		ftp://ftp.cert.dfn.de/pub/tools/net/openssl/source/
#DIST_SUBDIR=	${DISTNAME}
PKGNAMESUFFIX=	-unsafe

MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	Unsafe SSL and crypto library

LICENSE=	OpenSSL
LICENSE_FILE=	${WRKSRC}/LICENSE

CPE_VERSION=	${PORTVERSION}${DISTVERSIONSUFFIX}

USE_GITHUB=	yes
GH_ACCOUNT=	PeterMosmans
GH_TAGNAME=	293717318e903b95f4d7e83a98a087282f37efc3

ONLY_FOR_ARCHS=	amd64

USES=		cpe perl5
USE_PERL5=	build
MAKE_ARGS+=	WHOLE_ARCHIVE_FLAG=--whole-archive
MAKE_ENV+=	LIBRPATH="${PREFIX}/lib" GREP_OPTIONS= SHLIBVER=${OPENSSL_SHLIBVER}
CFLAGS+=	-fPIC
SUB_FILES=	pkg-message
PLIST_SUB+=	SHLIBVER=${OPENSSL_SHLIBVER}
USE_LDCONFIG=	yes

.include <bsd.port.pre.mk>

EXTRACONFIGURE=	experimental-jpake experimental-store \
		enable-ec_nistp_64_gcc_128 enable-md2 enable-rc5 enable-rfc3779 enable-ssl-trace \
		sctp shared threads zlib zlib-dynamic no-gmp

OPENSSLDIR?=	${PREFIX}/openssl-unsafe
PLIST_SUB+=	OPENSSLDIR=${OPENSSLDIR:S=^${PREFIX}/==}

OPENSSL_BASE_SONAME!=	readlink ${DESTDIR}/usr/lib/libcrypto.so || true
OPENSSL_SHLIBVER_BASE=	${OPENSSL_BASE_SONAME:E}
OPENSSL_BASE_SOPATH=	${OPENSSL_BASE_SONAME:H}

.include "version.mk"

.if ${PORT_OPTIONS:MSHARED}
EXTRACONFIGURE+=	shared
MAKE_ENV+=	SHLIBVER=${OPENSSL_SHLIBVER}
PLIST_SUB+=	SHLIBVER=${OPENSSL_SHLIBVER}
USE_LDCONFIG=	yes
.endif

post-patch:
	${REINPLACE_CMD} -e 's|m4 -B 8192|m4|g' \
		${WRKSRC}/crypto/des/Makefile
	${REINPLACE_CMD} -e 's|SHLIB_VERSION_NUMBER "1.0.0"|SHLIB_VERSION_NUMBER "${OPENSSL_SHLIBVER}"|' \
		${WRKSRC}/crypto/opensslv.h
	${REINPLACE_CMD} -e 's|ERR_R_MALLOC_ERROR|ERR_R_MALLOC_FAILURE|' \
		${WRKSRC}/crypto/bio/bss_dgram.c
	${REINPLACE_CMD} -e 's|TLS1_ALLOW_EXPERIMENTAL_CIPHERSUITES	0|TLS1_ALLOW_EXPERIMENTAL_CIPHERSUITES	1|' \
		${WRKSRC}/ssl/tls1.h

do-configure:
	${REINPLACE_CMD} -e "s|options 386|options|" \
		${WRKSRC}/config
	cd ${WRKSRC} \
	&& ${SETENV} CC="${CC}" FREEBSDCC="${CC}" CFLAGS="${CFLAGS}" PERL="${PERL}" \
	./config --prefix=${PREFIX}/openssl-unsafe --openssldir=${OPENSSLDIR} \
		--install_prefix=${STAGEDIR} \
		-L${PREFIX}/openssl-unsafe/lib ${EXTRACONFIGURE}

post-configure:
	${REINPLACE_CMD} \
		-e 's|^MANDIR=.*$$|MANDIR=$$(PREFIX)/man|' \
		-e 's|$$(LIBDIR)/pkgconfig|libdata/pkgconfig|g' \
		-e 's|LIBVERSION=[^ ]* |LIBVERSION=${OPENSSL_SHLIBVER} |' \
		${WRKSRC}/Makefile

#post-install:
#.for i in libcrypto libssl
#	${INSTALL_DATA} ${WRKSRC}/$i.so.${OPENSSL_SHLIBVER} ${STAGEDIR}${PREFIX}/lib
#	${LN} -sf $i.so.${OPENSSL_SHLIBVER} ${STAGEDIR}${PREFIX}/lib/$i.so
#.endfor

test: build
	cd ${WRKSRC} && ${MAKE} test

regression-test:	test

.include <bsd.port.post.mk>
