#!/usr/bin/env -S bash ../.port_include.sh
port=tinyscheme
version=1.42
files="https://downloads.sourceforge.net/project/tinyscheme/tinyscheme/tinyscheme-${version}/tinyscheme-${version}.tar.gz tinyscheme-${version}.tar.gz 273ac5ffe5305986b329e9045f2aea89"

useconfigure=false

build() {
    run make scheme CC="i686-pc-serenity-gcc -fpic -pedantic" SYS_LIBS= FEATURES='-DUSE_NO_FEATURES=1 -DInitFile=\"/usr/local/include/tinyscheme/init.scm\"'
}

install() {
    run mkdir -p "${SERENITY_ROOT}/Build/Root/usr/local/bin"
    run cp scheme "${SERENITY_ROOT}/Build/Root/usr/local/bin/tinyscheme"
    run mkdir -p "${SERENITY_ROOT}/Build/Root/usr/local/include/tinyscheme"
    run cp init.scm "${SERENITY_ROOT}/Build/Root/usr/local/include/tinyscheme/init.scm"
}
