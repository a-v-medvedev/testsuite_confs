#!/bin/bash

default_url="https://github.com/a-v-medvedev/testsuite_confs.git"
default_branch="master"
default_conf="generic"
default_suites="calibration pt2pt-patterns" # collective-patterns

app="mpi-benchmarks"
testdriver="functest"

export TESTSUITE_MODULE="$testdriver"
export TESTSUITE_PROJECT="$app"
export TESTSUITE_SCRIPT="functional"
export TESTSUITE_BRANCH=${1:-${default_branch}}
export TESTSUITE_CONF_URL=${default_url}
export TESTSUITE_SUITES="${2:-${default_suites}}"
export TESTSUITE_BUILD_CONF=${default_conf}

source ./testall.sh

