CC=g++
CXXFLAG=-w
LDFLAG=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
BUILD=_build
TMP=$(BUILD)/tmp
EXEC=../Incidence
LVL=src/game/level

all: $(EXEC)

$(EXEC): main.o Sol.o Element.o TileSet.o Carte.o
	@ cd $(TMP)/ && $(CC) $^ -o $@ $(LDFLAG)

main.o: main.cpp 
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	@ if [ ! -d $(TMP) ]; then mkdir $(TMP); fi
	$(CC) $(CXXFLAG) -o $(TMP)/$@ -c $<

# Level

Sol.o: $(LVL)/Sol.cpp $(LVL)/Sol.hpp
	$(CC) $(CXXFLAG) -o $(TMP)/$@ -c $<

Element.o: $(LVL)/Element.cpp $(LVL)/Element.hpp
	$(CC) $(CXXFLAG) -o $(TMP)/$@ -c $<

TileSet.o: $(LVL)/TileSet.cpp $(LVL)/TileSet.hpp
	$(CC) $(CXXFLAG) -o $(TMP)/$@ -c $<

Carte.o: $(LVL)/Carte.cpp $(LVL)/Carte.hpp
	$(CC) $(CXXFLAG) -o $(TMP)/$@ -c $<

# Nettoyage
clean: 
	rm -rf $(TMP)

mrproper: clean
	rm -rf $(BUILD)

