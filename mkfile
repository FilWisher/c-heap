MKSHELL=$PLAN9/bin/rc

cc=gcc
cflags=-Wall -Wextra -pedantic -std=c99

files=heap
tests=${files:%=%_test}

default:
	for(test in $tests) mk $test
	
test:
	for(test in $tests) $test

%.o: %.c
	$cc $cflags -c $stem.c -o $stem.o
	
%_test: %.o %_test.c
	$cc $cflags $stem^_test.c $stem.o -o $stem^_test

clean:
	rm -rf *.o *_test
