#!/bin/bash
#BSUB -n 24
#BSUB -q p
module load intel/2016 
mpirun -np 24 root "../macro/trigger/mtx_gate.C(6,5126)" 
