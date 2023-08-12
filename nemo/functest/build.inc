# vim: set filetype=sh :

function dnb_nemo-build() {
    local pkg="nemo-build"
    environment_check_specific "$pkg" || fatal "$pkg: environment check failed"
    local m=$(get_field "$1" 2 "=")
    local V=$(get_field "$2" 2 "=")
    du_gitclone_recursive "$pkg" "https://earth.bsc.es/gitlab/amedvede/nemo-build.git" "$V" "$m"
    cd nemo-build.src
    ./dnb.sh :d
    ./dnb.sh 
    cd $INSTALL_DIR
    if this_mode_is_set "i" "$m"; then
        mkdir -p "$pkg"-"$V"
        cp -a "$pkg"-"$V".src/sandbox/* "$pkg"-"$V"
    fi
    i_make_binary_symlink "$pkg" "${V}" "$m"
}

export TESTSUITE_PACKAGES="nemo-build"
export TESTSUITE_VERSIONS="nemo-build:HEAD"
