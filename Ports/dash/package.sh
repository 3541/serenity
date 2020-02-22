#!/bin/bash ../.port_include.sh
port=dash
version=0.5.10
useconfigure="true"
files="http://gondor.apana.org.au/~herbert/dash/files/dash-${version}.tar.gz dash-${version}.tar.gz"
configopts="--target=i686-pc-serenity"

install() {
    run make DESTDIR="$SERENITY_ROOT"/Root install-strip
}
