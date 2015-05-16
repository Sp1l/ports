# Created by: Martin Blapp
# $FreeBSD: head/mail/up-imapproxy/Makefile 355958 2014-05-31 10:57:17Z madpilot $

PORTNAME=	imapproxy
PORTVERSION=	1.2.7
PORTREVISION=	3
CATEGORIES=	mail
MASTER_SITES=	SF/squirrelmail/imap_proxy/${PORTVERSION}
PKGNAMEPREFIX=	up-
DISTNAME=	squirrelmail-imap_proxy-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Caching IMAP proxy server

LICENSE=	GPLv2 # (or later)

OPTIONS_DEFINE=	DOVECOT DOCS
DOVECOT_DESC=	Use with dovecot2
OPTIONS_SUB=	yes

USES=		autoreconf tar:bzip2 pathfix
USE_OPENSSL=	yes
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-openssl=${OPENSSLBASE}

USE_RC_SUBR=	imapproxyd

SUB_FILES=	pkg-message

DOCS=		ChangeLog README README.debian README.known_issues README.ssl
SBIN=		in.imapproxyd pimpstat

.include <bsd.port.options.mk>

DOVECOT_RUN_DEPENDS=	dovecot:${PORTSDIR}/mail/dovecot2

do-install:
.for i in ${SBIN}
	(cd ${WRKSRC}/bin && ${INSTALL_PROGRAM} ${i} ${STAGEDIR}${PREFIX}/sbin)
.endfor
	(cd ${WRKSRC}/scripts && ${INSTALL_DATA} imapproxy.conf \
		${STAGEDIR}${PREFIX}/etc/imapproxyd.conf.sample)
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for i in ${DOCS}
	(cd ${WRKSRC} && ${INSTALL_DATA} ${i} ${STAGEDIR}${DOCSDIR})
.endfor
.endif

.include <bsd.port.mk>
