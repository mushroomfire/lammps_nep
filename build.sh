# To compile the LAMMPS Python interface.
#!/usr/bin/env bash

cd lammps/src
if [ "$(expr substr $(uname -s) 1 10)" != "MINGW64_NT" ]; then
    dos2unix USER-NEP/Install.sh 
    dos2unix Depend.sh
    dos2unix Fetch.sh
fi
make yes-USER-NEP
cd ..
mkdir build && cd build
if [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then  
    echo "Windows NT"
    cmake -C ../cmake/presets/basic.cmake -D BUILD_MPI=no -D BUILD_OMP=no -D BUILD_SHARED_LIBS=yes ../cmake
    cmake --build . --config Release --parallel 4
    cd ../python  
    rm ./*.whl
    python ./install.py -p lammps -l ../build/Release/liblammps.dll -v ../src/version.h -n
    cd ../..
    cp lammps/python/lammps*.whl .
else
    echo "GNU/Linux"
    cmake -C ../cmake/presets/basic.cmake -D BUILD_MPI=no -D BUILD_OMP=no -D BUILD_SHARED_LIBS=yes ../cmake
    make -j 4
    cd ../python
    rm ./*.whl
    python ./install.py -p lammps -l ../build/liblammps.so -v ../src/version.h -n
    cd ../..
    cp lammps/python/lammps*.whl .
fi

echo "Install wheel..."
pip install ./lammps*.whl
echo "All done!"