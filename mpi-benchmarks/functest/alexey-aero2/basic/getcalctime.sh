#!/bin/bash

OUTPUT_YAML=$1
CALCTIME=calctime_${MASSIVE_TESTS_TESTITEM_WLD}_${MASSIVE_TESTS_TESTITEM_NP}
cat "$OUTPUT_YAML" | sed 's/[{},]/\n/g' | sed 's/^[ ]*//;s/://' | awk '/tavg/{start=1} /over_full/{start=0} { if (start && NF==2) { x=int($2*1.5e6)+1; rounding=100; x=((int(x/rounding))+((x%rounding)?1:0))*rounding; R[$1]=x; } } END { PROCINFO["sorted_in"]="@ind_num_asc"; for (i in R) printf R[i] ","; printf "\n" }' | sed '{s/,$//}' > $CALCTIME

