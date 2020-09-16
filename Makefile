TARGET = promptus
SRC = promptus.c
CONF = config.h
DEFCONF = config.def.h
PREFIX ?= /usr/local

CFLAGS += -O3 -std=c11 -Wall -W -pedantic
CPPFLAGS += -D_POSIX_C_SOURCE=1

.PHONY: all install uninstall clean

all: $(TARGET)

$(TARGET): $(CONF) $(SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRC) -o $@

$(CONF):
	@cp -v $(DEFCONF) $(CONF)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	$(RM) $(TARGET)
