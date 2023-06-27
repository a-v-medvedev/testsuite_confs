# vim: set filetype=sh :

export MASSIVE_TESTS_DRIVER="functest"
export MASSIVE_TESTS_APPLICATION="teststub"

# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4

# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=3

# Scope:
export MASSIVE_TESTS_NODES="2 4 6"
export MASSIVE_TESTS_PPNS=28

# Sizes:
export MASSIVE_TESTS_WORKPARTS="calibration"
export MASSIVE_TESTS_REPEATS="1"

# Workloads, sections and params:
WORKLOADS="calibration"
CONFS="X"
SECTIONS="ALL"
PARAMETERS="ALL"

# Modes and submodes:
MODES="X"
SUBMODES="X"

function get_value_extended() {
    local file=$1
    local keywords="$2"
    local key_block="$3"
    local wrptkeyword="$4"
    local wrpt="$5"
    local n="$6"
    L=$(get_line_from_output_yaml $file $keywords $key_block $wrptkeyword $wrpt $n)    
    V=$(get_value_simple "$L")
    if [ "$V" != "P" ]; then
        echo "$V"
        return 
    fi
    get_value_aux "$L"
    if [ "$aux1_irregularity" != "0" ]; then
        echo "F"
        return
    fi
    VALUE="${aux1_avg}(${aux1_min}/${aux1_max})"
    echo $VALUE
}
