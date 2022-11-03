# PLT

Le rapport se trouve dans `rapport/rapport.md`

## Dépendances :
    sudo apt install git dia cmake g++ lcov gcovr libxml2-dev libsfml-dev libboost-test-dev
    sudo apt install ghostscript

## WSL2 :
    export LIBGL_ALWAYS_INDIRECT=1
    export DISPLAY=$(awk '/nameserver / {print $2; exit}' /etc/resolv.conf 2>/dev/null):0
    
## Build and Launch :

    mkdir build
    cd build
    cmake ..
    make
    ./../bin/client

[![Actions Status](https://github.com/cbares/plt/workflows/PLT%20build/badge.svg)](https://github.com/cbares/plt/actions)
