set -e

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 contest problem (e.g. $0 239 a)"
    exit 1
fi

./test.sh "$@"
problem_upper=`echo "$2" | awk '{print toupper($0)}'`
solution_file="codeforces/$1/$problem_upper/$2.cpp"
tmpfile=$(mktemp --suffix=.cpp)
./build.dbg/solution_fuser --include-path lib --include-path ../common/lib \
    --input-file "$solution_file" > "$tmpfile"
echo

file_size_bytes=`du -b "$tmpfile" | cut -f1`
file_size_kb=$(( $file_size_bytes / 1024 ))
limit_size_bytes=65536
limit_size_kb=$(( $limit_size_bytes / 1024 ))
warning_threshold_bytes=$(( $limit_size_bytes * 3 / 4 ))
if [[ $file_size_bytes -gt $limit_size_bytes ]]; then
    echo -e "WARNING: file size is \e[1m\e[31m${file_size_kb}KB\e[0m," \
            "which is above Codeforces limit (${limit_size_kb}KB)"
    echo
elif [[ $file_size_bytes -gt $warning_threshold_bytes ]]; then
    echo -e "WARNING: file size is \e[1m\e[33m${file_size_kb}KB\e[0m," \
            "which is close to Codeforces limit (${limit_size_kb}KB)"
    echo
fi

cd /tmp
clang++ -std=c++17 "$tmpfile"
cat "$tmpfile" | xclip -sel clip
