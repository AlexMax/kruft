#
# POSIX makefile
#

CC = cc
CXX = c++
CFLAGS = -Wall -Wextra -I../include
LDFLAGS =

KRUFT_SOURCES = \
	../include/krbit.h \
	../include/krconfig.h \
	../include/krctype.h \
	../include/krint.h \
	../include/krlib.h \
	../include/krlimits.h \
	../include/krrand.h \
	../include/krserial.h \
	../include/krstr.h

KRUFT_TEST_SOURCES = \
	t_bit.inl \
	t_ctype.inl \
	t_int.inl \
	t_lib.inl \
	t_limits.inl \
	t_rand.inl \
	t_serial.inl \
	t_str.inl

DEPS = $(KRUFT_SOURCES) $(KRUFT_TEST_SOURCES)

all: test_c test_cxx

%.c.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.cpp.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

test_c: test_c.c.o zztest.c.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_cxx: test_cxx.cpp.o zztest.cpp.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o
	rm -f test_c test_cxx
