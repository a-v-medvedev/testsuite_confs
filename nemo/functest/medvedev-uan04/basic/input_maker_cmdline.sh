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

# This script generates a commant line for a test to run. The command line meant to be the only line
# which this script outputs to stdout.
#
# After parsing the assignments given in the command line, we have the variables:
#
# $WLD $CONF $WPRT $WPRT_PARAMS $NP $PPN $TIMEOUT $TESTITEM__xxx_yyy
#
# { $WLD, $CONF } -- workload name and configuration name
# { $WPRT, $WPRT_PARAMS } -- workpart name and its numeric parameter (typically, numer of iterations)
# { $NP, $PPN } -- number of nodes and number of processes per node for this MPI session
# $TIMEOUT -- numeric timeout parameter in seconds
#
# $TESTITEM__xxx_yyy  -- records from test_items.yaml that correspond to this test item
#
# Script return value: non-zero return value means that this test will be skipped, message will be
# copied to massivetest log
#

[ -z "$WLD" ] && fatal "input_maker_cmdline.sh logic error: workload parameter is empty or not set"
[ -z "$WPRT" ] && fatal "input_maker_cmdline.sh logic error: workpart parameter is empty or not set"

exit 0

