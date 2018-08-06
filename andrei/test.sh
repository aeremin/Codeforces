set -e

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 contest problem (e.g. $0 239 a)"
    exit 1
fi

cd "codeforces/$1/build/"
make "${2}_solver"
"./${2}_solver"
