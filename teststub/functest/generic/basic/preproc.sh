#!/bin/bash

# { $WLD, $CONF } -- workload name and configuration name
# { $WPRT, $WPRT_PARAMS } -- workpart name and its numeric parameter (typically, numer of iterations)
# { $NP, $PPN } -- number of nodes and number of processes per node for this MPI session
# $TIMEOUT -- numeric timeout parameter in seconds
#
# $TESTITEM__xxx_yyy  -- records from test_items.yaml that correspond to this test item

set -x

WLD=$MASSIVE_TESTS_TESTITEM_WLD
WPRT=$MASSIVE_TESTS_TESTITEM_WPRT
NP=$MASSIVE_TESTS_TESTITEM_NP

from="generated__${WLD}__${NP}.txt"
to="generated.${PSUBMIT_JOBID}.txt"

[ -e "$from" ] || exit 0
[ -e "$to" ] && exit 0
cp $from $to
echo "copied before processing" >> $to
