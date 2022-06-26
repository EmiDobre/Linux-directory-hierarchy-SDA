build: 
	gcc -g -m32 -std=gnu99 -o tema3 main.c arb.c
run:
	./tema3
clean:
	rm -rf tema3