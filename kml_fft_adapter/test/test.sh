#c2c
echo c2c 1d
./bench --report-mflops --speed ocf32768 #1d
echo c2c 2d
./bench --report-mflops --speed ocf1024x1024 #2d
echo c2c 3d
./bench --report-mflops --speed ocf256x256x256 #3d
echo c2c row
./bench --report-mflops --speed ocf1024:1:1v1024:1024:1024 #row
echo c2c col
./bench --report-mflops --speed ocf4096v4096 #col
#r2c
echo r2c 1d
./bench --report-mflops --speed orf32768 #1d
echo r2c 2d
./bench --report-mflops --speed orf1024x1024 #2d
echo r2c 3d
./bench --report-mflops --speed orf256x256x256 #3d
echo r2c row
./bench --report-mflops --speed orf1024:1:1v1024:1024:1024 #row
echo r2c col
./bench --report-mflops --speed orf4096v4096 #col