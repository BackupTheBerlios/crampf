bin_PROGRAMS=crampf

SUBDIRS=commands util cb

noinst_HEADERS=autocmd.hh command.hh commandmap.hh commands.hh	\
    	       config.h config.hh crampf.hh debug.hh file.hh	\
	       interface.hh player.hh playlist.hh		\
	       readlineinterface.hh track.hh

crampf_SOURCES=commandmap.cc config.cc crampf.cc file.cc	\
	       interface.cc player.cc playlist.cc		\
	       readlineinterface.cc track.cc

crampf_LDADD=commands/libcmds.a util/libutil.a

dist-hook:
	@echo updating ChangeLog
	./cvs2cl.pl
