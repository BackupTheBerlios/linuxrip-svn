# linuxrip Makefile

INSTALL = $(PREFIX)/bin/install
PREFIX = /usr

LIBFLAGS = -lcdio_paranoia -lcdio_cdda -lcdio -lcddb -lsndfile
LDLFAGS +=
CXXFLAGS +=

LINUXRIP_O = cddb.o linuxrip.o
LINUXRIP_H = cddb.h linuxrip.h

all: compile

compile: $(LINUXRIP_O)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o linuxrip $(LINUXRIP_O) $(LIBFLAGS)

LINUXRIP_O: $(LINUXRIP_H)

clean:
	$(RM) linuxrip
	$(RM) *.o
