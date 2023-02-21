#!/bin/bash



function parse_arg() {
    local arg=$1
    local varname=$(echo $arg | awk -F= '{print $1}')
    local value=$(echo $arg | sed "s/$varname=//")
    [ -z "$value" -o -z "$varname" ] && exit 1
    eval "$varname=$value"
}

for i in $*; do
    parse_arg $i
done

[ -z "$WLD" ] && exit 1

# WLD CONF WPRT WPRT_PARAMS NP PPN TIMEOUT

if [ "$MASSIVETEST_AUX_ARGS" == "-mode always -code T"  ]; then
    echo "I'm too lazy for this ($*)" >&2
    exit 1
fi
echo "-load input_$WLD.yaml -output result.%PSUBMIT_JOBID%.yaml -timeout $TIMEOUT $MASSIVETEST_AUX_ARGS"
exit 0


