set -e
mkdir -p build.dbg
cd build.dbg
cmake ..
make -j8
./contest_lib_test
