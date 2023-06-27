function env_init_global {
    echo "=== Specific Environment settings for KIAE supercomputer ==="
    script=$(mktemp .XXXXXX.sh)
cat > $script << 'EOM'
. /s/ls4/sw/intel/mkl/2018.3.222/mkl/bin/mklvars.sh intel64
module load python/2.7.14 cuda/11.4 cmake/3.16.2
module load openmpi/4.1.0-gcc7
module load gcc/10.2.0
export PATH=/s/ls4/sw/gcc/10.2.0/bin:$PATH
export LD_LIBRARY_PATH=/s/ls4/sw/openmpi/4.1.0/lib:/s/ls4/sw/gcc/10.2.0/lib64:/s/ls4/sw/gcc/10.2.0/lib

export PATH=$HOME/bin/psubmit:$PATH

unset CXX; export CXX
unset CC; export CC

#module load intel-parallel-studio/2017
#export I_MPI_HYDRA_BOOTSTRAP=slurm

export CUDA_CC=35
export CUDA_ARCH="-arch=sm_${CUDA_CC}"
export CUDA_GENCODE="arch=compute_${CUDA_CC},code=sm_${CUDA_CC}"

export MAKE_PARALLEL_LEVEL=8

export PSUBMIT_OPTS_NNODES=4
export PSUBMIT_OPTS_PPN=28
export PSUBMIT_OPTS_NGPUS=0
export PSUBMIT_OPTS_QUEUE_NAME=hpc4-el7-3d
export PSUBMIT_OPTS_QUEUE_SUFFIX=
export PSUBMIT_OPTS_NODETYPE=
export PSUBMIT_OPTS_INIT_COMMANDS=
export PSUBMIT_OPTS_MPI_SCRIPT=ompi4
export PSUBMIT_OPTS_BATCH_SCRIPT=slurm
export IMBASYNC_CPER10USEC=4
#calib const 14

EOM
    . ./$script
    cat $script
    rm $script
    echo "============================================================"
}


function env_init {
    local name="$1"
    case "$name" in
    lammps)
    ;;
    foam-extend)
        export MAKE_PARALLEL_LEVEL=16
    ;;
    gromacs)
    ;;
    q-e-gpu)
        export F90=pgf90
        export FC=pgf90
        export F77=pgf77
        export MPIF90=pgf90
        export PATH=$HOME/pgi/linux86-64/19.10/bin:$PATH
        # NOTE: if pgf90 is a hand-written wrapper, we put it to $HOME/bin and place a path to it before actual pgf90
        export PATH=$HOME/bin:$PATH
        [ -e $HOME/bin/pgf90 ] || ( echo "FATAL: This environment requires a wrapper: $HOME/bin/pgf90"; exit 1 )
        ###############
        export OMPI_INCLUDE_FLAGS_F90="-I/usr/include/openmpi-x86_64 -I/usr/lib64/openmpi/lib -I."
        export OMPI_LIBS_F90="-Wl,-rpath -Wl,/usr/lib64/openmpi/lib -Wl,--enable-new-dtags -L/usr/lib64/openmpi/lib -lmpi_usempi -lmpi_mpifh -lmpi"
        export JOBRUN_OPTS_PPN=4
        return 1;
    ;;
    namd)
        OMPI_CXX_LIBOPTS="-lmpi_cxx"
        return 1
    ;;
    yaml-cpp)
        ;;

    esac
    return 0
}
