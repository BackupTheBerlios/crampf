GCC=g++
SRC=$(wildcard *.cc)
OBJS=$(SRC:.cc=.o)
LIBS=
PROGNAME=crampf

all:    generate_header $(OBJS)

ifneq ($(MAKECMDGOALS),clean)
include $(OBJS:.o=.d)
endif

ifeq ($(MAKECMDGOALS),dist)
CXXFLAGS+=-DDIST
endif

.PHONY : clean

generate_header:
	@./commands.sh

clean:
	@rm -f $(PROGNAME) $(OBJS) $(OBJS:.o=.d)

%.d:	%.cc
	@$(SHELL) -ec '$(GCC) -MM $(CPPFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@'

