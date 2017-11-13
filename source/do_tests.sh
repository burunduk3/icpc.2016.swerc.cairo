#!/bin/bash

function die() {
    echo "fatal: $*" >&2
    exit 1
}

function try() {
    "$@" || die "failed: $*"
}

mkdir ../tests/
echo "unpack original tests"
rm -f ../tests/??{,.a}
try tar -xJf tests-original.txz -C ../tests/

test_index=1
function next_test() {
    while :; do
        local test_name="../tests/`printf '%02d' "${test_index}"`"
        [ -f "${test_name}" ] || break
        test_index=$(($test_index + 1))
    done
    try "$@" > "${test_name}"
}

echo "copy manual tests"
for x in *.manual; do
    next_test cat "${x}"
done

echo "generate some tricky large tests"
g++ -O2 -Wall -Wextra -Werror -o g_gen -x c++ -std=c++17 g_gen.c++
g++ -O2 -Wall -Wextra -Werror -o g_gen2 -x c++ -std=c++17 g_gen2.c++

next_test ./g_gen 1 0 11
next_test ./g_gen 1 1 11
next_test ./g_gen 1 2 11
next_test ./g_gen 1 0 249
next_test ./g_gen 1 1 249
next_test ./g_gen 1 2 249
next_test ./g_gen2 10 10 0
next_test ./g_gen2 11 11 0
next_test ./g_gen2 12 12 0
next_test ./g_gen2 13 13 0
next_test ./g_gen2 10 11 0
next_test ./g_gen2 11 12 0
next_test ./g_gen2 12 13 0
next_test ./g_gen2 13 14 0
next_test ./g_gen2 10 10 1
next_test ./g_gen2 11 11 1
next_test ./g_gen2 12 12 1
next_test ./g_gen2 13 13 1
next_test ./g_gen2 10 11 1
next_test ./g_gen2 11 12 1
next_test ./g_gen2 12 13 1
next_test ./g_gen2 13 14 1
for n in {247..250}; do
  for m in {247..250}; do
    next_test ./g_gen2 "${n}" "${m}" 1
    next_test ./g_gen2 "${n}" "${m}" 0
  done
done
