#!/bin/bash

for size in 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768; do #10 20 50 100 150 200 300 500 700 800 1000 1200 1500 3000; do
    echo ${size}
    ./testlog.x ${size} >output_${size}.txt
    grep -E "before" output_${size}.txt | awk '{print $4}'>>output_before_${size}
    grep -E "after" output_${size}.txt | awk '{print $4}'>>output_after_${size}
    #grep -E "maxb" output_${size}.txt | awk '{print $2}'>>output_before_${size}
    #grep -E "maxa" output_${size}.txt | awk '{print $2}'>>output_after_${size}
done
