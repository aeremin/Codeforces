set -e

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 solution_file"
    exit 1
fi

tmpfile=$(mktemp --suffix=.cpp)
./build.dbg/solution_fuser --include-path lib --include-path ../common/lib --input-file $1 > "${tmpfile}"
cd /tmp
clang++ -std=c++17 "${tmpfile}"
cat "${tmpfile}" | xclip -sel clip
