# Slow compilation, mainly for debugging purposes
c() {
	g++ -std=gnu++20 -Wall -Wextra -Wshadow \
	-fsanitize=address,undefined -ggdb3 -DLOCAL $1.cpp -o $1
}
# Quick compilation, close to judge's one (w/o -static)
f() {
	g++ -std=gnu++20 -O2 -g $1.cpp -o $1
}
# Hashes a file, ignoring all whitespace and comments
# Use for verifying that code was correctly typed
hasz() {
    cpp -dD -P -fpreprocessed $1.cpp | tr -d '[:space:]' | \
    md5sum | cut -c-6
}
# Runs a tester
tester() {
	for ((i=0;;i++)); do
		./gen > $1.test
		./$1 < $1.test > $1.wzo
		./brut < $1.test > $1.brut
		diff $1.wzo $1.brut || break
		echo "OK $i"
	done
}
