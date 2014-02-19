CC=g++
CXXFLAG=-w
LDFLAG=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
BUILDFOLDER=_build
TMPFOLDER=$(BUILDFOLDER)/tmp
EXEC=$(BUILDFOLDER)/Incidence


all: $(EXEC)

$(EXEC): main.o
	@ $(CC) $(TMPFOLDER)/$< -o $@ $(LDFLAG)

main.o: main.cpp
	@ if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
	@ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
	$(CC) $(CXXFLAG) -o $(TMPFOLDER)/$@ -c $<

clean: 
	rm -rf $(TMPFOLDER)

mrproper: clean
	rm -rf $(BUILDFOLDER)

