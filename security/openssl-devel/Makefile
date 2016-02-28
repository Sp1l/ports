# Created by: Dirk Froemberg <dirk@FreeBSD.org>
# $FreeBSD: head/security/openssl/Makefile 408778 2016-02-13 09:48:26Z dinoex $

PORTNAME=	openssl
PORTVERSION=	1.1.0
DISTVERSIONSUFFIX=	-pre3
PKGNAMESUFFIX=	-devel
CATEGORIES=	security devel
MASTER_SITES=	http://www.openssl.org/source/ \
		ftp://ftp.openssl.org/source/ \
		ftp://ftp.cert.dfn.de/pub/tools/net/openssl/source/
DIST_SUBDIR=	${DISTNAME}

MAINTAINER=	dinoex@FreeBSD.org
COMMENT=	SSL and crypto library

.ifdef USE_OPENSSL
.error You have `USE_OPENSSL' variable defined either in environment or in make(1) arguments. Please undefine and try again.
.endif

CONFLICTS?=	libressl-*
LICENSE=	OpenSSL
LICENSE_FILE=	${WRKSRC}/LICENSE

OPTIONS_GROUP=	CIPHERS HASHES OPTIMS PROTOS
OPTIONS_GROUP_CIPHERS=	IDEA JPAKE RC2 RC4 RC5
OPTIONS_GROUP_HASHES=	MD2 MD4 MDC2 MD_GHOST94 RMD160
OPTIONS_GROUP_OPTIMS=	ASM I386 SSE2
OPTIONS_GROUP_PROTOS=	NEXTPROTONEG SCTP SSL3

OPTIONS_DEFINE=	SHARED THREADS ZLIB RFC3779 MAN3
OPTIONS_DEFAULT=	ASM MAN3 RMD160 SCTP SHARED SSE2 THREADS
.for a in amd64 ia64
OPTIONS_GROUP_OPTIMS_${a}=	EC
OPTIONS_DEFAULT_${a}=	EC
.endfor
TARGET_ARCH?=	${MACHINE_ARCH}
.if ${TARGET_ARCH} == "mips64el"
OPTIONS_GROUP_OPTIMS+=	EC
OPTIONS_DEFAULT+=	EC
.endif
ASM_DESC=	optimized Assembler code
CIPHERS_DESC=	Cipher suites
EC_DESC=	Optimize NIST elliptic curves
HASHES_DESC=	Cryptographic Hash Functions
I386_DESC=	Optimize for i386 (instead of i486+)
IDEA_DESC=	IDEA cipher
JPAKE_DESC=	J-PAKE cipher (experimental)
MAN3_DESC=	Install API manpages (section 3)
MD2_DESC=	MD2 hash (obsolete)
MD4_DESC=	MD4 hash
MDC2_DESC=	MDC-2 hash
MD_GHOST94_DESC=	GHOST94 hash
NEXTPROTONEG_DESC=	NPN Protocol (SPDY)
OPTIMS_DESC=	Optimizations
PROTOS_DESC=	Cryptographic protocols
RC2_DESC=	RC2 cipher (unsafe)
RC4_DESC=	RC4 cipher (unsafe)
RC5_DESC=	RC5 cipher (patented)
RMD160_DESC=	RIPEMD-160 hash
RFC3779_DESC=	RFC3779 support (BGP)
SCTP_DESC=	SCTP protocol support
SHARED_DESC=	build shared libraries
SSE2_DESC=	runtime SSE2 detection
SSL3_DESC=	SSLv3 protocol support
ZLIB_DESC=	zlib compression support

NO_OPTIONS_SORT=yes
OPTIONS_SUB=	yes

MAKE_JOBS_UNSAFE=	yes
NOPRECIOUSMAKEVARS=	Too many _MLINKS for fetch
NOPRECIOUSSOFTMAKEVARS=	Too many _MLINKS for fetch

USES=		perl5 cpe
USE_PERL5=	build
MAKE_ARGS+=	WHOLE_ARCHIVE_FLAG=--whole-archive
MAKE_ENV+=	LIBRPATH="${PREFIX}/lib" GREP_OPTIONS=
SUB_FILES=	pkg-message
TEST_TARGET=	test

CPE_VERSION=	${PORTVERSION}${DISTVERSIONSUFFIX}

.for _option in asm idea md2 md4 mdc2 md_ghost94 nextprotoneg rc5 rfc3779 rmd160 sctp sse2 ssl3 threads
${_option:tu}_CONFIGURE_ON=	enable-${_option}
${_option:tu}_CONFIGURE_OFF=	no-${_option}
.endfor
EC_CONFIGURE_ON+=	enable-ec_nistp_64_gcc_128
EC_CONFIGURE_OFF+=	no-ec_nistp_64_gcc_128
SSL3_CONFIGURE_OFF+=		no-ssl3-method

.include <bsd.port.pre.mk>

.if ${PREFIX} == /usr
IGNORE=	the OpenSSL port can not be installed over the base version
.endif

OPENSSLDIR?=	${PREFIX}/openssl
PLIST_SUB+=	OPENSSLDIR=${OPENSSLDIR:S=^${PREFIX}/==}

OPENSSL_BASE_SONAME!=	readlink ${DESTDIR}/usr/lib/private/libcrypto.so || true
OPENSSL_SHLIBVER_BASE=	${OPENSSL_BASE_SONAME:E}
OPENSSL_BASE_SOPATH=	${OPENSSL_BASE_SONAME:H}
OPENSSL_SHLIBVER?=	8

.if ${PORT_OPTIONS:MI386}
.if ${ARCH} == "i386"
CONFIGURE_ARGS+=	386
.endif
.endif

.if ${PORT_OPTIONS:MASM}
NOT_FOR_ARCHS=	sparc6
.endif

.if ${PORT_OPTIONS:MSHARED}
CONFIGURE_ARGS+=	shared
MAKE_ENV+=	SHLIBVER=${OPENSSL_SHLIBVER}
PLIST_SUB+=	SHLIBVER=${OPENSSL_SHLIBVER}
USE_LDCONFIG=	yes
.endif

.if ${OPENSSL_SHLIBVER_BASE} > ${OPENSSL_SHLIBVER}
pre-everything::
	@${ECHO_CMD} "#"
	@${ECHO_CMD} "# this ports conflicts with your base system"
	@${ECHO_CMD} "# please undefine OPENSSL_OVERWRITE_PORT"
	@${ECHO_CMD} "# and use WITH_OPENSSL_BASE=yes instead."
	@${ECHO_CMD} "#"
	@${FALSE}

.endif

post-patch:
	${REINPLACE_CMD} -e 's|m4 -B 8192|m4|g' \
		${WRKSRC}/crypto/des/Makefile.in
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
		-L${PREFIX}/lib ${CONFIGURE_ARGS:C/--(no|enable)/\1/g}
.else
	cd ${WRKSRC} \
	&& ${SETENV} CC="${CC}" FREEBSDCC="${CC}" CFLAGS="${CFLAGS}" PERL="${PERL}" \
	./config --prefix=${PREFIX} --openssldir=${OPENSSLDIR} \
		-L${PREFIX}/lib ${CONFIGURE_ARGS:C/--\(no|enable\)/\1/g}
.endif
	${REINPLACE_CMD} \
		-e 's|^MANDIR=.*$$|MANDIR=$$(PREFIX)/man|' \
		-e 's|$$(LIBDIR)/pkgconfig|libdata/pkgconfig|g' \
		-e 's|LIBVERSION=[^ ]* |LIBVERSION=$(OPENSSL_SHLIBVER) |' \
		${WRKSRC}/Makefile

post-install:
.if ${PORT_OPTIONS:MSHARED}
.for i in libcrypto libssl
	${INSTALL_DATA} ${WRKSRC}/$i.so.${OPENSSL_SHLIBVER} ${STAGEDIR}${PREFIX}/lib
	${LN} -sf $i.so.${OPENSSL_SHLIBVER} ${STAGEDIR}${PREFIX}/lib/$i.so
.endfor
.endif
.if empty(PORT_OPTIONS:MMAN3)
	${RM} -rf ${STAGEDIR}/${PREFIX}/man/man3
	${REINPLACE_CMD} -e 's|^man/man3/.*||' ${TMPPLIST}
.endif

.include <bsd.port.post.mk>
