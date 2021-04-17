#!/bin/bash

function parse_yaml {
   local prefix=$2
   local s='[[:space:]]*' w='[a-zA-Z0-9_]*' fs=$(echo @|tr @ '\034')
   sed -ne "s|^\($s\):|\1|" \
        -e "s|^\($s\)\($w\)$s:$s[\"']\(.*\)[\"']$s\$|\1$fs\2$fs\3|p" \
        -e "s|^\($s\)\($w\)$s:$s\(.*\)$s\$|\1$fs\2$fs\3|p"  $1 |
   awk -F$fs '{
      indent = length($1)/2;
      vname[indent] = $2;
      for (i in vname) {if (i > indent) {delete vname[i]}}
      if (length($3) > 0) {
         vn=""; for (i=0; i<indent; i++) {vn=(vn)(vname[i])("_")}
         printf("%s%s%s=\"%s\"\n", "'$prefix'",vn, $2, $3);
      }
   }'
}

eval $(parse_yaml $1)

if [ "${info_nprocs}" == "1" ]; then
VSTR=$(echo $spmv_Y_norm | awk -F'[\\[\\], ]+' '{ for (i=1;i<NF+1;i++) if ($i != "") { V=$i; n++} } END { if (n) printf "spmv/Y_norm[" n-1 "]: %.10f", V; }')

#if [ "axpby/NV1/@@1000000" == "${blas_operation}/NV${info_NV}/@@${info_size}" ]; then
echo -ne "spmv/NV${info_NV}/${info_matrix}:\t"
echo -ne "    values:\t"
echo -ne "        $VSTR\t"
echo
#fi
fi
