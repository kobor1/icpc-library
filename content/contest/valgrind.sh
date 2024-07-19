# Runtime
valgrind --tool=callgrind ./code < t.in
callgrind_annotate callgrind.out.12345
# Memory
valgrind --tool=massif ./code < t.in
ms_print massif.out.12345
ms_print massif.out.12345 | grep code
