subdir = . 
top_builddir = .
includedir = include
testdir = test

OBJS = $(SRCS:.c=.o)
LIBS = -I$(top_builddir)/$(includedir) -lm
SRCS = *.c

.PHONY: check clean

$(OBJS): SRCS
	gcc -c $(SRCS) $(LIBS)

check:
ifneq ("$(wildcard $(SRCS:.c=.o))",)
	gcc -c $(SRCS) $(LIBS)
endif
	cd test ; make ; \
	./test_quadratic_equation -t traces/quadratic_equation.trace

clean:
	rm *.o
