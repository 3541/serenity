#!/bin/bash ../.port_include.sh
port=wget
version=1.20.3
useconfigure="true"
files="https://ftp.gnu.org/gnu/wget/wget-${version}.tar.gz wget-${version}.tar.gz"
#configopts="--target=i686-pc-serenity"
#depends="pcre2"

install() {
    run make DESTDIR="$SERENITY_ROOT"/Root install-strip
}
