TARGET = promptus
SRC = promptus.cpp
PREFIX ?= /usr/local

CXXFLAGS += -O3 -std=c++20 -Wall -W -pedantic
CPPFLAGS += -D_POSIX_C_SOURCE=1
LDFLAGS += -lfmt

.PHONY: all install uninstall clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRC) -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	$(RM) $(TARGET)
