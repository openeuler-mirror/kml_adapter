rm -rf ./build
mkdir build
cd build
cmake ..
make -j
ln -s libfftw3f.so.1.0.0 libfftw3f.so.3
ln -s libfftw3f.so.1.0.0 libfftw3f_threads.so.3
cmake .. -DFFT_FLOAT_TYPE=double
make -j
ln -s libfftw3.so.1.0.0 libfftw3.so.3
ln -s libfftw3.so.1.0.0 libfftw3_threads.so.3
