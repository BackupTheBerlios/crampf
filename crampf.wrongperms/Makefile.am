bin_PROGRAMS=crampf

SUBDIRS=commands util cb player iosubsys

EXTRA_DIST=README COPYING INSTALL COPYRIGHT ChangeLog crampfrc-example

noinst_HEADERS=autocmd.hh command.hh commandmap.hh commands.hh	\
    	       config.h options.hh crampf.hh debug.hh file.hh	\
	       playlist.hh track.hh module.hh

crampf_SOURCES=commandmap.cc options.cc crampf.cc file.cc	\
	       playlist.cc track.cc

crampf_LDADD=commands/libcmds.a player/libgenplayer.a		\
	     player/backends/execplayer/libexecplayer.a		\
	     iosubsys/libiosubsys.a util/libutil.a

README:
	@echo generating README
	./generate_readme.sh > README

ChangeLog:
	@echo updating ChangeLog
	./cvs2cl.pl --prune

dist-hook:
	@echo updating ChangeLog
	./cvs2cl.pl --prune
	@echo generating README
	./generate_readme.sh > README
