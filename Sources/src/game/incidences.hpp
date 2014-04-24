#ifndef INCIDENCES_HPP
#define INCIDENCES_HPP

#include "game.hpp"
#include "level/tilemap.hpp"
#include "weather.hpp"
#include "entity/entity_type.hpp"
#include "entity/entity.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Entity;
class Game;
class Weather;

#define ALEATOIRE 3

// --- fonction principale ---
void doIncidences(TileMap* tilemap,Weather* weather, sf::Vector2i posHome,std::vector< Entity * > entityList);
// ---------------------------

// --- fonctions "privées" ---
void spreadGround(TileMap* tilemap, int type, sf::Vector2i position);

void dilateGround(TileMap* tilemap, TileBehavior behavior);
void erodeGround(TileMap* tilemap, TileBehavior behavior);

void dilateNearGround(TileMap* tilemap, TileBehavior behavior, TileBehavior behaviorNear);
void erodeNearGround(TileMap* tilemap, TileBehavior behavior, TileBehavior behaviorNear);

void dilateElement(TileMap* tilemap, TileBehavior behavior);
void erodeElement(TileMap* tilemap, TileBehavior behavior);

int spawnEntities(EntityType type, std::vector< Entity * > list);
int killEntities(EntityType type, std::vector< Entity * > list);
// ---------------------------

// --- fonctions à utiliser ---
void dilateFluids(TileMap* tilemap);
void erodeFluids(TileMap* tilemap);

void dilateNearFluids(TileMap* tilemap);
void erodeNearFluids(TileMap* tilemap);

void dilateNearCliffs(TileMap* tilemap);
void erodeNearCliffs(TileMap* tilemap);

void dilateForests(TileMap* tilemap);
void erodeForests(TileMap* tilemap);

void spawnRessources(TileMap* tilemap);
void spawnOnlyStone(TileMap* tilemap);
void burnRessources(TileMap* tilemap);

int allyCitizenBirth(Game* game);
int enemyCitizenBirth(Game* game);
int wildAnimalBirth(Game* game);
int peacefulAnimalBirth(Game* game);

int allyCitizenDeath(Game* game);
int enemyCitizenDeath(Game* game);
int wildAnimalDeath(Game* game);
int peacefulAnimalDeath(Game* game);

void updateRessources(Game* game);
// ----------------------------

#endif
