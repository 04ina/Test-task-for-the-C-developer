subdir = test
top_builddir = ..
includedir = /include

PROGRAM = "test_quadratic_equation"

SRCS = *.c
OBJS = $(top_builddir)/quadratic_equation.o

LIBS = -I$(top_builddir)/$(includedir) -lm

.PHONY: all clean

all:
	gcc -o $(PROGRAM) $(OBJS) $(SRCS) $(LIBS) 

clean:
	rm $(PROGRAM)

#clean:
#	rm $(PROGRAM) 

