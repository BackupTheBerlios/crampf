GCC=g++
OBJS=config.o crampf.o playlist.o player.o
#LIBS=-lpthread
PROGNAME=crampf

all:    $(OBJS)
	$(GCC) $(LIBS) -o $(PROGNAME) $(OBJS)

clean:
	@rm -f $(PROGNAME) $(OBJS)
