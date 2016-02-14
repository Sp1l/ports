# $FreeBSD$
#
# Provide support for MySQL/MariaDB/Percona (mysql)
#
# Feature:	mysql
# Usage:	USES=		mysql[:version]
#
#		Maintainer can set version required.  Minimum and maximum
#		versions can be specified; e.g. 5.6-, 5.7+
#		MySQL flavours MariaDB and Percona are identified by the
#		m and p version suffixes respectively, eg 10.0m+
#
#		WANT_MYSQL=	server[:fetch]
#
#		Add MySQL component dependency, using
#		WANT_MYSQL=	component[:target].
#		For the full list use make -V _USE_MYSQL_DEP
#		If no version is given (by the maintainer via the port or
#		by the user via defined variable), try to find the
#		currently installed version.  Fall back to default if
#		necessary.
#
# MAINTAINER: brnrd@FreeBSD.org

.if !defined(_INCLUDE_USES_MYSQL_MK)

_INCLUDE_USES_MYSQL_MK=	yes

# Variables set by mysql.mk:
#
# MYSQL_VER
#	Detected PostgreSQL version.  Do *not* use this
#	to add dependencies; use WANT_MYSQL as explained above
#

VALID_MYSQL_VER=	5.5 5.6 5.7 5.5m 10.0m 10.1m 5.5p 5.6p

# Override non-default LIBVERS like this:
#MYSQL60_LIBVER=22

MYSQL_LIBVER=	18
.for v in ${VALID_MYSQL_VER:S,.,,}
MYSQL$v_LIBVER?=	${MYSQL_LIBVER}
.endfor
MYSQL57_LIBVER=	20

.include "${PORTSDIR}/Mk/bsd.default-versions.mk"

.for v in ${MYSQL_DEFAULT}
.  if ! ${VALID_MYSQL_VER:M$v}
IGNORE=		Invalid MYSQL default version ${MYSQL_DEFAULT}; valid versions are ${VALID_MYSQL_VER}
.  endif
.endfor

.for w in WITH DEFAULT
.  ifdef $w_MYSQL_VER
WARNING+=	"$w_MYSQL_VER is defined, consider using DEFAULT_VERSIONS=mysql=${$w_MYSQL_VER:C,^.,&.,} instead"
MYSQL_DEFAULT?=	${$w_MYSQL_VER:C,^.,&.,}
.  endif
.endfor

.ifdef DEFAULT_MYSYQL_VER && WITH_MYSQL_VER
IGNORE=		will not allow setting both DEFAULT_MYSQL_VER and WITH_MYSQL_VER.  Use DEFAULT_VERSIONS=mysql=5.6 instead
.endif

# Setting/finding MySQL version and flavour we want.
MYSQL_CLI?=	${LOCALBASE}/bin/mysql
.if exists(${MYSQL_CLI})
_MYSQL_CLI_VER!=	${MYSQL_CLI} --version | ${SED} -e 's/.*Distrib \([0-9]\{1,2\}\)\.\([0-9]*\).*/\1.\2/'
_MARIADB!=	${MYSQL_CLI} --version | ${GREP} MariaDB | wc -l
_PERCONA!=	${MYSQL_CLI} --version | ${GREP} Percona | wc -l
.  if ${_MARIADB} == 1
_MYSQL_FLAVOUR=	MariaDB
_MYSQL_VER=	${_MYSQL_CLI_VER}m
.  elif ${_PERCONA} == 1
_MYSQL_FLAVOUR=	Percona
_MYSQL_VER=	${_MYSQL_CLI_VER}p
.  else
_MYSQL_FLAVOUR=	MySQL
_MYSQL_VER=	${_MYSQL_CLI_VER}
.  endif
.endif

# Handle the + and - version stuff
.if !empty(mysql_ARGS)
.  if ${mysql_ARGS:M*+}
.    for version in ${VALID_MYSQL_VER}
.      if ${mysql_ARGS:S/+//} <= ${version}
_WANT_MYSQL_VER+=	${version}
.      endif
.    endfor
.  elif ${mysql_ARGS:M*-}
.    for version in ${VALID_MYSQL_VER}
.      if ${mysql_ARGS:S/-//} >= ${version}
_WANT_MYSQL_VER+=i	${version}
.      endif
.    endfor
.  endif
_WANT_MYSQL_VER?=	${mysql_ARGS}
.endif

# Try to match default version, otherwise just take the first version
# that matches
.if !empty(_WANT_MYSQL_VER)
.  for version in ${_WANT_MYSQL_VER}
.    if ${MYSQL_DEFAULT} == ${version}
MYSQL_VER=	${version}
.    endif
MYSQL_VER?=	${version}
.  endfor
.endif # !empty(_WANT_MYSQL_VER)

# OK, so the port is ambivalent, we'll just take what's on the system 
.if defined(_MYSQL_VER)
MYSQL_VER?=	${_MYSQL_VER}
.endif

# After all that, we still have found nothing!
MYSQL_VER?=	${MYSQL_DEFAULT}

# Derive MySQL flavour from version
.if ${MYSQL_VER:M[0-9.]*m}
MYSQL_FLAVOUR= MariaDB
.elif ${MYSQL_VER:M[0-9.]*p}
MYSQL_FLAVOUR=  Percona
.endif
MYSQL_FLAVOUR?= MySQL

# Now we can generate a proper message
.if !empty(_WANT_MYSQL_VER)
.  if defined(_MYSQL_VER) && ${_MYSQL_VER} != ${MYSQL_VER}
IGNORE?=        cannot install: the port wants ${MYSQL_FLAVOUR}-client version ${_WANT_MYSQL_VER} and you have ${_MYSQL_FLAVOUR} version ${_MYSQL_VER} installed
.  endif
.endif

# We don't want to be :S,.,, the whole time when doing port version checks
MYSQL_VER_NODOT=	${MYSQL_VER:S,.,,}

# And now we are checking if we can use it
.if defined(MYSQL${MYSQL_VER_NODOT}_LIBVER)
# Compat.  Please DO NOT use IGNORE_WITH_MYSQL!
.  if defined(IGNORE_WITH_MYSQL)
DEV_WARNING+=	"Do not set IGNORE_WITH_MYSQL, use the version argument to USES=mysql"
.    for ver in ${IGNORE_WITH_MYSQL}
.      if (${MYSQL_VER} == ${ver})
IGNORE?=		cannot install: does not work with ${_MYSQL_FLAVOUR:tl}${MYSQL_VER_NODOT:C/[mp//]}-client (${_MYSQL_FLAVOUR} ${IGNORE_WITH_MYSQL} not supported)
.      endif
.    endfor
.  endif # IGNORE_WITH_MYSQL

MYSQL_CLIENT_PORT=${PORTSDIR}/databases/${MYSQL_FLAVOUR:tl}${MYSQL_VER_NODOT:C/[mp]//}-client
MYSQL_SERVER_PORT=${PORTSDIR}/databases/${MYSQL_FLAVOUR:tl}${MYSQL_VER_NODOT:C/[mp]//}-server

_USE_MYSQL_DEP=	client embedded lib server
.  if defined(WANT_MYSQL)
.    if ${WANT_MYSQL:Mclient}
RUN_DEPENDS+=	${LOCALBASE}/bin/mysql:${MYSQL_CLIENT_PORT}
.    elif ${WANT_MYSQL:Membedded}
BUILD_DEPENDS+=	${LOCALBASE}/lib/mysql/libmysqld.a:${MYSQL_SERVER_PORT}
RUN_DEPENDS+=	${LOCALBASE}/libexec/mysqld:${MYSQL_SERVER_PORT}
.    elif ${WANT_MYSQL:Mlib}
LIB_DEPENDS+=	libmysqlclient.so.${MYSQL${MYSQL_VER_NODOT}_LIBVER}:${MYSQL_CLIENT_PORT}
.    elif ${WANT_MYSQL:Mserver}
RUN_DEPENDS+=	${LOCALBASE}/libexec/mysqld:${MYSQL_SERVER_PORT}
.    endif
.  else # WANT_MYSQL undefined
LIB_DEPENDS+=	libmysqlclient.so.${MYSQL${MYSQL_VER_NODOT}_LIBVER}:${MYSQL_CLIENT_PORT}
.  endif

.else
IGNORE?=		cannot install: unknown MySQL version: ${MYSQL_VER}
.endif # Check for correct version

CPPFLAGS+=		-I${LOCALBASE}/include
LDFLAGS+=		-L${LOCALBASE}/lib

.endif # !defined(_INCLUDE_USES_MYSQL_MK)
