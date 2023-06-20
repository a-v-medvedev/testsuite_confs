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
export MASSIVE_TESTS_APPLICATION="teststub"

# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4

# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=3

# Scope:
export MASSIVE_TESTS_NODES="1 2 4"
export MASSIVE_TESTS_PPNS=1

# Sizes:
export MASSIVE_TESTS_WORKPARTS="simple"
export MASSIVE_TESTS_REPEATS="3"

# Workloads, sections and params:
WORKLOADS="xxx yyy"
CONFS="X"
SECTIONS="sec1 sec2" 
PARAMETERS="ALL"

# Modes and submodes:
MODES="T A C E"
SUBMODES="always rand50 never"


function parse_yaml {
   local prefix=$2
   local s='[[:space:]]*' w='[a-zA-Z0-9_]*' fs=$(echo @|tr @ '\034')
   echo "$1" | sed -ne "s|,$s\]$s\$|]|" \
        -e ":1;s|^\($s\)\($w\)$s:$s\[$s\(.*\)$s,$s\(.*\)$s\]|\1\2: [\3]\n\1  - \4|;t1" \
        -e "s|^\($s\)\($w\)$s:$s\[$s\(.*\)$s\]|\1\2:\n\1  - \3|;p" | \
   sed -ne "s|,$s}$s\$|}|" \
        -e ":1;s|^\($s\)-$s{$s\(.*\)$s,$s\($w\)$s:$s\(.*\)$s}|\1- {\2}\n\1  \3: \4|;t1" \
        -e    "s|^\($s\)-$s{$s\(.*\)$s}|\1-\n\1  \2|;p" | \
   sed -ne "s|^\($s\):|\1|" \
        -e "s|^\($s\)-$s[\"']\(.*\)[\"']$s\$|\1$fs$fs\2|p" \
        -e "s|^\($s\)-$s\(.*\)$s\$|\1$fs$fs\2|p" \
        -e "s|^\($s\)\($w\)$s:$s[\"']\(.*\)[\"']$s\$|\1$fs\2$fs\3|p" \
        -e "s|^\($s\)\($w\)$s:$s\(.*\)$s\$|\1$fs\2$fs\3|p" | \
   awk -F$fs '{
      indent = length($1)/2;
      vname[indent] = $2;
      for (i in vname) {if (i > indent) {delete vname[i]; idx[i]=0}}
      if(length($2)== 0){  vname[indent]= ++idx[indent] };
      if (length($3) > 0) {
         vn=""; for (i=0; i<indent; i++) { vn=(vn)(vname[i])("_")}
         printf("%s%s%s=\"%s\"\n", "'$prefix'",vn, vname[indent], $3);
      }
   }'
}

function get_value() {
    local line=$1
    eval $(parse_yaml "$line" "local")
    if [ ! -z "$local1_Auxvalues" ]; then
        local aux=$(echo $line | sed 's/^.*Auxvalues: /- /;s/}$//')
        eval $(parse_yaml "$aux" "aux")
    fi
    if [ -z "$aux1_p1" -o "$local1_Value" != "P" ]; then
        echo "$local1_Value" 
    else
        printf "%.4g\n" "$aux1_p1"
    fi
}

