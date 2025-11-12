CFLAGS = -std=c17 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond\
         -Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init\
         -Wlogical-not-parentheses -Wnull-dereference -Wvla -Werror\
         -fstack-protector-strong -fsanitize=undefined -fno-sanitize-recover\
         -g -fno-omit-frame-pointer -O1


suma: ./tests/suma_test.c zbior_ary.c ./../tests/print.cpp
	g++ ./tests/suma_test.c zbior_ary.c ./../tests/print.cpp -o suma_test.e
	./suma_test.e

ocen: zbior_ary.c ocen.c 
	g++ ocen.c zbior_ary.c -o ocen.e
	./ocen.e

nalezy: ./tests/nalezy_test.c zbior_ary.c
	gcc ./tests/nalezy_test.c zbior_ary.c -o nalezy_test.e
	./nalezy_test.e

ilo: ./tests/iloczyn_test.c zbior_ary.c
	gcc ./tests/iloczyn_test.c zbior_ary.c -o iloczyn_test.e
	./iloczyn_test.e
	
inter: ./tests/inter_test.c zbior_ary.c
	gcc ./tests/inter_test.c zbior_ary.c -o inter_test.e
	./inter_test.e

clean:
	rm -f *.e
