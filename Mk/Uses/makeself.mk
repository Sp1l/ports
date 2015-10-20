# $FreeBSD: head/Mk/Uses/makeself.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle makeself archives
#
# Feature:	makeself
# Usage:	USES=makeself
#
# MAINTAINER: portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_MAKESELF_Mk)
_INCLUDE_USES_MAKESELF_MK=	yes

.if !empty(makeself_ARGS)
IGNORE=	Incorrect 'USES+= makeself:${makeself_ARGS}' makeself takes no arguments
.endif

EXTRACT_DEPENDS+=	${UNMAKESELF_CMD}:${PORTSDIR}/archivers/unmakeself

EXTRACT_CMD=	${UNMAKESELF_CMD}
EXTRACT_BEFORE_ARGS=
EXTRACT_AFTER_ARGS=

.endif
