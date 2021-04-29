#!/bin/bash

function env_init_global {
    echo "=== Specific Environment settings for 'mars' host ==="
    script=$(mktemp .XXXXXX.sh)
cat > $script << 'EOM'

export MAKE_PARALLEL_LEVEL=10

export PSUBMIT_OPTS_NNODES=1
export PSUBMIT_OPTS_PPN=1
export PSUBMIT_OPTS_NGPUS=1
export PSUBMIT_OPTS_QUEUE_NAME=test
export PSUBMIT_OPTS_QUEUE_SUFFIX=
export PSUBMIT_OPTS_NODETYPE=
export PSUBMIT_OPTS_INIT_COMMANDS=
export PSUBMIT_OPTS_MPI_SCRIPT=generic
export PSUBMIT_OPTS_BATCH_SCRIPT=direct

export PSUBMIT_OPTS_CPER10USEC=33

export XAMG_IGNORE_AFFINITY=1

export DNB_NOCUDA=1
export DNB_NOCCOMP=1


EOM
    . $script
    cat $script
    rm $script
    echo "============================================================"
}


function env_init {
    local name="$1"
    case "$name" in
    scotch)
        # put here any specific env. setting before scotch build
    ;;
    yaml-cpp)
        # put here any specific env. setting before yaml-cpp build
    ;;
    argsparser)
        # put here any specific env. setting before silo build
    ;;
    massivetests)
        # put here any specific env. setting before scotch build
    ;;
    mpi-benchmarks)
        # put here any specific env. setting before yaml-cpp build
    ;;
    testsuite)
        # put here any specific env. setting before silo build
    ;;
    XAMG)
        # put here any specific env. setting before silo build
    ;;
    esac
    return 0
}

