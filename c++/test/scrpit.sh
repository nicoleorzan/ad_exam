#!/bin/bash

for size in 500000 600000; do  #300000 400000 500000 600000 700000 800000 900000 1000000; do
    echo ${size}
    ./testlog.x ${size} >output_${size}.txt
    grep -E "before" output_${size}.txt | awk '{print $4}'>>output_before_${size}
    grep -E "after" output_${size}.txt | awk '{print $4}'>>output_after_${size}
done
