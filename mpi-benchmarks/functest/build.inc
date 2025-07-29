# vim: set filetype=sh :

function dnb_mpi-benchmarks() {
    generic_prolog "mpi-benchmarks" $* || return 0
    du_gitclone_recursive "$pkg" "https://github.com/a-v-medvedev/mpi-benchmarks"
    if this_mode_is_set "b"; then
        cd "$pkg"-"$V".src
        old_pwd=$PWD
        DIR=src/ASYNC/thirdparty
        cd $DIR
        ln -s ../../../../argsparser.bin .
        ln -s ../../../../yaml-cpp.bin .
        cd $old_pwd 
        cd $DNB_INSTALL_DIR
    fi
    b_make "" "TARGET=ASYNC CXX=mpicxx"
    if this_mode_is_set "i"; then
        mkdir -p "$pkg"-"$V"
        cp "$pkg"-"$V".src/IMB-ASYNC "$pkg"-"$V"
    fi
    i_generate_psubmit_opt
    generic_epilog
}

export TESTSUITE_PACKAGES="mpi-benchmarks"
export TESTSUITE_VERSIONS="mpi-benchmarks:HEAD"
