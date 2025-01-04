#
# Borland makefile
#
# Assumes that the current shell has Visual Studio's environment set up with
# one of the vcvars batch files.
#

CFLAGS = -I../include

all: test_c.exe test_cxx.exe

test_c.exe: test_c.c zztest.c
	$(CC) $(CFLAGS) $?

test_cxx.exe: test_cxx.cpp zztest.cpp
	$(CC) $(CFLAGS) $?

clean:
	del *.obj
	del *.exe
