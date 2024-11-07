#!/usr/bin/env bash

function usage() {
    echo "$0 usage:" && grep " .)\ #" $0
    exit 0
}

[ $# -eq 0 ] && usage

while getopts "s:f:h" arg; do
    case $arg in
        s) # The size of the array to sort
            size=${OPTARG}
            ;;
        f) # The plot file name
            name=${OPTARG}
            ;;
        h | *) # Display help if options are missing or incorrect
            usage
            exit 0
            ;;
    esac
done

if [ -z "$name" ] || [ -z "$size" ]; then
    usage
    exit 1
fi

if [ -e ./myprogram ]; then
    if [ -e "data.dat" ]; then
        rm -f data.dat
    fi

    echo "Running myprogram to generate data"
    echo "# Time Threads" > data.dat

    for n in {1..32}; do
        echo -ne "Running with $n threads\r"
        total_time=0
        runs=5  # Number of runs to average

        for i in $(seq 1 $runs); do
            result=$(./myprogram "$size" "$n" | grep "Time taken")
            time=$(echo "$result" | awk '{print $3}')
            total_time=$(echo "$total_time + $time" | bc)
        done

        avg_time=$(echo "$total_time / $runs" | bc -l)
        echo "$avg_time $n" >> data.dat
    done

    gnuplot -e "filename='$name.png'" graph.plt
    echo "Created plot $name.png from data.dat file"
else
    echo "myprogram is not present in the root directory. Did you compile your code?"
fi
