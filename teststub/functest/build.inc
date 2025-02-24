# vim: set filetype=sh :

function dnb_teststub() {
    generic_prolog "teststub" $* || return 0
    du_github "a-v-medvedev" ""
	bi_make "" "THIRDPARTY=.." "teststub"
    i_psubmit_opt
    generic_epilog
}


#    NOTE: if a project has its own dnb.sh:
#    ------
#    if this_mode_is_set "b"; then
#        cd "$pkg"-"$V".src
#        local old_install_dir=$DNB_INSTALL_DIR        
#		 cd thrirdparty
#		 DNB_INSTALL_DIR=$PWD
#		 export DNB_SUPERIOR="../.."
#		 ./dnb.sh
#		 DNB_INSTALL_DIR="$old_install_dir"
#        cd $DNB_INSTALL_DIR
#    fi
#    -------

