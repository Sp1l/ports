# Created by: alfred
# $FreeBSD$

PORTNAME=	jlog
# version is YYYYMMDDxx <- xx is 00, 01 as needed per day
PORTVERSION=	1.2.2.s2015012200
PORTREVISION=	1
CATEGORIES=	databases

MAINTAINER=	alfred@FreeBSD.org
COMMENT=	journaled log

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	omniti-labs	
# we want cf3085fe as it has c++ fixes
# and other additions over the latest 1.2.2
# release
GH_PROJECT=	${PORTNAME}
GH_TAGNAME=	cf3085f

GNU_CONFIGURE=	yes
USES=		perl5 shebangfix

OPTIONS_DEFINE= PERL
OPTIONS_DEFAULT=        PERL
OPTIONS_SUB=	yes

SHEBANG_FILES=	jlog_change_endian.pl jlog_sanity_check.pl
perl_OLD_CMD=	/opt/msys/3rdParty/bin/perl

BUILD_DEPENDS=	autoconf-2.13:${PORTSDIR}/devel/autoconf213

PERL_CONFIGURE_ON=	--with-perl-lib=site
PERL_CONFIGURE_WITH=	perl

pre-configure:
	(cd ${WRKSRC} && ${LOCALBASE}/bin/autoconf-2.13)

.include <bsd.port.mk>
