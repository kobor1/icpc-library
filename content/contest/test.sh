# Example usage: "./test.sh kob 100"
for i in $(seq "$2")
do
	./gen > $1.in
	./$1 < $1.in > $1.out
	./brut < $1.in > $1.brut
	diff $1.out $1.brut || break
	echo $i
done
