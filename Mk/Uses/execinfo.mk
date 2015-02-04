# $FreeBSD: head/Mk/Uses/execinfo.mk 364083 2014-08-05 07:52:48Z mat $
#
# handle dependency on libexecinfo
#
# Feature:	execinfo
# Usage:	USES=execinfo
#
# Take no arguments

.if !defined(_INCLUDE_USES_EXECINFO_MK)
_INCLUDE_USES_EXECINFO_MK=	yes

.if !exists(/usr/lib/libexecinfo.so)
LIB_DEPENDS+=	libexecinfo.so:${PORTSDIR}/devel/libexecinfo
.endif

.endif
