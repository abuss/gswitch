CC = g++-4.8
CFLAGS += -std=c++11 -I..

test: test.cc
	${CC} ${CFLAGS} -w test.cc -o test 

test_gswitch: ../gswitch.hpp ../pattern.hpp test_gswitch.cc
	${CC} ${CFLAGS} test_gswitch.cc -o test_gswitch -g -O0

clean:
	rm -f test_gswitch test
	rm -f *~
