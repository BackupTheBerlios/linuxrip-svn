# linuxrip Makefile

INSTALL = $(PREFIX)/bin/install
PREFIX = /usr

LDLFAGS +=
CXXFLAGS +=

all: compile

compile:
	$(CXX) tagprocess.cpp $(CXXFLAGS) $(LDFLAGS) -o tagprocess

install:
	$(INSTALL) -d "$(DESTDIR)$(PREFIX)/lib/"
	$(INSTALL) -m 755 anser "$(DESTDIR)$(PREFIX)/lib/linuxrip/"
	$(INSTALL) -m 755 createnfo "$(DESTDIR)$(PREFIX)/bin/"
	$(INSTALL) -m 755 detecttracks "$(DESTDIR)$(PREFIX)/lib/linuxrip/"
	$(INSTALL) -m 755 nfowriter "$(DESTDIR)$(PREFIX)/lib/linuxrip/"
	$(INSTALL) -m 755 tagprocess "$(DESTDIR)$(PREFIX)/lib/linuxrip/"
	$(INSTALL) -m 755 xmlwriter "$(DESTDIR)$(PREFIX)/lib/linuxrip/"
	$(INSTALL) -m 755 lowercdspeed "$(DESTDIR)$(PREFIX)/lib/linuxrip/"
	$(INSTALL) -m 755 linuxrip "$(DESTDIR)$(PREFIX)/bin/"
	$(INSTALL) -m 755 rename_album "$(DESTDIR)$(PREFIX)/bin/"
	$(INSTALL) -d "$(DESTDIR)/etc/linuxrip"
	$(INSTALL) -m 644 settings "$(DESTDIR)/etc/linuxrip/"
	$(INSTALL) -d "$(DESTDIR)$(PREFIX)/share/doc/linuxrip"
	$(INSTALL) -m 644 README "$(DESTDIR)$(PREFIX)/share/doc/linuxrip/"
	$(INSTALL) -m 644 gpl.txt "$(DESTDIR)$(PREFIX)/share/doc/linuxrip/"

clean:
	$(RM) tagprocess
