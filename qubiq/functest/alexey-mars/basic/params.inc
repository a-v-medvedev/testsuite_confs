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
export MASSIVE_TESTS_APPLICATION="qubiq"


# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4


# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=3


# Scope:
export MASSIVE_TESTS_NODES="1 2 3 4"
export MASSIVE_TESTS_PPNS=1
[ -z "$MASSIVE_TESTS_PPNS" ] && fatal "PSUBMIT_OPTS_PPN is not set."


# Sizes:
export MASSIVE_TESTS_WORKPARTS="Tube_s1_10_tet.cgns"
export MASSIVE_TESTS_REPEATS="1"


# Workloads, sections and params:
WORKLOADS="sod-1p"
CONFS="X"

SECTIONS="xxx"
PARAMETERS="ALL"

# Modes and submodes:
MODES="X"
SUBMODES="X"

function get_value() {
    local line=$1
    echo "$line" | awk -F '[ :{},]*' '{ for (v=1; v<=NF; v++) { if (flag==1) {flag=0; print $v} if ($v=="Value") flag=1; } }'
}
