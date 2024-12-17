# NMAKE makefile

CFLAGS = /nologo /W4 /I"../include"
LDFLAGS = /nologo

all: test_c.exe test_cxx.exe

test_c.exe: test_c.c
	$(CC) $(CFLAGS) $?

test_cxx.exe: test_cxx.cpp
	$(CC) $(CFLAGS) $?

clean:
	del *.obj
	del *.exe
