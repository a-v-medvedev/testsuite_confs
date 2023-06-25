# vim: set filetype=sh :

export MASSIVE_TESTS_DRIVER="functest"
export MASSIVE_TESTS_APPLICATION="teststub"

# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4

# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=20

# Scope:
export MASSIVE_TESTS_NODES="2 4 6"
export MASSIVE_TESTS_PPNS=28

# Sizes:
export MASSIVE_TESTS_WORKPARTS="sync async"
export MASSIVE_TESTS_REPEATS="1"

# Workloads, sections and params:
WORKLOADS="pt2pt"
CONFS="X"
SECTIONS="ALL"
PARAMETERS="ALL"

# Modes and submodes:
MODES="NOPROG MANUAL5 MANUAL10 MANUAL20"
SUBMODES="X"

export MASSIVE_TESTS_COLUMN_WIDTH=24

function calc_efficiency() {
    local len=$1
    eval async=\$aux1_async_$len
    eval over=\$aux1_over_$len
    eval sync=\$aux1_sync_$len
    V=$(echo "$over" "$sync" | awk '{ printf("%d", int(100.0 - 100.0 * $1 / $2 + 0.5)); }' 2>/dev/null || echo "??")
    [ -z "$VALUE" ] || VALUE="${VALUE},"
    VALUE="${VALUE}${V}"
}

function get_value_extended() {
    local file=$1
    local keywords="$2"
    local key_block="$3"
    local wrptkeyword="$4"
    local wrpt="$5"
    local n="$6"
    L=$(get_line_from_output_yaml $file $keywords $key_block $wrptkeyword $wrpt $n)    
    V=$(get_value_simple "$L")
    if [ "$wrpt" == "sync" -o "$V" != "P" ]; then
        echo "$V"
        return 
    fi
    VALUE=""
    get_value_aux "$L"
    L=$(get_line_from_output_yaml $file $keywords $key_block $wrptkeyword sync $n)    
    get_value_aux "$L"
    calc_efficiency 4
    calc_efficiency 512
    calc_efficiency 16384
    calc_efficiency 131072
    calc_efficiency 4194304
    echo $VALUE
}
