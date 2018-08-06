set -e

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 contest problem (e.g. $0 239 a)"
    exit 1
fi

./test.sh "$@"
problem_upper=`echo "$2" | awk '{print toupper($0)}'`
solution_file="codeforces/$1/$problem_upper/$2.cpp"
tmpfile=$(mktemp --suffix=.cpp)
./build.dbg/solution_fuser --include-path lib --include-path ../common/lib --input-file "$solution_file" > "$tmpfile"
cd /tmp
clang++ -std=c++17 "${tmpfile}"
cat "$tmpfile" | xclip -sel clip
