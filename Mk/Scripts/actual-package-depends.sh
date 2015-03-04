#!/bin/sh
# MAINTAINER: portmgr@FeeeBSD.org
# $FreeBSD: head/Mk/Scripts/actual-package-depends.sh 378742 2015-02-09 17:16:43Z bapt $

if [ -z "${PKG_BIN}" ]; then
	echo "PKG_BIN required in environment." >&2
	exit 1
fi

resolv_symlink() {
	local file tgt
	file=${1}
	if [ ! -L ${file} ] ; then
		echo ${file}
		return
	fi

	tgt=`readlink ${file}`
	case $tgt in
	/*)
		echo $tgt
		return
		;;
	esac

	file=${file%/*}/${tgt}
	absolute_path ${file}
}

absolute_path() {
	local file myifs target
	file=$1

	myifs=${IFS}
	IFS='/'
	set -- ${file}
	IFS=${myifs}
	for el; do
		case $el in
		.) continue ;;
		'') continue ;;
		..) target=${target%/*} ;;
		*) target="${target}/${el}" ;;
		esac
	done
	echo ${target}
}

find_dep() {
	pattern=$1
	case ${pattern} in
	*\>*|*\<*|*=*)
		${PKG_BIN} info -Eg "${pattern}" 2>/dev/null
		return
		;;
	/*)
		searchfile=$pattern
		;;
	*)
		searchfile=$(/usr/bin/which ${pattern} 2>/dev/null)
		;;
	esac
	if [ -n "${searchfile}" ]; then
		echo $(resolv_symlink ${searchfile}) >&2
		${PKG_BIN} which -q ${searchfile} || ${PKG_BIN} which -q "$(resolv_symlink ${searchfile} 2>/dev/null)" ||
			echo "actual-package-depends: dependency on ${searchfile} not registered (normal if it belongs to base)" >&2
	fi
}

for lookup; do
	${PKG_BIN} query "\"%n\": {origin: \"%o\", version: \"%v\"}" "$(find_dep ${lookup})" || :
done
