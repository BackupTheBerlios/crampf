GCC=g++
OBJS=config.o crampf.o playlist.o player.o track.o interface.o command.o commandmap.o readlineinterface.o
CMDOBJS=commands/*.o
LIBS=-lreadline -s
PROGNAME=crampf

all:    cmds $(OBJS)
	$(GCC) $(LIBS) -o $(PROGNAME) $(OBJS) $(CMDOBJS)

ifneq ($(MAKECMDGOALS),clean)
include $(OBJS:.o=.d)
endif
ifeq ($(MAKECMDGOALS),dist)
CXXFLAGS+=-DDIST
endif

.PHONY: dist tar clean cmds

cmds:	
	$(MAKE) -C commands

dist:   clean tar all

tar:
	./make_tarball.sh

clean:
	@rm -f $(PROGNAME) $(OBJS) $(OBJS:.o=.d) $(PROGNAME)-*.tar.gz
	$(MAKE) clean -C commands 

commands/commands.hh:
	@cd commands && ./commands.sh

%.d:	%.cc
	@$(SHELL) -ec '$(GCC) -MM $(CPPFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@'

