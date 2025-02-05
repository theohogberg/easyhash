default: compile_apple
	./easyhash

compile_apple:
	gcc -O3  easyhash.c -o easyhash
