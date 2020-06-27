# Created by: Bernard Spil <brnrd@FreeBSD.org>
# $FreeBSD: head/databases/mariadb-client/Makefile 536602 2020-05-26 09:58:39Z brnrd $

PORTNAME=	mariadb
PKGNAMESUFFIX=	105-client

COMMENT=	Multithreaded SQL database (client)

MASTERDIR=	${.CURDIR}/../${PORTNAME}${PKGNAMESUFFIX:C/-client/-server/}

PLIST=		${.CURDIR}/pkg-plist

.include "${MASTERDIR}/Makefile"
