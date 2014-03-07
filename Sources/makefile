CC=g++
CXXFLAG=-w
LDFLAG=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
BUILD=_build
TMP=$(BUILD)/tmp
EXEC=$(BUILD)/Incidence
LVL=src/game/level

all: $(EXEC)

$(EXEC): $(TMP)/main.o $(TMP)/Sol.o $(TMP)/Element.o $(TMP)/TileSet.o $(TMP)/Carte.o
	@ $(CC) $^ -o $@ $(LDFLAG)

$(TMP)/main.o: main.cpp 
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	@ if [ ! -d $(TMP) ]; then mkdir $(TMP); fi
	$(CC) $(CXXFLAG) -o $@ -c $<

# Level

$(TMP)/Sol.o: $(LVL)/Sol.cpp $(LVL)/Sol.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/Element.o: $(LVL)/Element.cpp $(LVL)/Element.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/TileSet.o: $(LVL)/TileSet.cpp $(LVL)/TileSet.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/Carte.o: $(LVL)/Carte.cpp $(LVL)/Carte.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

# Nettoyage
clean: 
	rm -rf $(TMP)

mrproper: clean
	rm -rf $(BUILD)

