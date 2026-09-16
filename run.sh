#!/bin/bash

rm -f main
g++ -c src/*.cpp -DDEBUG=0 -I/home/root/Scopa/lib
find -maxdepth 1 -name '*.o' ! -name 'main.o' -print0 | xargs -0 mv -t lib/
g++ main.o lib/*.o -o main
rm -f main.o
chmod +x main
script -q -c "./main" session.log
