OBJS=config.o crampf.o playlist.o player.o track.o interface.o command.o commandmap.o readlineinterface.o file.o
CMDOBJS=commands/*.o
UTILOBJS=util/*.o
LIBS=-lreadline 
PROGNAME=crampf

all:    util cmds $(OBJS)
	$(CXX) -o $(PROGNAME) $(OBJS) $(CMDOBJS) $(UTILOBJS) $(LDFLAGS) $(LIBS)

ifneq ($(MAKECMDGOALS),clean)
include $(OBJS:.o=.d)
endif
ifeq ($(MAKECMDGOALS),dist)
CXXFLAGS+=-DDIST -O2
LDFLAGS+=-s 
else
CXXFLAGS+=-g
endif

.PHONY: dist tar clean cmds util

cmds:	
	$(MAKE) -C commands $(MAKECMDGOALS)

util:
	$(MAKE) -C util $(MAKECMDGOALS)

dist:   clean tar all

tar:
	./make_tarball.sh

clean:
	@rm -f $(PROGNAME) $(OBJS) $(OBJS:.o=.d) $(PROGNAME)-*.tar.gz
	$(MAKE) clean -C commands 
	$(MAKE) clean -C util

commands/commands.hh:
	@cd commands && ./commands.sh

%.d:	%.cc
	@$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@' 

