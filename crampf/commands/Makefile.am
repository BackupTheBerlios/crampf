noinst_LIBRARIES=libcmds.a
noinst_HEADERS=addpath.hh autocommand.hh calldef.hh case.hh define.hh	 \
	       exit.hh filename.hh generatetitles.hh help.hh info.hh	 \
	       jump.hh kill.hh listtracks.hh loadnfilter.hh		 \
	       loadpfilter.hh loadplaylist.hh loop.hh map.hh		 \
	       nfilter.hh pfilter.hh playercmd.hh playercmd_args.hh	 \
	       quit.hh randomorder.hh regexp.hh rsearch.hh search.hh	 \
	       set.hh shuffle.hh sort.hh source.hh status.hh		 \
	       titlewidth.hh unify.hh version.hh vol.hh write.hh	 \
	       echo.hh commands.hh genre.dat

libcmds_a_SOURCES=addpath.cc autocommand.cc calldef.cc case.cc		\
		  define.cc exit.cc filename.cc generatetitles.cc	\
		  help.cc info.cc jump.cc kill.cc listtracks.cc		\
		  loadnfilter.cc loadpfilter.cc loadplaylist.cc		\
		  loop.cc map.cc nfilter.cc pfilter.cc playercmd.cc	\
		  playercmd_args.cc quit.cc randomorder.cc regexp.cc	\
		  rsearch.cc search.cc set.cc shuffle.cc sort.cc	\
		  source.cc status.cc titlewidth.cc unify.cc		\
		  version.cc vol.cc write.cc echo.cc

noinst_SCRIPTS=commands.sh
EXTRA_DIST=commands.sh genre.dat
BUILT_SOURCES=commands.hh

commands.hh:	commands.sh
	./commands.sh
