# Created by: gahr
# $FreeBSD: head/mail/opensmtpd-extras/Makefile 409808 2016-02-29 12:06:32Z gahr $

PORTNAME=	opensmtpd-extras
PORTVERSION=	201602042118
CATEGORIES=	mail
MASTER_SITES=	http://www.opensmtpd.org/archives/

MAINTAINER=	gahr@FreeBSD.org
COMMENT=	Addons for OpenSMTPD

LICENSE=	ISCL

OPTIONS_DEFINE=		NULL_Q PYTHON_Q PYTHON_S RAM_S STATS
OPTIONS_GROUP=		FILTERS TABLE
OPTIONS_GROUP_FILTERS=	CLAMAV DKIM-SIGNER DNSBL LUA MONKEY PAUSE PERL PYTHON_F \
			REGEX SPAMASSASSIN STUB TRACE VOID
OPTIONS_GROUP_SCHEDULER=	RAM PYTHON_S
OPTIONS_GROUP_TABLE=	LDAP MYSQL PASSWD PGSQL PYTHON REDIS SMAP SQLITE
OPTIONS_DEFAULT=	LDAP MYSQL PASSWD PGSQL PYTHON REDIS SMAP SQLITE

FILTERS_DESC=		Filters
CLAMAV_DESC=	ClamAV support
DKIM-SIGNER_DESC=	DKIM-signer support
DNSBL_DESC=	DNSBL support
LUA_DESC=	Lua support
MONKEY_DESC=	Monkey support
NULL_Q_DESC=	Null queue support
PASSWD_DESC=	passwd(5) table support
PAUSE_DESC=	Pause support
PERL_DESC=	Perl support
PYTHON_DESC=	Python support
PYTHON_F_DESC=	${PYTHON_DESC}
PYTHON_Q_DESC=	Python queueing support
PYTHON_S_DESC=	Python scheludling support
RAM_S_DESC=	RAM scheduling suport
REGEX_DESC=	Regular expression support
SMAP_DESC=	Socketmap protocol support
SPAMASSASSIN_DESC=	SpamAssassin support
STATS_DESC=	Statistics module
STUB_DESC=	Stub support
TABLE_DESC=	OpenSMTPd table support
TRACE_DESC=	Trace support
VOID_DESC=	Void support

OPTIONS_SUB=	yes

LIB_DEPENDS=	libevent.so:${PORTSDIR}/devel/libevent2
RUN_DEPENDS=	${LOCALBASE}/sbin/smtpctl:${PORTSDIR}/mail/opensmtpd

USES=		autoreconf libtool pkgconfig
USE_OPENSSL=	yes
WITH_OPENSSL_PORT=	yes
GNU_CONFIGURE=	yes
INSTALL_DIR=	libexec/opensmtpd

.for _FILTER in ${OPTIONS_GROUP_FILTERS}
${_FILTER}_CONFIGURE_WITH=	filter-${_FILTER:S/_F$//:tl}
${_FILTER}_PLIST_FILES=		${INSTALL_DIR}/filter-${_FILTER:S/_F$//:tl}
.endfor

CLAMAV_RUN_DEPENDS=	clamav>=0:${PORTSDIR}/security/clamav
DNSBL_LIB_DEPENDS=	libasr.so:${PORTSDIR}/dns/libasr
LUA_CONFIGURE_ON=	--with-lua=${LOCALBASE}
LUA_CPPFLAGS=		-I ${LUA_INCDIR}
LUA_USES=		lua
PERL_CONFIGURE_ON+=	--with-perl=${LOCALBASE}
PERL_USE=		perl5
SPAMASSASSIN_RUN_DEPENDS=	spamassassin>=0:${PORTSDIR}/mail/spamassassin

NULL_Q_CONFIGURE_WITH=	queue-null
PYTHON_Q_CONFIGURE_WITH=queue-python

RAM_S_CONFIGURE_WITH=	scheduler-ram
PYTHON_S_CONFIGURE_WITH=scheduler-python

.for _TABLE in ${OPTIONS_GROUP_TABLE}
${_TABLE}_CONFIGURE_WITH= table-${_TABLE:S/SMAP/SOCKETMAP/:S/PGSQL/POSTGRES/:tl}
${_TABLE}_PLIST_FILES=	${INSTALL_DIR}/table-${_TABLE:S/SMAP/SOCKETMAP/:S/PGSQL/POSTGRES/:tl}
.endfor

MYSQL_USE=		MYSQL=client
MYSQL_LDFLAGS=		-L${LOCALBASE}/lib/mysql
PGSQL_USES=		pgsql
PYTHON_USES=		python
REDIS_CONFIGURE_ENV=	REDIS_CONFIG=${LOCALBASE}/bin/pkgconf
REDIS_LIB_DEPENDS=	libhiredis.so:${PORTSDIR}/databases/hiredis
REDIS_VARS=		CFLAGS+=-I${LOCALBASE}/include/hiredis
SQLITE_USES=		sqlite

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MPYTHON*}
CONFIGURE_ARGS+=	--with-python-type=${PYTHON_VERSION}
USES+=			python
.endif

.include <bsd.port.mk>
