set -e
mkdir -p build.dbg
cd build.dbg
cmake ..
make -j8
./codeforces --gtest_filter=-*NoTravis*:*582E*:*AlexeyTopologySort*
