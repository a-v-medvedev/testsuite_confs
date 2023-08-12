#!/bin/bash

function env_init_global {
    echo "=== Specific Environment settings for 'LUMI-C' host ==="
    script=$(mktemp .XXXXXX.sh)
cat > $script << 'EOM'

module load LUMI/23.03 partition/G PrgEnv-cray/8.3.3 cce/15.0.1 cray-mpich/8.1.25 cray-hdf5/1.12.1.5 cray-netcdf/4.8.1.5 CrayEnv Subversion/1.14.2

export FC=ftn

export MAKE_PARALLEL_LEVEL=1

export PSUBMIT_OPTS_NNODES=1
export PSUBMIT_OPTS_PPN=56
export PSUBMIT_OPTS_NGPUS=7
export PSUBMIT_OPTS_QUEUE_NAME=small
export PSUBMIT_OPTS_TIME_LIMIT=10
export PSUBMIT_OPTS_ACCOUNT=project_465000454
export PSUBMIT_OPTS_INIT_COMMANDS='"module load LUMI/23.03 partition/G PrgEnv-cray/8.3.3 cce/15.0.1 cray-mpich/8.1.25 cray-hdf5/1.12.1.5 cray-netcdf/4.8.1.5"'
export PSUBMIT_OPTS_INJOB_INIT_COMMANDS='"export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH"'
export PSUBMIT_OPTS_MPI_SCRIPT=cray-srun
export PSUBMIT_OPTS_BATCH_SCRIPT=slurm

export PSUBMIT_OPTS_DIRECT_OVERSUBSCRIBE_LEVEL=4

export DNB_NOCUDA=1
export DNB_NOCMAKE=1
export DNB_NOCCOMP=1
export DNB_NOCXXCOMP=1

# Download is slow, so we normally do build in two stages: "./dnb.sh :d" and "./dnb.sh"
export DEFAULT_BUILD_MODE=":ubi"

source nemo-build.inc

EOM
    . $script
    cat $script
    rm $script
    echo "============================================================"
}


function env_init {
    local name="$1"
    local necdf_path=""
    local hdf5_path=""
    if [ ! -z "$NEMO_USE_PREBUILD_PREREQS" ]; then
        necdf_path="/opt/cray/pe/netcdf/4.8.1.5/crayclang/14.0"
        hdf5_path="/opt/cray/pe/hdf5/1.12.1.5/crayclang/14.0"
    fi

    case "$name" in
    netcdf-c)
        # put here any specific env. setting before build
    ;;
    netcdf-fortran)
        # put here any specific env. setting before build
    ;;
    xios)
        export XIOS_HDF5_PATH="$hdf5_path"
        export XIOS_NETCDF_C_PATH="$necdf_path"
        export XIOS_NETCDF_FORTRAN_PATH="$necdf_path"
        export XIOS_MAKE_PARALLEL_LEVEL="1"
        export XIOS_CCOMPILER="mpicc"
        export XIOS_FCOMPILER="mpif90"
        export XIOS_LINKER="mpif90"
        export XIOS_CFLAGS="-std=c++03 -O3 -D BOOST_DISABLE_ASSERTS"
        export XIOS_CPP="mpicc -EP"
        export XIOS_FPP="cpp -P"
    ;;
    nemo)
        export NEMO_HDF5_PATH="$hdf5_path"
        export NEMO_NETCDF_C_PATH="$necdf_path"
        export NEMO_NETCDF_FORTRAN_PATH="$necdf_path"
        export NEMO_XIOS_PATH="$INSTALL_DIR/xios.bin"
        export NEMO_CPP="cpp"
        export NEMO_CC="gcc"
        export NEMO_FC="mpif90"
        export NEMO_FCFLAGS="-O3"
        export NEMO_LDFLAGS="-lstdc++"
        export NEMO_FPPFLAGS="-P -traditional -I/opt/cray/pe/mpich/8.1.25/ofi/cray/10.0/include"
    ;;
    esac
    return 0
}

