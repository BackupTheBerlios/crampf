SRC=$(wildcard *.cc)
OBJS=$(SRC:.cc=.o)
PROGNAME=crampf

all:    generate_header $(OBJS)

ifneq ($(MAKECMDGOALS),clean)
include $(OBJS:.o=.d)
endif
ifeq ($(MAKECMDGOALS),dist)
CXXFLAGS+=-DDIST -O2
LDFLAGS=-s 
else
CXXFLAGS+=-g
endif

.PHONY : clean dist static

dist:	clean all

generate_header:
	@./commands.sh

clean:
	@rm -f $(PROGNAME) $(OBJS) $(OBJS:.o=.d)

%.d:	%.cc
	@$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@'

