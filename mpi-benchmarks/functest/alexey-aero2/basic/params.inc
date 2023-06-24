export MASSIVE_TESTS_DRIVER="functest"
export MASSIVE_TESTS_APPLICATION="teststub"

# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4

# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=3

# Scope:
export MASSIVE_TESTS_NODES="2 4"
export MASSIVE_TESTS_PPNS=1

# Sizes:
export MASSIVE_TESTS_WORKPARTS="sync async"
export MASSIVE_TESTS_REPEATS="3"

# Workloads, sections and params:
WORKLOADS="pt2pt"
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
    if [ "$wrpt" == "sync" -o "$V" != "P" ]; then
        echo "$V"
        return 
    fi
    get_value_aux "$L"
    if [ ! -z $aux1_sync_4 ]; then sync=$aux1_sync_4; fi
    L=$(get_line_from_output_yaml $file $keywords $key_block $wrptkeyword sync $n)    
    get_value_aux "$L"
    if [ ! -z $aux1_async_4 ]; then async=$aux1_async_4; fi
    if [ ! -z $aux1_over_full_4 ]; then over_full=$aux1_over_full_4; fi
    echo "$over_full" "$sync" | awk '{ printf("%d%%", int(100.0 * float($1) / float($2) + 0.5); }' 2>/dev/null || echo "??" && true
}
