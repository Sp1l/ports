# $FreeBSD: head/Mk/Uses/shared-mime-info.mk 369465 2014-09-28 16:36:31Z tijl $
#
# handle dependency depends on shared-mime-info and package regen
#
# Feature:	shared-mime-info
# Usage:	USES=shared-mime-info
# Valid ARGS:	does not require args
#
# MAINTAINER: gnome@FreeBSD.org

.if !defined(_INCLUDE_USES_SHARED_MIME_INFO_MK)
_INCLUDE_USES_SHARED_MIME_INFO_MK=	yes

.if !empty(shared-mime-info_ARGS)
IGNORE=	USES=shared-mime-info does not require args
.endif

BUILD_DEPENDS+=	update-mime-database:${PORTSDIR}/misc/shared-mime-info
RUN_DEPENDS+=	update-mime-database:${PORTSDIR}/misc/shared-mime-info
PLIST_FILES+=	"@shared-mime-info share/mime"

.endif
