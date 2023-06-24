# vim: set filetype=sh :

function dnb_mpi-benchmarks() {
    local pkg="mpi-benchmarks"
    environment_check_specific "$pkg" || fatal "$pkg: environment check failed"
    local m=$(get_field "$1" 2 "=")
    local V=$(get_field "$2" 2 "=")
    du_gitclone_recursive "$pkg" "https://github.com/a-v-medvedev/mpi-benchmarks" "$V" "$m"
    if this_mode_is_set "b" "$m"; then
        cd "$pkg"-"$V".src
        old_pwd=$PWD
        DIR=src/ASYNC/thirdparty
        cd $DIR
        ln -s ../../../../argsparser.bin .
        ln -s ../../../../yaml-cpp.bin .
        cd $old_pwd 
        cd $INSTALL_DIR
    fi
    b_make "$pkg" "$V" "" "TARGET=ASYNC" "$m"
    i_make_binary_symlink "$pkg" "${V}" "$m"
}


