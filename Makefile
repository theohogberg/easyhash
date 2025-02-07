default: compile_apple
	./easyhash

# makeout
out:
	./easyhash > output-for-test.txt

compile_apple:
	gcc -O3  easyhash.c -o easyhash
