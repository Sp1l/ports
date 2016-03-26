# Created by: Horia Racoviceanu <horia@racoviceanu.com>
# $FreeBSD: head/databases/galera/Makefile 399346 2015-10-15 14:55:14Z mat $

PORTNAME=	galera
PORTVERSION=	25.3.15
DISTVERSIONPREFIX=	3-
CATEGORIES=	databases
MASTER_SITES=	http://releases.galeracluster.com/source/

MAINTAINER=	horia@racoviceanu.com
COMMENT=	Synchronous multi-master replication engine

LICENSE=	GPLv2

BUILD_DEPENDS=	checkmk:${PORTSDIR}/devel/libcheck
LIB_DEPENDS=	libboost_date_time.so:${PORTSDIR}/devel/boost-libs

USES=		execinfo scons shebangfix

USE_CXXSTD=	c++11
USE_LDCONFIG=	yes
USE_OPENSSL=	yes

LDFLAGS+=	-lboost_program_options -lboost_system

PLIST_FILES=	lib/libgalera_smm.so \
		lib/libgalera.so

PORTDOCS=	AUTHORS README

OPTIONS_DEFINE=	BOOSTPOOL BPOSTATIC DEBUG DOCS TEST
OPTIONS_GROUP=	DOCS
OPTIONS_GROUP_DOCS=	EPUB JSON LATEX PICKLE
OPTIONS_SUB=	yes

BOOSTPOOL_DESC=	Use boost pool allocator
BPOSTATIC_DESC=	Use static boost_program_options
EPUB_DESC=	EPUB support
PICKLE_DESC=	Pickle support

.include <bsd.port.pre.mk>

.if ${PORT_OPTIONS:MBOOSTPOOL}
MAKE_ARGS+=	boost_pool=1
.endif

.if ${PORT_OPTIONS:MBPOSTATIC}
MAKE_ARGS+=	bpostatic=${PREFIX}/lib/libboost_program_options.so
.endif

.if ${PORT_OPTIONS:MDEBUG}
MAKE_ARGS+=	debug=3
.endif

post-patch:
	@${REINPLACE_CMD} -e "/-Werror/d; \
		s|LINKFLAGS = link_arch|& + ' ' + os.environ['LDFLAGS']|" \
		${WRKSRC}/SConstruct
	@${REINPLACE_CMD} -e '/#\/asio/d; s|asio.hpp|boost/&|; \
		s|asio/ssl.hpp|boost/&|' ${WRKSRC}/SConstruct
	@${REINPLACE_CMD} -e 's|asio.hpp|boost/&|' -e 's|asio/ssl.hpp|boost/&|' \
		-e 's|gu_boost/asio.hpp|gu_asio.hpp|' \
		-e 's|asio::error_code|::boost::system::error_code|g' \
		-e 's|asio::system_error|::boost::system::system_error|g' \
		-e 's|asio::|::boost::asio::|g' \
		${WRKSRC}/galerautils/src/gu_asio.hpp \
		${WRKSRC}/galerautils/src/gu_asio.cpp
#		${WRKSRC}/galera/src/ist.hpp \
#		${WRKSRC}/gcomm/src/asio_protonet.hpp
	@${REINPLACE_CMD} -e 's|asio::system_error|::boost::system::system_error|g' \
		${WRKSRC}/galera/src/ist.cpp \
		${WRKSRC}/gcomm/src/asio_tcp.cpp \
		${WRKSRC}/gcomm/src/asio_udp.cpp
	@${REINPLACE_CMD} -e 's|asio::error_code|::boost::system::error_code|g' \
		${WRKSRC}/gcomm/src/asio_protonet.*pp \
		${WRKSRC}/gcomm/src/asio_tcp.*pp \
		${WRKSRC}/gcomm/src/asio_udp.*pp
	@${REINPLACE_CMD} -e 's|asio::|boost::&|g' \
		${WRKSRC}/galera/src/ist.*pp \
		${WRKSRC}/galera/src/ist_proto.hpp \
		${WRKSRC}/gcomm/src/asio_protonet.*pp \
		${WRKSRC}/gcomm/src/asio_tcp.*pp \
		${WRKSRC}/gcomm/src/asio_udp.*pp
	@${REINPLACE_CMD} -e 's|LLONG_MAX|gu::LOG_MAX|' \
		${WRKSRC}/galera/src/monitor.hpp
	@${REINPLACE_CMD} -e "s|'galera/SConscript',|'galera/SConscript'])|; \
		/'garb\/SConscript'])/d" ${WRKSRC}/SConscript
	@${REINPLACE_CMD} -e "s|'tests', 1|'tests', 0|" ${WRKSRC}/SConstruct

.if ! ${PORT_OPTIONS:MTEST}
	@${REINPLACE_CMD} -e 's| tests/SConscript||' \
		${WRKSRC}/galerautils/SConscript ${WRKSRC}/gcache/SConscript
	@${REINPLACE_CMD} -e "s|, 'tests/SConscript'||" \
		${WRKSRC}/galera/SConscript
.endif

#	@${REINPLACE_CMD} -e "s|\[u'Codership Oy'\], 1|\[u'Codership Oy'\], 8|" \
#		${WRKSRC}/docs/pasture/source/conf.py

.for d in galerautils gcomm gcs
	@${REINPLACE_CMD} -e 's|= ./|= ../../docs/build/doc/${d}|; \
		s|= man|= ../../man|' ${WRKSRC}/${d}/doc/Doxyfile

. if ! ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${WRKSRC}/docs/build/doc/${d}
	@${REINPLACE_CMD} -e '/GENERATE_HTML / s|YES|NO|' \
		${WRKSRC}/${d}/doc/Doxyfile
. elif ${PORT_OPTIONS:MLATEX}
	@${REINPLACE_CMD} -e '/GENERATE_LATEX/ s|NO|YES|; s|= a4wide|= a4|; \
		/LATEX_OUTPUT/ s|latex|&|' ${WRKSRC}/${d}/doc/Doxyfile
. endif
.endfor

do-install:
	${INSTALL_LIB} ${WRKDIR}/${DISTNAME}/libgalera_smm.so \
		${STAGEDIR}${PREFIX}/lib/
	@(cd ${STAGEDIR}${PREFIX}/lib && ${LN} -sf libgalera_smm.so \
		libgalera.so)

.include <bsd.port.post.mk>
