# Example usage: "./test.sh prog"
for i in {1..1000}
do
	./gen > $1.in
	./$1 < $1.in > $1.out
	./brute < $1.in > $1.brute
	diff $1.out $1.brute || break
	echo $i
done
