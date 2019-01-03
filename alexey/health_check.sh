set -e
mkdir -p build
cd build
cmake ..
make -j8
./codeforces --gtest_filter=-*NoTravis*:*582E*:*AlexeyTopologySort*
