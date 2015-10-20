# $FreeBSD: head/Mk/Uses/lha.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle lha archives
#
# Feature:	lha
# Usage:	USES=lha
#
.if !defined(_INCLUDE_USES_LHA_Mk)
_INCLUDE_USES_LHA_MK=	yes

EXTRACT_SUFX?=	.lzh

.if !empty(lha_ARGS)
IGNORE=	Incorrect 'USES+=lha:${lha_ARGS}' expecting 'USES+=lha'
.endif

EXTRACT_DEPENDS+=	lha:${PORTSDIR}/archivers/lha
EXTRACT_CMD?=		${LHA_CMD}
EXTRACT_BEFORE_ARGS?=	xfpw=${WRKDIR}
EXTRACT_AFTER_ARGS?=

.endif
