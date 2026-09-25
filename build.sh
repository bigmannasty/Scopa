#!/bin/bash

rm -f bin/main
g++ -c src/*.cpp -DDEBUG=0 -I./inc
find -maxdepth 1 -name '*.o' -print0 | xargs -0 mv -t build/obj/
g++ build/obj/*.o -o bin/main
chmod +x bin/main
if [ -f bin/main ]
	then echo "Build Successful"
fi
