# Created by: Bernard Spil <brnrd@FreeBSD.org>
# $FreeBSD$

PORTNAME=	testssl.sh
PORTVERSION=	2.6
CATEGORIES=	security

MAINTAINER=	brnrd@FreeBSD.org
COMMENT=	Pure BASH SSL/TLS profiler

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	bash:${PORTSDIR}/shells/bash

WITH_OPENSSL_PORT=	YES
USE_GITHUB=	yes
GH_ACCOUNT=	drwetter

NO_ARCH=	yes
NO_BUILD=	yes

PLIST_FILES=	bin/testssl.sh \
		${LOCALBASE}/share/${PORTNAME}/mapping-rfc.txt
PORTDOCS_PLIST_FILES=	%%PORTDOCS%%%%DOCSDIR%%/Readme.md \
		%%PORTDOCS%%%%DOCSDIR%%/mapping-rfc.txt \
		%%PORTDOCS%%%%DOCSDIR%%/openssl-rfc.mappping.html

SUB_LIST=	PORTNAME=${PORTNAME}
PORTDOCS=	Readme.md openssl-rfc.mappping.html

post-patch:
	${REINPLACE_CMD} -e "s|MAPPING_FILE_RFC=\"\"|MAPPING_FILE_RFC=\"${LOCALBASE}/share/${PORTNAME}/mapping-rfc.txt\"|" \
		-e "s|declare -x OPENSSL|declare -x OPENSSL=/usr/local/bin/openssl|" ${WRKSRC}/testssl.sh

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

post-install:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${MKDIR} ${STAGEDIR}${PREFIX}/share/${PORTNAME}
.for i in ${PORTDOCS}
	${INSTALL_MAN} ${WRKSRC}/${i} ${STAGEDIR}${DOCSDIR}
.endfor
	${INSTALL_DATA} ${WRKSRC}/mapping-rfc.txt ${STAGEDIR}${PREFIX}/share/${PORTNAME}

.include <bsd.port.mk>
