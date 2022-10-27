#c2c
./bench --report-mflops --speed ocf32768 #1d
./bench --report-mflops --speed ocf1024x1024 #2d
./bench --report-mflops --speed ocf256x256x256 #3d
./bench --report-mflops --speed ocf1024:1:1v1024:1024:1024 #row
./bench --report-mflops --speed ocf1024v1024 #col
#r2c
./bench --report-mflops --speed orf32768 #1d
./bench --report-mflops --speed orf1024x1024 #2d
./bench --report-mflops --speed orf256x256x256 #3d
./bench --report-mflops --speed orf1024:1:1v1024:1024:1024 #row
./bench --report-mflops --speed orf1024v1024 #col
#c2r
./bench --report-mflops --speed orb32768 #1d
./bench --report-mflops --speed orb1024x1024 #2d
./bench --report-mflops --speed orb256x256x256 #3d
./bench --report-mflops --speed orb1024:1:1v1024:1024:1024 #row
./bench --report-mflops --speed orb1024v1024 #col

#c2c thread
./bench --user-option=nthreads=48 --report-mflops --speed ocf32768 #1d
./bench --user-option=nthreads=48 --report-mflops --speed ocf1024x1024 #2d
./bench --user-option=nthreads=48 --report-mflops --speed ocf256x256x256 #3d
./bench --user-option=nthreads=48 --report-mflops --speed ocf1024:1:1v1024:1024:1024 #row
./bench --user-option=nthreads=48 --report-mflops --speed ocf1024v1024 #col
#r2c thread
./bench --user-option=nthreads=48 --report-mflops --speed orf32768 #1d
./bench --user-option=nthreads=48 --report-mflops --speed orf1024x1024 #2d
./bench --user-option=nthreads=48 --report-mflops --speed orf256x256x256 #3d
./bench --user-option=nthreads=48 --report-mflops --speed orf1024:1:1v1024:1024:1024 #row
./bench --user-option=nthreads=48 --report-mflops --speed orf1024v1024 #col
#c2r thread
./bench --user-option=nthreads=48 --report-mflops --speed orb32768 #1d
./bench --user-option=nthreads=48 --report-mflops --speed orb1024x1024 #2d
./bench --user-option=nthreads=48 --report-mflops --speed orb256x256x256 #3d
./bench --user-option=nthreads=48 --report-mflops --speed orb1024:1:1v1024:1024:1024 #row
./bench --user-option=nthreads=48 --report-mflops --speed orb1024v1024 #col