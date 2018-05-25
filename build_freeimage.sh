#!/bin/bash

set -ex



# FreeImage needs a few environment variables to build properly
export CFLAGS=-std=c99\ -Wno-narrowing\ -O3\ -fPIC\ -fexceptions\ -fvisibility=hidden
export CXXFLAGS=-std=c++03\ -Wno-narrowing\ -O3\ -fPIC\ -fexceptions\ -fvisibility=hidden\ -Wno-ctor-dtor-privacy
export LDFLAGS=-fPIC



function freeimage_configure()
{
    pushd @EXTERNAL_PROJECT_PREFIX@/src/FreeImage

    # Ensure the makefile's DESTDIR lets us point to where we want it to
    set +e
    grep -E 'DESTDIR.+\/usr' Makefile.gnu
    if [ $? -eq 0 ]; then
        sed -i -r 's/\/usr//g' Makefile.gnu

        # Freeimage attempts to give root permissions to the installed files. No
        sed -i -r 's/(^[[:space:]]+install)[[:space:]]+\-m[[:space:]]+.+root[[:space:]]+(\$.+)/\1 \2/g' Makefile.gnu
    fi

    # Rename functions which conflict with GLibC
    grep -E '\bpowf64\b' "./Source/LibRawLite/internal/dcraw_common.cpp"
    if [ $? -eq 0  ]; then
        echo "*************************************************UPDATING LIBRAW!"
        set -e
        sed -i -r "s/(\b)powf64(\b)/\1internal_powf64\2/g" "./Source/LibRawLite/internal/dcraw_common.cpp"
    fi

    set -e
    popd
}



function freeimage_make()
{
    pushd @EXTERNAL_PROJECT_PREFIX@/src/FreeImage
    make DESTDIR=@EXTERNAL_PROJECT_PREFIX@
    popd
}



function freeimage_install()
{
    cd @EXTERNAL_PROJECT_PREFIX@/src/FreeImage && make DESTDIR=@EXTERNAL_PROJECT_PREFIX@ install
}



function build_freeimage()
{
    local doConfig=0
    local doMake=0
    local doInstall=0

    set +u

    while [ "$1" != "" ]; do
        case $1 in
            -c | --configure )
                doConfig=1
                ;;

            -m | --make )
                doMake=1
                ;;

            -i | --install )
                doInstall=1
                ;;
        esac
        shift
    done

    set -u

    if [[ $doConfig -ne 0 ]]; then
        echo "Configuring FreeImage"
        freeimage_configure
    fi

    if [[ $doMake -ne 0 ]]; then
        echo "Building FreeImage"
        freeimage_make
    fi

    if [[ $doInstall -ne 0 ]]; then
        echo "Installing FreeImage"
        freeimage_install
    fi
}



build_freeimage "$@"
