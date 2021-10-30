#!/bin/bash
make clean
make
make clean
chmod u+x ./bin/main

rm -f ./solutions/*


for file in ./instances/*.dat; do
#    [ -f "$file" ] || continue
    ./bin/main "$file"
done
