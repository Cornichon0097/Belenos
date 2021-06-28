SRCDIR      = src
INCLUDEDIR  = include
EXAMPLESDIR = examples
BINDIR      = bin

CC     = gcc
CFLAGS = -ansi \
         -pedantic \
         -Wall \
         -Wextra \
         -Wwrite-strings \
         -Wstrict-prototypes \
         -Wunreachable-code \
         -Werror \
         -g \
         -I$(INCLUDEDIR)

LD      = gcc
LDFLAGS = -lX11

CFILES = $(SRCDIR)/color.c \
         $(SRCDIR)/window.c \
         $(SRCDIR)/event.c \
         $(SRCDIR)/component.c \
         $(SRCDIR)/panel.c \
         $(EXAMPLESDIR)/sample.c

OFILES = $(BINDIR)/color.o \
         $(BINDIR)/window.o \
         $(BINDIR)/event.o \
         $(BINDIR)/component.o \
         $(BINDIR)/panel.o \
         $(BINDIR)/sample.o

TARGET = $(BINDIR)/sample.out

DEPENDFILE = .depend


all: $(TARGET)

$(TARGET): $(BINDIR) $(OFILES)
	$(LD) -o $@ $(OFILES) $(LDFLAGS)

$(BINDIR):
	mkdir $@

$(BINDIR)/sample.o: $(EXAMPLESDIR)/sample.c \
                    $(INCLUDEDIR)/belenos/color.h \
                    $(INCLUDEDIR)/belenos/window.h \
                    $(INCLUDEDIR)/belenos/event.h \
                    $(INCLUDEDIR)/belenos/panel.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BINDIR)/color.o: $(SRCDIR)/color.c \
                   $(INCLUDEDIR)/belenos/color.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BINDIR)/window.o: $(SRCDIR)/window.c \
                    $(INCLUDEDIR)/belenos/window.h \
                    $(INCLUDEDIR)/belenos/component.h \
                    $(INCLUDEDIR)/belenos/color.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BINDIR)/event.o: $(SRCDIR)/event.c \
                   $(INCLUDEDIR)/belenos/event.h \
                   $(INCLUDEDIR)/belenos/window.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BINDIR)/component.o: $(SRCDIR)/component.c \
                       $(INCLUDEDIR)/belenos/component.h \
                       $(INCLUDEDIR)/belenos/color.h \
                       $(INCLUDEDIR)/belenos/window.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BINDIR)/panel.o: $(SRCDIR)/panel.c \
                   $(INCLUDEDIR)/belenos/color.h \
                   $(INCLUDEDIR)/belenos/window.h \
                   $(INCLUDEDIR)/belenos/component.h \
                   $(INCLUDEDIR)/belenos/panel.h
	$(CC) $(CFLAGS) -o $@ -c $<


run: all
	./$(TARGET)

depend:
	$(CC) -I$(INCLUDEDIR) -E -MM $(CFILES) > $(DEPENDFILE)

clean:
	rm -f $(OFILES) $(TARGET) $(DEPENDFILE)

mrproper: clean all

.PHONY: all \
        run \
        depend \
        clean \
        mrproper
