CC = gcc
CFLAGS = -Wall -pedantic -ansi -g

RM = rm -f

EXEMPLE = ./exemples/
INCLUDE = ./include/
SOURCE = ./src/
OBJECT = ./obj/

MAIN = main
EXECUTABLE = executable.out

OFILES = $(OBJECT)$(MAIN).o \
         $(OBJECT)fenetre.o \
				 $(OBJECT)file.o \
				 $(OBJECT)composant.o \
				 $(OBJECT)point.o


but: $(OBJECT) $(EXECUTABLE)

$(OBJECT):
	mkdir $@

$(EXECUTABLE): $(OFILES)
	$(CC) $(CFLAGS) -o $@ $(OFILES) -lX11

$(OBJECT)main.o: $(EXEMPLE)main.c \
							   $(INCLUDE)couleur.h \
				         $(INCLUDE)fenetre.h \
								 $(INCLUDE)point.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT)fenetre.o: $(SOURCE)fenetre.c \
                    $(INCLUDE)fenetre.h \
										$(INCLUDE)file.h \
										$(INCLUDE)composant.h
	$(CC) $(CFLAGS) -o $@ -c $< -lX11

$(OBJECT)file.o: $(SOURCE)file.c \
	               $(INCLUDE)file.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT)composant.o: $(SOURCE)composant.c \
	                    $(INCLUDE)composant.h \
											$(INCLUDE)couleur.h \
											$(INCLUDE)fenetre.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT)point.o: $(SOURCE)point.c \
	                $(INCLUDE)point.h \
									$(INCLUDE)composant.h
	$(CC) $(CFLAGS) -o $@ -c $< -lX11


run: but
	./$(EXECUTABLE)

clean:
	$(RM) $(OFILES)

.PHONY: but \
	      run \
				clean