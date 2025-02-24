#!/bin/bash

default_branch="master"
default_conf="generic"
default_suites="basic"
default_hwconf="generic"

app="teststub"

export TESTSUITE_HWCONF=${TESTSUITE_HWCONF:-${default_hwconf}}
export TESTSUITE_PROJECT="$app"
export TESTSUITE_BRANCH=${1:-${default_branch}}
export TESTSUITE_SUITES="${2:-${default_suites}}"
export TESTSUITE_BUILD_CONF=${default_conf}

source ./testall.sh

