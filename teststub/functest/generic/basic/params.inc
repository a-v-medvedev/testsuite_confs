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

export MASSIVE_TESTS_APPLICATION="teststub"

# Number of simultaineously queued:
export MASSIVE_TESTS_NQUEUED=4

# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=3

# Scope:
export MASSIVE_TESTS_PCONFS="2:1 4:1"

# Sizes:
export MASSIVE_TESTS_WORKPARTS="simple generating waiting"
export MASSIVE_TESTS_WORKPART_PARAMS="3"

# Workloads, sections and params:
WORKLOADS="xxx yyy"
CONFS="X"
SECTIONS="sec1" 
PARAMETERS="p1"

# Modes and submodes:
MODES="T A C E"
SUBMODES="always rand50 never"

