# $FreeBSD: head/Mk/Uses/objc.mk 406126 2016-01-14 18:54:29Z antoine $
#
# Objective C support
#
# Feature:	objc
# Usage:	USES=objc
#
# MAINTAINER:	objc@FreeBSD.org

.if !defined(_INCLUDE_USES_OBJC_MK)
_INCLUDE_USES_OBJC_MK=	yes

objc_ARGS?=
.if !empty(objc_ARGS) && ! ${objc_ARGS:Mcompiler}
IGNORE=	USES=objc only accepts no arguments or 'compiler'
.endif

_CCVERSION!=	${CC} --version
.if defined(.PARSEDIR)
COMPILER_VERSION=	${_CCVERSION:M[0-9].[0-9]*:tW:C/([0-9]).([0-9]).*/\1\2/g}
.else
COMPILER_VERSION=	${_CCVERSION:M[0-9].[0-9]*:C/([0-9]).([0-9]).*/\1\2/g:u}
.endif
.if ${_CCVERSION:Mclang}
COMPILER_TYPE=	clang
.else
COMPILER_TYPE=	gcc
.endif

ALT_COMPILER_VERSION=	0
ALT_COMPILER_TYPE=	none
_ALTCCVERSION=	
.if ${COMPILER_TYPE} == gcc && exists(/usr/bin/clang)
_ALTCCVERSION!=	/usr/bin/clang --version
.elif ${COMPILER_TYPE} == clang && exists(/usr/bin/gcc)
_ALTCCVERSION!=	/usr/bin/gcc --version
.endif

.if defined(.PARSEDIR)
ALT_COMPILER_VERSION=	${_ALTCCVERSION:M[0-9].[0-9]*:tW:C/([0-9]).([0-9]).*/\1\2/g}
.else
ALT_COMPILER_VERSION=	${_ALTCCVERSION:M[0-9].[0-9]*:C/([0-9]).([0-9]).*/\1\2/g:u}
.endif
.if ${_ALTCCVERSION:Mclang}
ALT_COMPILER_TYPE=	clang
.elif !empty(_ALTCCVERSION)
ALT_COMPILER_TYPE=	gcc
.endif

# We do always need clang
.if (${COMPILER_TYPE} == clang && ${COMPILER_VERSION} < 34) || ${COMPILER_TYPE} != clang
.if ${ALT_COMPILER_TYPE} == clang && ${ALT_COMPILER_VERSION} >= 34
CC=	/usr/bin/clang
CPP=	/usr/bin/clang-cpp
CXX=	/usr/bin/clang++
.else
BUILD_DEPENDS+=	${LOCALBASE}/bin/clang34:${PORTSDIR}/lang/clang34
CPP=	${LOCALBASE}/bin/clang-cpp34
CC=	${LOCALBASE}/bin/clang34
CXX=	${LOCALBASE}/bin/clang++34
.endif
.endif

.if ! ${objc_ARGS:Mcompiler}
LIB_DEPENDS+=	libobjc.so.4.6:${PORTSDIR}/lang/libobjc2
OBJCFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
.endif
CONFIGURE_ENV+=	OBJC="${CC}" OBJCFLAGS="${OBJCFLAGS}"
MAKE_ENV+=	OBJC="${CC}" OBJCFLAGS="${OBJCFLAGS}"

.endif
