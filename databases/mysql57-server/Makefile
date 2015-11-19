# Created by: "Mahdi Mokhtari <mokhi64@gmail.com>"
# $FreeBSD$

PORTNAME?=	mysql
PORTVERSION=	5.7.9
CATEGORIES=	databases ipv6
MASTER_SITES=	${MASTER_SITE_MYSQL}:MySQL SF/boost/boost/${PORTVERSION}:boost
MASTER_SITE_SUBDIR=	MySQL-5.7:MySQL
PKGNAMESUFFIX?=	57-server
DISTFILES=	mysql-5.7.9.tar.gz:MySQL boost_1_59_0.tar.gz:boost

MAINTAINER=	mokhi64@gmail.com
COMMENT?=	Multithreaded SQL database (server)

SLAVEDIRS=	databases/mysql57-client
#RUN_DEPENDS=	libboost_atomic.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_chrono.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_context.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_coroutine.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_date_time.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_filesystem.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_graph.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_iostreams.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_locale.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_log.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_log_setup.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_math_c99.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_math_c99f.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_math_tr1.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_math_tr1f.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_prg_exec_monitor.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_program_options.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_python.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_random.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_regex.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_serialization.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_signals.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_system.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_thread.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_timer.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_unit_test_framework.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=	libboost_wave.so.1.58.0:${PORTSDIR}/devel/boost-libs
#RUN_DEPENDS=    libboost_wserialization.so.1.58.0:${PORTSDIR}/devel/boost-libs
USES=		cmake:outsource shebangfix

CMAKE_ARGS+=	-DINSTALL_DOCDIR="share/doc/mysql" \
		-DINSTALL_DOCREADMEDIR="share/doc/mysql" \
		-DINSTALL_INCLUDEDIR="include/mysql" \
		-DINSTALL_INFODIR="info" \
		-DINSTALL_LIBDIR="lib/mysql" \
		-DINSTALL_MANDIR="man" \
		-DINSTALL_MYSQLDATADIR="/var/db/mysql" \
		-DINSTALL_MYSQLSHAREDIR="share/mysql" \
		-DINSTALL_MYSQLTESTDIR="share/mysql/tests" \
		-DINSTALL_PLUGINDIR="lib/mysql/plugin" \
		-DINSTALL_SBINDIR="libexec" \
		-DINSTALL_SCRIPTDIR="bin" \
		-DINSTALL_SHAREDIR="share" \
		-DINSTALL_SUPPORTFILESDIR="share/mysql" \
		-DLOCAL_BOOST_DIR=${WRKSRC}/../boost_1_59_0
#		-DINSTALL_SQLBENCHDIR="share/mysql" \
#		-DWITH_EDITLINE=system \
#		-DWITH_LIBWRAP=1

SHEBANG_FILES=	scripts/*.pl* scripts/*.sh

# MySQL-Server part
.if !defined(CLIENT_ONLY)
USES=		mysql:5.7

USES+=		perl5
USE_PERL5=	run

CONFLICTS_INSTALL=	mariadb[0-9]*-server-* \
			mysql[0-46-9][0-689]-server-* \
			percona[0-9]*-server-*

USE_RC_SUBR=	mysql-server

USERS=		mysql
GROUPS=		mysql

MAN1=		my_print_defaults.1 myisam_ftdump.1 myisamchk.1 myisamlog.1 myisampack.1 \
		mysql.server.1 mysql_convert_table_format.1 mysql_fix_extensions.1 \
		mysql_install_db.1 mysql_plugin.1 mysql_secure_installation.1 mysql_setpermission.1 \
		mysql_tzinfo_to_sql.1 mysql_upgrade.1 mysql_zap.1 mysqlbug.1 \
		mysqld_multi.1 mysqld_safe.1 mysqldumpslow.1 mysqlhotcopy.1 mysqlman.1 \
		mysqltest.1 perror.1 replace.1 resolve_stack_dump.1 resolveip.1

#CMAKE_ARGS+=	-DWITH_EMBEDDED_SERVER="ON"
.else
USES+=		readline
.endif

##post-configure:
##	cp -r ${WRKSRC}/include/* ${WRKSRC}/../.build/include
##	cp -r ${WRKSRC}/sql/* ${WRKSRC}/../.build/sql
##
post-patch:
	@${REINPLACE_CMD} 's/*.1/${MAN1}/' ${WRKSRC}/man/CMakeLists.txt

.include <bsd.port.mk>
