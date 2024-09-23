# To compile the LAMMPS module for different python versions.
#!/usr/bin/env bash

cd lammps/src
if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    dos2unix USER-NEP/Install.sh 
    dos2unix Depend.sh
    dos2unix Fetch.sh
fi
make yes-USER-NEP
cd ..

if [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then  
    echo "Windows NT"
    mkdir build_win
    cd build_win
    cmake -C ../cmake/presets/windows.cmake -D BUILD_MPI=no -D BUILD_OMP=no -D BUILD_SHARED_LIBS=yes ../cmake
    cmake --build . --config Release --parallel 4
    cd ../python  
    python ./install.py -p lammps -l ../build_win/Release/liblammps.dll -v ../src/version.h -n
    cd ../..
    cp lammps/python/lammps*.whl .
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    echo "GNU/Linux"
    mkdir build_linux
    cd build_linux
    cmake -C ../cmake/presets/basic.cmake -D BUILD_MPI=no -D BUILD_OMP=no -D BUILD_SHARED_LIBS=yes ../cmake
    make -j 4
    cd ../python
    python ./install.py -p lammps -l ../build_linux/liblammps.so -v ../src/version.h -n
    cd ../..
    cp lammps/python/lammps*.whl .
fi
