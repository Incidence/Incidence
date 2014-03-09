CC=g++
CXXFLAG=-w
LDFLAG=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
BUILD=_build
TMP=$(BUILD)/tmp
EXEC=$(BUILD)/Incidence

all: $(EXEC)

$(EXEC): $(TMP)/main.o engine state game
	$(CC) $^ -o $@ $(LDFLAG)

$(TMP)/main.o: main.cpp 
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	@ if [ ! -d $(TMP) ]; then mkdir $(TMP); fi
	$(CC) $(CXXFLAG) -o $@ -c $<


# Engine

ENGINE=src/engine

engine: $(TMP)/animation.o $(TMP)/data_manager.o $(TMP)/foo.o $(TMP)/state_manager.o $(TMP)/time.o

$(TMP)/animation.o: $(ENGINE)/animation.cpp $(engine)/animation.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/data_manager.o: $(ENGINE)/data_manager.cpp $(engine)/data_manager.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/foo.o: $(ENGINE)/foo.cpp $(engine)/foo.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/state_manager.o: $(ENGINE)/state_manager.cpp $(engine)/state_manager.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/time.o: $(ENGINE)/time.cpp $(engine)/time.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# State

STATE=src/state

state: $(TMP)/main_state.o $(TMP)/test_state.o

$(TMP)/main_state.o: $(ENGINE)/main_state.cpp $(engine)/main_state.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/test_state.o: $(ENGINE)/test_state.cpp $(engine)/test_state.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# Game

GAME=src/game

game: $(TMP)/game.o level entity

$(TMP)/game.o: $(GAME)/game.cpp $(GAME)/game.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# Level

LVL=$(GAME)/level

level: $(TMP)/Sol.o $(TMP)/Element.o $(TMP)/TileSet.o $(TMP)/Carte.o

$(TMP)/Sol.o: $(LVL)/Sol.cpp $(LVL)/Sol.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/Element.o: $(LVL)/Element.cpp $(LVL)/Element.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/TileSet.o: $(LVL)/TileSet.cpp $(LVL)/TileSet.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/Carte.o: $(LVL)/Carte.cpp $(LVL)/Carte.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# Entity

ENT=$(GAME)/entity

entity: $(TMP)/entity.o $(TMP)/entity_set.o $(TMP)/lumberjack.o

$(TMP)/entity.o: $(ENT)/entity.cpp $(ENT)/entity.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/entity_set.o: $(ENT)/entity_set.cpp $(ENT)/entity_set.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/lumberjack.o: $(ENT)/lumberjack.cpp $(ENT)/lumberjack.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# Nettoyage

clean: 
	rm -rf $(TMP)

mrproper: clean
	rm -rf $(BUILD)

