# $FreeBSD: head/Mk/Uses/mono.mk 369465 2014-09-28 16:36:31Z tijl $
#
# mono (c#) support
#
# Feature:	mono
# Usage:	USES=mono
#
# MAINTAINER=	mono@FreeBSD.org

.if !defined(_INCLUDE_USES_MONO_MK)
_INCLUDE_USES_MONO_MK=	yes

.if !empty(mono_ARGS)
IGNORE=	USES=mono takes no arguments
.endif

# Set the location of the .wapi directory so we write to a location we
# can always assume to be writable.
MONO_SHARED_DIR=	${WRKDIR}
CONFIGURE_ENV+=		MONO_SHARED_DIR="${MONO_SHARED_DIR}"
MAKE_ENV+=		MONO_SHARED_DIR="${MONO_SHARED_DIR}"
BUILD_DEPENDS+=		mono:${PORTSDIR}/lang/mono
RUN_DEPENDS+=		mono:${PORTSDIR}/lang/mono

# Set the location that webaps served by XSP should use.
XSP_DOCROOT=		${PREFIX}/www/xsp

# gac utilities
GACUTIL=${LOCALBASE}/bin/gacutil /root ${PREFIX}/lib/ /gacdir ${PREFIX}/lib
GACUTIL_INSTALL=${GACUTIL} /i
GACUTIL_INSTALL_PACKAGE=${GACUTIL} /i /package 1.0 /package 2.0

.endif
