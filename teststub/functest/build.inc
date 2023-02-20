# vim: set filetype=sh :

function dnb_teststub() {
    local pkg="teststub"
    environment_check_specific "$pkg" || fatal "$pkg: environment check failed"
    local m=$(get_field "$1" 2 "=")
    local V=$(get_field "$2" 2 "=")
    du_gitclone_recursive "$pkg" "https://github.com/a-v-medvedev/teststub" "$V" "$m"
    if this_mode_is_set "b" "$m"; then
		[ -e ../env.sh -a ! -e env.sh ] && ln -s ../env.sh env.sh
        cd "$pkg"-"$V".src
        local old_install_dir=$INSTALL_DIR        
		cd thrirdparty
		INSTALL_DIR=$PWD
		export DNB_SUPERIOR="../.."
		./dnb.sh
		INSTALL_DIR="$old_install_dir"
        cd $INSTALL_DIR
    fi
	b_make "$pkg" "$V" "" "THIRDPARTY=thirdparty" "$m"
    i_make_binary_symlink "$pkg" "${V}" "$m"
}


