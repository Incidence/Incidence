CC=g++
FLAG=-lsfml-graphics -lsfml-window -lsfml-system
BUILDFOLDER=_build
TMPFOLDER=tmp


all: Incidence

Incidence: main.o
	if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
	$(CC) $(FLAG) $(BUILDFOLDER)/$(TMPFOLDER)/main.o -o Incidence

main.o: main.cpp
	if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
	if [ ! -d $(BUILDFOLDER)/$(TMPFOLDER) ]; then mkdir $(BUILDFOLDER)/$(TMPFOLDER); fi
	$(CC) -o $(BUILDFOLDER)/$(TMPFOLDER)/main.o -c main.cpp

clean: 
	rm -rf $(BUILDFOLDER)

