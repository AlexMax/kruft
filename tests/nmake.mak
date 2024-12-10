# NMAKE makefile

OBJS = zztest.obj t_ctype.obj t_lib.obj t_str.obj
CFLAGS = /nologo /W4 /I"../include"
LDFLAGS = /nologo

test_c.exe: $(OBJS) test_c.obj
	$(CC) $(CFLAGS) $? /Fe:$@

test_c.obj: test_c.c
	$(CC) $(CFLAGS) /c $? /Fo:"$@"

zztest.obj: zztest.c
	$(CC) $(CFLAGS) /c $? /Fo:"$@"

t_ctype.obj: t_ctype.c
	$(CC) $(CFLAGS) /c $? /Fo:"$@"

t_lib.obj: t_lib.c
	$(CC) $(CFLAGS) /c $? /Fo:"$@"

t_str.obj: t_str.c
	$(CC) $(CFLAGS) /c $? /Fo:"$@"

clean:
	del test_c.exe
	del *.obj
