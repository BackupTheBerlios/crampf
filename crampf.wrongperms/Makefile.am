bin_PROGRAMS=crampf

SUBDIRS=commands util cb player

noinst_HEADERS=autocmd.hh command.hh commandmap.hh commands.hh	\
    	       config.h config.hh crampf.hh debug.hh file.hh	\
	       interface.hh playlist.hh	readlineinterface.hh	\
	       track.hh player.hh

crampf_SOURCES=commandmap.cc config.cc crampf.cc file.cc	\
	       interface.cc playlist.cc readlineinterface.cc	\
	       track.cc player.cc

crampf_LDADD=commands/libcmds.a util/libutil.a player/stdplayer/libstdplayer.a

dist-hook:
	@echo updating ChangeLog
	./cvs2cl.pl --prune --no-wrap --seperate-header
