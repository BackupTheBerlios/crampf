GCC=g++
OBJS=config.o crampf.o playlist.o player.o track.o interface.o command.o commandmap.o readlineinterface.o
CMDOBJS=commands/*.o
LIBS=-lreadline -s
PROGNAME=crampf

all:    cmds $(OBJS)
	$(GCC) $(LIBS) -o $(PROGNAME) $(OBJS) $(CMDOBJS)

cmds:	
	$(MAKE) -C commands

clean:
	@rm -f $(PROGNAME) $(OBJS) $(OBJS:.o=.d)
	$(MAKE) clean -C commands 

commands/commands.hh:
	@cd commands && ./commands.sh

%.d:	%.cc
	$(SHELL) -ec '$(GCC) -MM $(CPPFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@'

include $(OBJS:.o=.d)
