GCC=g++
SRC=$(wildcard *.cc)
OBJS=$(SRC:.cc=.o)
LIBS=
PROGNAME=

all:    generate_header $(OBJS)
#	$(GCC) $(LIBS) -o $(PROGNAME) $(OBJS)

generate_header:
	./commands.sh

clean:
	@rm -f $(PROGNAME) $(OBJS) $(OBJS:.o=.d)

%.d:	%.cc
	$(SHELL) -ec '$(GCC) -MM $(CPPFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@'

include $(OBJS:.o=.d)

