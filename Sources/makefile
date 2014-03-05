CC=g++
CXXFLAG=-w
LDFLAG=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
BUILDFOLDER=_build
TMPFOLDER=$(BUILDFOLDER)/tmp
EXEC=../Incidence

all: $(EXEC)

$(EXEC): main.o TileSet.o Case.o Carte.o
	@ cd $(TMPFOLDER)/ && $(CC) $^ -o $@ $(LDFLAG)

main.o: main.cpp TileSet.o Case.o Carte.o
	@ if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
	@ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
	$(CC) $(CXXFLAG) -o $(TMPFOLDER)/$@ -c $<

TileSet.o: src/TileSet.cpp src/TileSet.hpp
	$(CC) $(CXXFLAG) -o $(TMPFOLDER)/$@ -c $<

Case.o: src/Case.cpp src/Case.hpp
	$(CC) $(CXXFLAG) -o $(TMPFOLDER)/$@ -c $<

Carte.o: src/Carte.cpp src/Carte.hpp
	$(CC) $(CXXFLAG) -o $(TMPFOLDER)/$@ -c $<

clean: 
	rm -rf $(TMPFOLDER)

mrproper: clean
	rm -rf $(BUILDFOLDER)

