CFLAGS = -std=c17 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond\
         -Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init\
         -Wlogical-not-parentheses -Wnull-dereference -Wvla -Werror\
         -fstack-protector-strong -fsanitize=undefined -fno-sanitize-recover\
         -g -fno-omit-frame-pointer -O1


suma_test: ./tests/suma_test.c zbior_ary.c
	gcc @opcje ./tests/suma_test.c zbior_ary.c -o suma_test.e
	./suma_test.e
	
clean:
	rm -f *.e
