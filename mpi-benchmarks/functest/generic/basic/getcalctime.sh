#!/bin/bash

ROUNDUP_STEP=10
OUTPUT_YAML=result.${PSUBMIT_JOBID}.yaml
[ -f "$OUTPUT_YAML" ] || { echo ">> FATAL: $(basename $0): can't open file $OUTPUT_YAML"; exit 1; }
CALCTIME=calctime_${MASSIVE_TESTS_TESTITEM_WLD}_${MASSIVE_TESTS_TESTITEM_NP}.txt
cat "$OUTPUT_YAML" | sed 's/[{},]/\n/g' | sed 's/^[ ]*//;s/://' | awk -v rounding=$ROUNDUP_STEP '/tavg/{start=1} /over_full/{start=0} { if (start && NF==2) { x=int($2*1.2e6)+1; x=((int(x/rounding))+((x%rounding)?1:0))*rounding; R[$1]=x; } } END { PROCINFO["sorted_in"]="@ind_num_asc"; for (i in R) printf R[i] ","; printf "\n" }' | sed '{s/,$//}' > $CALCTIME

