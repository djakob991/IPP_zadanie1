all: quantization.o trie.o parser.o
	gcc -Wall -Wextra -std=c11 -O2 -o quantization quantization.o trie.o parser.o

trie.o: trie.c
	gcc -Wall -Wextra -std=c11 -O2 -c trie.c

parser.o: parser.c
	gcc -Wall -Wextra -std=c11 -O2 -c parser.c

quantization.o: quantization.c parser.h trie.h
	gcc -Wall -Wextra -std=c11 -O2 -c quantization.c

clean:
	rm trie.o
	rm parser.o
	rm quantization.o
	rm quantization
