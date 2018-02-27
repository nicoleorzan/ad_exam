#!/bin/bash


#before script
for size in 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288; do
    echo ${size}
    >times_before_${size}
    >cachemiss_before_${size}
    export OMP_NUM_THREADS=20
    for i in `seq 10`; do
    perf stat -e L1-dcache-misses ./testlog_before.x ${size} &>>tmp_file	
    grep -E "max_sum_before" tmp_file | awk '{print $2}'>>times_before_${size}
    gawk '/L1-dcache-misses/ {print $1}' tmp_file | sed 's/[^0-9]*//g' >> cachemiss_before_${size}
    >tmp_file
    done
done

for size in 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288; do
    echo ${size}
    >times_after_${size}
    >cachemiss_after_${size}
    export OMP_NUM_THREADS=20
    for i in `seq 10`; do
    perf stat -e L1-dcache-misses ./testlog_after.x ${size} &>>tmp_file	
    grep -E "max_sum_after" tmp_file | awk '{print $2}'>>times_after_${size}
    gawk '/L1-dcache-misses/ {print $1}' tmp_file | sed 's/[^0-9]*//g' >> cachemiss_after_${size}
    >tmp_file
    done
done
