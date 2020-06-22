# Created by: Bernard Spil <brnrd@FreeBSD.org>
# $FreeBSD: head/databases/mariadb-client/Makefile 536602 2020-05-26 09:58:39Z brnrd $

PORTNAME=	mariadb
PKGNAMESUFFIX=	105-client

COMMENT=	Multithreaded SQL database (client)

#BROKEN_i386=	compile error: undeclared identifier 'my_atomic_add32'

MASTERDIR=	${.CURDIR}/../${PORTNAME}${PKGNAMESUFFIX:C/-client/-server/}

PLIST=		${.CURDIR}/pkg-plist

CONFLICTS_INSTALL=	databases/mytop

.include "${MASTERDIR}/Makefile"
