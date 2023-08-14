# vim: set filetype=sh :

function dnb_nemo-build() {
    local pkg="nemo-build"
    environment_check_specific "$pkg" || fatal "$pkg: environment check failed"
    local m=$(get_field "$1" 2 "=")
    local V=$(get_field "$2" 2 "=")
    du_gitclone_recursive "$pkg" "https://earth.bsc.es/gitlab/amedvede/nemo-build.git" "$V" "$m"
    cd ${pkg}-${V}.src
    ln -s ../../env.sh .
    this_mode_is_set "d" "$m" && ./dnb.sh :d
    this_mode_is_set "u" "$m" && ./dnb.sh :u 
    this_mode_is_set "b" "$m" && ./dnb.sh :b
    this_mode_is_set "i" "$m" && ./dnb.sh :i
    cd $INSTALL_DIR
    if this_mode_is_set "i" "$m"; then
        mkdir -p "$pkg"-"$V"
        cp -a "$pkg"-"$V".src/sandbox/* "$pkg"-"$V"
    fi
    i_make_binary_symlink "$pkg" "${V}" "$m"
}

export TESTSUITE_MODULE=functest
export TESTSUITE_PROJECT=teststub
#TESTSUITE_BUILD_CONF=
export TESTSUITE_SCRIPT="functional"
export TESTSUITE_PACKAGES="nemo-build"
export TESTSUITE_VERSIONS="nemo-build:HEAD"
