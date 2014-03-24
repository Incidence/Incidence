CC=g++
CXXFLAG=-w
LDFLAG=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -llua -ldl
BUILD=_build
TMP=$(BUILD)/tmp
EXEC=$(BUILD)/Incidence

all: $(EXEC)

$(EXEC): $(TMP)/main.o engine state game
	@ $(CC) $(TMP)/*.o -o $@ $(LDFLAG)
	@echo Done.

$(TMP)/main.o: main.cpp
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	@ if [ ! -d $(TMP) ]; then mkdir $(TMP); fi
	$(CC) $(CXXFLAG) -o $@ -c $<


# Engine

ENGINE=src/engine

engine: $(TMP)/animation.o $(TMP)/data_manager.o $(TMP)/foo.o $(TMP)/state_manager.o $(TMP)/time.o

$(TMP)/animation.o: $(ENGINE)/animation.cpp $(ENGINE)/animation.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/data_manager.o: $(ENGINE)/data_manager.cpp $(ENGINE)/data_manager.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/foo.o: $(ENGINE)/foo.cpp $(ENGINE)/foo.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/state_manager.o: $(ENGINE)/state_manager.cpp $(ENGINE)/state_manager.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/time.o: $(ENGINE)/time.cpp $(ENGINE)/time.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# State

STATE=src/state

state: $(TMP)/main_state.o $(TMP)/test_state.o

$(TMP)/main_state.o: $(STATE)/main_state.cpp $(STATE)/main_state.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/test_state.o: $(STATE)/test_state.cpp $(STATE)/test_state.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# Game

GAME=src/game

game: $(TMP)/game.o $(TMP)/incidences.o level entity

$(TMP)/game.o: $(GAME)/game.cpp $(GAME)/game.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/incidences.o: $(GAME)/incidences.cpp $(GAME)/incidences.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<


# Level

LVL=$(GAME)/level

level: $(TMP)/ground.o $(TMP)/element.o $(TMP)/tileset.o $(TMP)/tilemap.o $(TMP)/pathfinding.o

$(TMP)/ground.o: $(LVL)/ground.cpp $(LVL)/ground.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/element.o: $(LVL)/element.cpp $(LVL)/element.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/tileset.o: $(LVL)/tileset.cpp $(LVL)/tileset.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/tilemap.o: $(LVL)/tilemap.cpp $(LVL)/tilemap.hpp
	$(CC) $(CXXFLAG) -o $@ -c $<

$(TMP)/pathfinding.o: $(LVL)/pathfinding.cpp $(LVL)/pathfinding.hpp
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

