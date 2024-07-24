#!/usr/bin/env sh
# Runs a suite of benchmarks on the fgt C++ library.

modes="direct_tree ifgt"
rows="100 400 1000 4000 10000 40000"
bandwidths="0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1"
niter=3

for mode in ${modes}; do
    for row in ${rows}; do
        for bandwidth in ${bandwidths}; do
            printf "%s %s %s" $mode $row $bandwidth
            for i in `seq 1 ${niter}`; do
                printf " %s" $(./1d_normal $mode $row $bandwidth)
            done
            printf "\n"
        done
    done
done
