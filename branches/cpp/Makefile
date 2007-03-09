# linuxrip Makefile

INSTALL = $(PREFIX)/bin/install
PREFIX = /usr

LIBFLAGS = -lcdio_paranoia -lcdio_cdda -lcdio -lcddb -lsndfile
LDLFAGS +=
CXXFLAGS +=

all: compile

compile:
	$(CXX) linuxrip.cpp $(LIBFLAGS) $(CXXFLAGS) $(LDFLAGS) -o linuxrip
clean:
	$(RM) tagprocess
