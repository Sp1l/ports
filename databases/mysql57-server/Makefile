# Created by: "Mahdi Mokhtari <mokhi64@gmail.com>"
# $FreeBSD$

PORTNAME=	mysql
PORTVERSION=	5.7.9
CATEGORIES=	databases ipv6
MASTER_SITES=	MYSQL/MySQL-5.7:MySQL SF/boost/boost/1.59.0:boost
PKGNAMESUFFIX?=	57-server
DISTFILES=	${DISTNAME}${EXTRACT_SUFX}:MySQL boost_1_59_0.tar.gz:boost

MAINTAINER=	mokhi64@gmail.com
COMMENT=	Multithreaded SQL database (server)

SLAVEDIRS=	databases/mysql57-client
USES=		cmake:outsource shebangfix

#needed as MySQL's CMakeLists.txt are thread (job) unsafe
MAKE_JOBS_UNSAFE=	yes

#for testing and debuging purposes
CMAKE_VERBOSE=	yes

CMAKE_ARGS+=	-DINSTALL_DOCDIR="share/doc/mysql" \
		-DINSTALL_DOCREADMEDIR="share/doc/mysql" \
		-DINSTALL_INCLUDEDIR="include/mysql" \
		-DINSTALL_INFODIR="info" \
		-DINSTALL_LIBDIR="lib/mysql" \
		-DINSTALL_PKGCONFIGDIR=${PREFIX}/libdata/pkgconfig \
		-DINSTALL_MANDIR="man" \
		-DINSTALL_MYSQLDATADIR="/var/db/mysql" \
		-DINSTALL_MYSQLSHAREDIR="share/mysql" \
		-DINSTALL_MYSQLTESTDIR="share/mysql/tests" \
		-DINSTALL_PLUGINDIR="lib/mysql/plugin" \
		-DINSTALL_SBINDIR="libexec" \
		-DINSTALL_SCRIPTDIR="bin" \
		-DINSTALL_SHAREDIR="share" \
		-DINSTALL_SUPPORTFILESDIR="share/mysql" \
		-DLOCAL_BOOST_DIR=${WRKSRC}/../boost_1_59_0 \
		-DWITH_INNODB_EXTRA_DEBUG=0
##		-DWITH_INNODB_MEMCACHED=0 \
##		-DWITH_INNOBASE_STORAGE_ENGINE=0
##		-DWITH_SSL={ssl_type|path_name} \
##		-DWITH_SYSTEMD=0 \


SHEBANG_FILES=	scripts/*.pl* scripts/*.sh

.ifdef USE_MYSQL
.error You have `USE_MYSQL' variable defined either in environment or in make(1) arguments. Please undefine and try again.
.endif

# MySQL-Server part
.if !defined(CLIENT_ONLY)
USE_MYSQL=	yes
WANT_MYSQL_VER=	57
MYSQL57_LIBVER=		20

USES+=		perl5
USE_PERL5=	run

CONFLICTS_INSTALL=	mariadb[0-9]*-server-* \
			mysql[0-46-9][0-689]-server-* \
			percona[0-9]*-server-*

USE_RC_SUBR=	mysql-server

USERS=		mysql
GROUPS=		mysql

MMAN1=		my_print_defaults.1 myisam_ftdump.1 myisamchk.1 myisamlog.1 myisampack.1 \
		mysql.server.1 mysql_convert_table_format.1 mysql_fix_extensions.1 \
		mysql_install_db.1 mysql_plugin.1 mysql_secure_installation.1 mysql_setpermission.1 \
 		mysql_tzinfo_to_sql.1 mysql_upgrade.1 mysql_zap.1 mysqlbug.1 \
		mysqld_multi.1 mysqld_safe.1 mysqldumpslow.1 mysqlhotcopy.1 mysqlman.1 \
		mysqltest.1 perror.1 replace.1 resolve_stack_dump.1 resolveip.1

CMAKE_ARGS+=	-DWITH_EMBEDDED_SERVER="ON"

.else
USES+=		readline
.endif

post-extract:
	${RM} -rvf ${WRKSRC}/sql/sql_hints.yy.cc ${WRKSRC}/sql/sql_hints.yy.h

post-patch:
	@${REINPLACE_CMD} 's/*.1/${MMAN1}/' ${WRKSRC}/man/CMakeLists.txt

.include <bsd.port.mk>
