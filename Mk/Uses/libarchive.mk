# $FreeBSD: head/Mk/Uses/libarchive.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle dependency on the libarchive port
#
# Feature:	libarchive
# Usage:	USES=libarchive
# Valid ARGS:	none
#
# MAINTAINER:	portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_LIBARCHIVE_MK)
_INCLUDE_USES_LIBARCHIVE_MK=	yes
.include "${USESDIR}/localbase.mk"

LIB_DEPENDS+=	libarchive.so.13:${PORTSDIR}/archivers/libarchive
.endif
