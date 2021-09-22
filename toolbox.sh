#!/usr/bin/env bash

gdb="./bin/gdb-arch-2021-02"
libname="libgamemodeauto.so.0" # Pretend to be gamemode, change this to another lib that may be in /maps (if already using real gamemode, I'd suggest using libMangoHud.so)
tf2_pid=$(pidof hl2_linux)

SUDO=${CH_SUDO:-sudo}

if [[ $EUID -eq 0 ]]; then
    echo "You cannot run this as root." 
    exit 1
fi

rm -rf /tmp/dumps
mkdir -p --mode=000 /tmp/dumps

function load {
    echo "Loading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope > /dev/null
    sudo cp bin/libMistral.so /usr/lib/$libname
    gdbOut=$(
        $gdb -n -q -batch \
        -ex "set auto-load safe-path /usr/lib/" \
        -ex "attach $tf2_pid" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "call \$dlopen(\"/usr/lib/$libname\", 1)" \
        -ex "detach" \
        -ex "quit" 2> /dev/null
    )
    lastLine="${gdbOut##*$'\n'}"
    if [[ "$lastLine" != "\$1 = (void *) 0x0" ]]; then
      echo "Successfully injected!"
    else
      echo "Injection failed, make sure you have compiled."
    fi
}

function load_debug {
    echo "Loading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    sudo cp bin/libMistral.so /usr/lib/$libname
    $gdb -n -q -batch \
        -ex "set auto-load safe-path /usr/lib:/usr/lib/" \
        -ex "attach $tf2_pid" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "call \$dlopen(\"/usr/lib/$libname\", 1)" \
        -ex "continue" \
        -ex "backtrace"
    echo "Successfully loaded!"
}

function build {
    echo "Building cheat..."
    mkdir -p build
    pushd build
    cmake ..
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . --target Mistral -- -j $(nproc --all)
    cwd="$(pwd)"
    cmake --build . --target data || { echo -e "\033[1;31m\nFailed to update /opt/Mistral/data directory! Trying with root rights!\n\033[0m"; $SUDO bash -c "cd \"$cwd\"; cmake --build . --target data" || { echo -e "\033[1;31m\nFailed to update /opt/Mistral/data directory\n\033[0m"; exit 1; } }
    popd
}

function build_debug {
    echo "Building cheat..."
    mkdir -p build
    pushd build
    cmake ..
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build . --target Mistral -- -j $(nproc --all)
    cwd="$(pwd)"
    cmake --build . --target data || { echo -e "\033[1;31m\nFailed to update /opt/Mistral/data directory! Trying with root rights!\n\033[0m"; $SUDO bash -c "cd \"$cwd\"; cmake --build . --target data" || { echo -e "\033[1;31m\nFailed to update /opt/Mistral/data directory\n\033[0m"; exit 1; } }
    popd
}

function pull {
    git pull
}

while [[ $# -gt 0 ]]
do
keys="$1"
case $keys in
    -u|--unload)
        unload
        shift
        ;;
    -l|--load)
        load
        shift
        ;;
    -ld|--load_debug)
        load_debug
        shift
        ;;
    -b|--build)
        build
        shift
        ;;
    -bd|--build_debug)
        build_debug
        shift
        ;;
    -p|--pull)
        pull
        shift
        ;;
    -h|--help)
        echo "
                    Toolbox script for Mistral
==================================================================
|      Argument       |               Description                |
| ------------------- | ---------------------------------------- |
| -l  (--load)        | Load/inject the cheat via gdb.           |
| -ld (--load_debug)  | Load/inject the cheat and debug via gdb. |
| -b  (--build)       | Build to the build/ dir.                 |
| -bd (--build_debug) | Build to the build/ dir as debug.        |
| -p  (--pull)        | Update the cheat.                        |
| -h  (--help)        | Show help.                               |
==================================================================

All args are executed in the order they are written in, for
example, \"-p -b -l\" would update the cheat, then build it, and
then load it into TF2.
"
        exit
        ;;
    *)
        echo "Unknown arg $1, use -h for help"
        exit
        ;;
esac
done