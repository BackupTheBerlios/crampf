bin_PROGRAMS=crampf

SUBDIRS=commands util cb player

EXTRA_DIST=README COPYING INSTALL COPYRIGHT ChangeLog

noinst_HEADERS=autocmd.hh command.hh commandmap.hh commands.hh	\
    	       config.h config.hh crampf.hh debug.hh file.hh	\
	       interface.hh playlist.hh	readlineinterface.hh	\
	       track.hh

crampf_SOURCES=commandmap.cc config.cc crampf.cc file.cc	\
	       interface.cc playlist.cc readlineinterface.cc	\
	       track.cc

crampf_LDADD=commands/libcmds.a util/libutil.a player/libgenplayer.a player/backends/execplayer/libexecplayer.a

ChangeLog:
	./cvs2cl.pl --prune
