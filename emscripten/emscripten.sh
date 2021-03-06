#/bin/sh

cd ..
docker run --rm -v $(pwd):/src trzeci/emscripten:sdk-tag-1.37.36-64bit emcc libteol0/teonet_l0_client.c -c -o emscripten/teonet_l0_client.o
docker run --rm -v $(pwd):/src trzeci/emscripten:sdk-tag-1.37.36-64bit emcc main_select_cpp.cpp -std=c++14 emscripten/teonet_l0_client.o -o emscripten/main_select.js -s DEMANGLE_SUPPORT=1 -s NO_EXIT_RUNTIME=0
cd emscripten

# node main_select.js teocli++js gt1.kekalan.net 9010 ps-server
# ../dist/Debug/GNU-Linux/teocli teocli++js gt1.kekalan.net 9010 ps-server
