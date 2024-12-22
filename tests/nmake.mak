# NMAKE makefile

CFLAGS = /nologo /W4 /I"../include"
LDFLAGS = /nologo

all: test_c.exe test_cxx.exe

test_c.exe: test_c.c zztest.c
	$(CC) $(CFLAGS) $?

test_cxx.exe: test_cxx.cpp zztest.cpp
	$(CC) $(CFLAGS) $?

clean:
	del *.obj
	del *.exe
