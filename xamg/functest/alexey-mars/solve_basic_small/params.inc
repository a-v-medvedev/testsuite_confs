#!/bin/bash
#
#   This file is part of massivetest.
#
#   Massivetest is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Foobar is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
#
#

export MASSIVE_TESTS_DRIVER="functest"
export MASSIVE_TESTS_APPLICATION="xamg"


# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4


# Repeats in execution:
#MASSIVE_TESTS_EXEC_REPEATS=3
MASSIVE_TESTS_EXEC_REPEATS=1


# Scope:
#export MASSIVE_TESTS_NODES="1 2 4 8"
export MASSIVE_TESTS_NODES="4 8"
export MASSIVE_TESTS_PPNS=1   #$PSUBMIT_OPTS_PPN
[ -z "$MASSIVE_TESTS_PPNS" ] && fatal "PSUBMIT_OPTS_PPN is not set."


# Sizes:
export MASSIVE_TESTS_WORKPARTS="@10x10x10 @5x5x5"
export MASSIVE_TESTS_REPEATS="3"


# Workloads, sections and params:
#WORKLOADS="pjacobi pmg_cheb phsgs bicgstab rjacobi"
WORKLOADS="phsgs"
CONFS="NV1 NV2 NV8"
#CONFS="NV1"
SECTIONS="solver" 
PARAMETERS="ALL"


# Modes and submodes:
MODES="1:1 2:2 1:4"
#MODES="1:1"
SUBMODES="solve"


function get_value() {
    local line=$1
    echo "$line" | awk -F '[ :{},]*' '{ for (v=1; v<=NF; v++) { if (flag==1) {flag=0; print $v} if ($v=="Value") flag=1; } }'
}

