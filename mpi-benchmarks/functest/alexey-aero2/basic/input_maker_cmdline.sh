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
[ -z "$IMBASYNC_CPER10USEC" ] && fatal "\$IMBASYNC_CPER10USEC shell variable is required to defile a dummy loop calibration constant."

LEN="4,512,16384,131072,4194304"
NCYCLES="10000,1000,50,10,5"
IMBASYNC_BASIC="-datatype char -len $LEN -ncycles $NCYCLES -output result.%PSUBMIT_JOBID%.yaml"
if [ "$WPRT" == "sync" ]; then
    echo "$IMBASYNC_BASIC" sync_$WLD
elif [ "$WPRT" == "async" ]; then
    IMBASYNC_WORKLOAD_PARAMS="cpu_calculations=true:gpu_calculations=false:cycles_per_10usec=$IMBASYNC_CPER10USEC"
    IMBASYNC_WORKLOAD_PARAMS="$IMBASYNC_WORKLOAD_PARAMS:manual_progress=true"
    [ ! -f calctime_${WLD}_${NP}.txt ] && fatal "No file calctime_${WLD}_${NP}.txt"
    [ $(wc -l < calctime_${WLD}_${NP}.txt) != "1" ] && fatal "Wrong format of file calctime_${WLD}_${NP}.txt"
    [ $(wc -c < calctime_${WLD}_${NP}.txt) -lt "2" ] && fatal "Wrong format of file calctime_${WLD}_${NP}.txt"
    echo "$IMBASYNC_BASIC -workload_params $IMBASYNC_WORKLOAD_PARAMS -calctime $(cat calctime_${WLD}_${NP}.txt)" async_$WLD
fi
exit 0

