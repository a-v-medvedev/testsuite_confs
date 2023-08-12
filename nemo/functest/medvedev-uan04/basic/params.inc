# vim: set filetype=sh :

export MASSIVE_TESTS_DRIVER="functest"
export MASSIVE_TESTS_APPLICATION="nemo"

# Number of sumultaineously queued:
export MASSIVE_TESTS_NQUEUED=4

# Repeats in execution:
MASSIVE_TESTS_EXEC_REPEATS=3

# Scope:
export MASSIVE_TESTS_NODES="2 4 6"
export MASSIVE_TESTS_PPNS=8

# Sizes:
export MASSIVE_TESTS_WORKPARTS="16"
export MASSIVE_TESTS_REPEATS="1"

# Workloads, sections and params:
WORKLOADS="eORCA1"
CONFS="X"
SECTIONS="ALL"
PARAMETERS="ALL"

# Modes and submodes:
MODES="CPU GPU"
SUBMODES="X"

export MASSIVE_TESTS_COLUMN_WIDTH=24


