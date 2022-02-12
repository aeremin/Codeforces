set -e

cd common
./health_check.sh
cd ..

cd alexey
./health_check.sh
cd ..

cd andrei
./health_check.sh
cd ..
