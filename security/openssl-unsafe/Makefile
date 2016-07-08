#b Created by: Dirk Froemberg <dirk@FreeBSD.org>
# $FreeBSD: head/security/openssl/Makefile 417176 2016-06-20 19:16:43Z dinoex $

PORTNAME=	openssl
PORTVERSION=	1.0.2
DISTVERSIONSUFFIX=	h
CATEGORIES=	security devel
MASTER_SITES=	http://www.openssl.org/source/ \
		ftp://ftp.openssl.org/source/ \
		ftp://ftp.cert.dfn.de/pub/tools/net/openssl/source/
PKGNAMESUFFIX=	-unsafe
DIST_SUBDIR=	${DISTNAME}

MAINTAINER=	dinoex@FreeBSD.org
COMMENT=	SSL and crypto library

LICENSE=	OpenSSL
LICENSE_FILE=	${WRKSRC}/LICENSE

MAKE_JOBS_UNSAFE=	yes
CPE_VERSION=	${PORTVERSION}${DISTVERSIONSUFFIX}
CONFLICTS=	libressl-[0-9]* \
		libressl-devel-[0-9]* \
		openssl-devel-[0-9]*

OPENSSL_SHLIBVER=1.0

OPTIONS_DEFINE=	SHARED THREADS SSE2 ASM PADLOCK GMP
OPTIONS_DEFAULT=SHARED THREADS SSE2
.for a in amd64 ia64 mips64el
OPTIONS_DEFINE_${a}=	EC
OPTIONS_DEFAULT_${a}=	EC
.endfor
OPTIONS_DEFINE_i386=	I386
NO_OPTIONS_SORT=yes
OPTIONS_SUB=	yes
I386_DESC?=	Optimize for i386 (instead of i486+)
SSE2_DESC?=	runtime SSE2 detection
ASM_DESC?=	optimized Assembler code
PADLOCK_DESC?=	VIA Padlock support
SHARED_DESC?=	build of shared libs
GMP_DESC?=	gmp support (LGPLv3)

GMP_LIB_DEPENDS=	libgmp.so:math/gmp

USES=		perl5 cpe
USE_PERL5=	build
MAKE_ARGS+=	WHOLE_ARCHIVE_FLAG=--whole-archive
MAKE_ENV+=	LIBRPATH="${PREFIX}/lib" GREP_OPTIONS=
SUB_FILES=	pkg-message

CONFIGURE_ARGS=	--libdir=lib/private sctp experimental-jpake enable-ssl2 enable-ssl3 enable-md2 enable-rc5 enable-rfc3779 enable-weak-ssl-ciphers zlib zlib-dynamic

ASM_CONFIGURE_ON=	enable-asm
ASM_CONFIGURE_OFF=	no-asm
ASM_BROKEN_sparc64=	option ASM generates illegal instructions

.if ${MACHINE_ARCH} == amd64 || ${MACHINE_ARCH} == i386 || ${MACHINE_ARCH} == mips64el
CONFIGURE_ARGS+=	enable-ec_nistp_64_gcc_128
.endif

GMP_CONFIGURE_ON=	enable-gmp -I${LOCALBASE}/include
GMP_CONFIGURE_OFF=	no-gmp
GMP_IGNORE=		can not be linked because GMP is LGPLv3

I386_CONFIGURE_ON=	386

SSE2_CONFIGURE_OFF=	no-sse2

SHARED_CONFIGURE_ON=	shared
SHARED_MAKE_ENV=	SHLIBVER=${OPENSSL_SHLIBVER}
SHARED_PLIST_SUB=	SHLIBVER=${OPENSSL_SHLIBVER}
SHARED_USE=		ldconfig=yes		

THREADS_CONFIGURE_ON=	threads
THREADS_CONFIGURE_OFF=	no-threads

OPENSSLDIR?=	${PREFIX}/openssl-unsafe
PLIST_SUB+=	OPENSSLDIR=${OPENSSLDIR:S=^${PREFIX}/==}

.include <bsd.port.pre.mk>

.if ${PORT_OPTIONS:MPADLOCK}
PATCH_DIST_STRIP=	-p1
PATCH_SITES+=	http://git.alpinelinux.org/cgit/aports/plain/main/openssl/:padlock
PATCHFILES+=	1001-crypto-hmac-support-EVP_MD_CTX_FLAG_ONESHOT-and-set-.patch:padlock \
		1002-backport-changes-from-upstream-padlock-module.patch:padlock \
		1003-engines-e_padlock-implement-sha1-sha224-sha256-accel.patch:padlock \
		1004-crypto-engine-autoload-padlock-dynamic-engine.patch:padlock
.endif

post-patch:
	${REINPLACE_CMD} -e 's|m4 -B 8192|m4|g' \
		${WRKSRC}/crypto/des/Makefile
	${REINPLACE_CMD} -e 's|ERR_R_MALLOC_ERROR|ERR_R_MALLOC_FAILURE|' \
		${WRKSRC}/crypto/bio/bss_dgram.c
.if ${PORT_OPTIONS:MEXPCIPHERS}
	${REINPLACE_CMD} -e 's|TLS1_ALLOW_EXPERIMENTAL_CIPHERSUITES	0|TLS1_ALLOW_EXPERIMENTAL_CIPHERSUITES	1|' \
		${WRKSRC}/ssl/tls1.h
.endif

do-configure:
	${REINPLACE_CMD} -e "s|options 386|options|" \
		${WRKSRC}/config
.if ${PORT_OPTIONS:MTHREADS}
	cd ${WRKSRC} \
	&& ${SETENV} CC="${CC}" FREEBSDCC="${CC}" CFLAGS="${CFLAGS}" PERL="${PERL}" \
	./config --prefix=${PREFIX} --openssldir=${OPENSSLDIR} \
		--install_prefix=${STAGEDIR} \
		-L${PREFIX}/lib ${CONFIGURE_ARGS}
.else
	cd ${WRKSRC} \
	&& ${SETENV} CC="${CC}" FREEBSDCC="${CC}" CFLAGS="${CFLAGS}" PERL="${PERL}" \
	./config --prefix=${PREFIX} --openssldir=${OPENSSLDIR} \
		--install_prefix=${STAGEDIR} \
		-L${PREFIX}/lib ${EXTRACONFIGURE}
.endif
	${REINPLACE_CMD} \
		-e 's|^MANDIR=.*$$|MANDIR=$$(PREFIX)/man|' \
		-e 's|$$(LIBDIR)/pkgconfig|libdata/pkgconfig|g' \
		-e 's|LIBVERSION=[^ ]* |LIBVERSION=$(OPENSSL_SHLIBVER) |' \
		${WRKSRC}/Makefile

post-stage-SHARED:
.for i in libcrypto libssl
	${INSTALL_DATA} ${WRKSRC}/$i.so.${OPENSSL_SHLIBVER} ${STAGEDIR}${PREFIX}/lib/private
	${LN} -sf $i.so.${OPENSSL_SHLIBVER} ${STAGEDIR}${PREFIX}/lib/private//$i.so
.endfor

post-stage:
	${MV} ${STAGEDIR}${PREFIX}/bin/openssl ${STAGEDIR}${PREFIX}/bin/openssl-unsafe
	${REINPLACE_CMD} -e 's|^#.*include <openssl|# include <openssl-unsafe|' \
		${STAGEDIR}${PREFIX}/include/openssl/*
	${MV} ${STAGEDIR}${PREFIX}/include/openssl ${STAGEDIR}${PREFIX}/include/openssl-unsafe

test: build
	cd ${WRKSRC} && ${MAKE} test

regression-test:	test

.include <bsd.port.post.mk>
