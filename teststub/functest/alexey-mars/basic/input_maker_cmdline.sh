#!/bin/bash

function fatal() {
    local msg="$1"
    echo "FATAL: $msg"
    exit 1
}


function parse_arg() {
    local arg=$1
    local varname=$(echo $arg | awk -F= '{print $1}' | sed 's/MASSIVE_TESTS_TESTITEM_//')
    local value=$(echo $arg | awk -F= '{print $2}')
    [ -z "$value" -o -z "$varname" ] && exit 1
    eval "$varname=$value"
}

for i in $*; do
    parse_arg $i
done

[ -z "$WLD" ] && fatal "input_maker_cmdline.sh logic error: workload parameter is empty or not set"

# WLD CONF WPRT WPRT_PARAMS NP PPN TIMEOUT
#
# { WLD, CONF } -- worload name and configuration name
# { WPRT, WPRT_PARAMS } -- workpart name and its numeric parameter (typically, numer of iterations)
# { NP, PPN } -- number of nodes and number of processes per node for this MPI session
# TIMEOUT -- numeric timeout parametee in seconds
#
# TESTITEM__xxx_yyy  -- records from test_items,yaml that correspond to this test item
#
# Return value: non-zero return value means that this test will be skipped, message will be copied to massivetest log
#

if [ "$MASSIVETEST_AUX_ARGS" == "-mode always -code T"  ]; then
    echo "I'm too lazy for this ($*)" >&2
    exit 1
fi
echo "-load input_$WLD.yaml -output result.%PSUBMIT_JOBID%.yaml -timeout $TIMEOUT $MASSIVETEST_AUX_ARGS"
exit 0


