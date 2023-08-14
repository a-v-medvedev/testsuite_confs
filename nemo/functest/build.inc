# vim: set filetype=sh :

function dnb_nemo-build() {
    local pkg="nemo-build"
    environment_check_specific "$pkg" || fatal "$pkg: environment check failed"
    local m=$(get_field "$1" 2 "=")
    local V=$(get_field "$2" 2 "=")
    [ "$m" == "d" ] && m="du"
    du_gitlab "amedvede" "$pkg" "" "$V" "$m" "earth.bsc.es/gitlab"
    if this_mode_is_set "u" "$m" && this_mode_is_set "d" "$m"; then
        rm -rf nemo-build-root
    	[ -d ${pkg}-${V}.src ] &&  mv ${pkg}-${V}.src nemo-build-root
        cd nemo-build-root
    	ln -s ../../env.sh .
        if [ -d dbscripts ]; then
            rm -rf dbscripts
            ln -s ../dbscripts .
        fi
        rm -f eORCA1_OCE_ICE_DE340.tar nemo_de340.tgz ORCA2_ICE_v4.0.tar 
        cd $INSTALL_DIR
    fi
    cd nemo-build-root
    this_mode_is_set "d" "$m" && ./dnb.sh :d
    this_mode_is_set "u" "$m" && ./dnb.sh :u 
    this_mode_is_set "b" "$m" && ./dnb.sh :b
    this_mode_is_set "i" "$m" && ./dnb.sh :i
    cd $INSTALL_DIR
    if this_mode_is_set "i" "$m"; then
        mkdir -p "$pkg"-"$V"
        cp -a nemo-build-root/sandbox/* "$pkg"-"$V"
    fi
    i_make_binary_symlink "$pkg" "${V}" "$m"
}

export TESTSUITE_MODULE=functest
export TESTSUITE_PROJECT=teststub
#TESTSUITE_BUILD_CONF=
export TESTSUITE_SCRIPT="functional"
export TESTSUITE_PACKAGES="nemo-build"
export TESTSUITE_VERSIONS="nemo-build:HEAD"
