# $FreeBSD: head/Mk/Uses/fuse.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle dependency on the fuse port
#
# Feature:	fuse
# Usage:	USES=fuse
# Valid ARGS:	does not require args
#
# MAINTAINER: portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_FUSE_MK)
_INCLUDE_USES_FUSE_MK=	yes

.if !empty(fuse_ARGS)
IGNORE=	USES=fuse does not require args
.endif

LIB_DEPENDS+=	libfuse.so:${PORTSDIR}/sysutils/fusefs-libs
.if !exists(/sbin/mount_fusefs)
RUN_DEPENDS+=	mount_fusefs:${PORTSDIR}/sysutils/fusefs-kmod
.endif

.endif
