#!/bin/bash

set -euxo pipefail

# PYTHON_DIR=$(/bin/ls -1 | grep Python- | head -1)
CLONE_DIR=$(pwd)
PYTHON_DIR=$(pwd)

# for i in patches/*.patch; do
#     patch -uN -p0 -d "${PYTHON_DIR}" -i "../${i}"
# done

cp Setup.local ${PYTHON_DIR}/Modules/.

cd ${PYTHON_DIR}/.

export CONFIG_SITE="${CLONE_DIR}/config.site"

export CC="clang --sysroot=/opt/wasi-sdk/wasi-sysroot"
export C_INCLUDE_PATH="${PYTHON_DIR}/wasi-stubs/include"
export CFLAGS="-g --target=wasm32-unknown-wasi -mthread-model single -fno-exceptions -I${C_INCLUDE_PATH} -I${CLONE_DIR} -D_WASI_EMULATED_SIGNAL"

export CXX="clang++ --sysroot=/opt/wasi-sdk/wasi-sysroot"
export CPLUS_INCLUDE_PATH="${C_INCLUDE_PATH}"
export CPPFLAGS="${CFLAGS}"

export LINKCC="clang --sysroot=/opt/wasi-sdk/wasi-sysroot --target=wasm32-unknown-wasi -mthread-model single -Wl,--stack-first -Wl,-z,stack-size=83886080"
export LDFLAGS="-L/opt/wasi-sdk/wasi-sysroot/lib/wasm32-wasi -L/usr/lib/clang/12/lib/wasi -L${CLONE_DIR}/lib"
export LIBS="-lc -lwasi-emulated-signal"
export AR=llvm-ar
export RANLIB=llvm-ranlib
export READELF=llvm-readelf

./configure --host=wasm32 --build=x86_64-pc-linux-gnu --disable-ipv6 --without-threads

BUILD_DIR="build\/lib.wasm32-$(echo ${PYTHON_DIR} | cut -d'-' -f2 | cut -d'.' -f1,2)"

#perl -p -i -e 's/\-O3/\-O0/g' Makefile
# perl -p -i -e 's/@echo "none"/@echo "'${BUILD_DIR}'"/g' Makefile
# perl -p -i -e 's/^\s+.*\-\-generate-posix-vars/\t\@cat .\/pybuilddir.txt/g' Makefile

make clean
make python
