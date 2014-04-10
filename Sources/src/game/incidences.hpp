#ifndef INCIDENCES_HPP
#define INCIDENCES_HPP

#include "level/tilemap.hpp"
#include <vector>

#define ALEATOIRE 3

void doIncidences();

void spreadGround(TileMap* tilemap, int type, sf::Vector2i position);
void dilateGround(TileMap* tilemap, TileBehavior behavior);
void erodeGround(TileMap* tilemap, TileBehavior behavior);
void dilateElement(TileMap* tilemap, TileBehavior behavior);
void erodeElement(TileMap* tilemap, TileBehavior behavior);

void dilateFluids(TileMap* tilemap);
void erodeFluids(TileMap* tilemap);
void dilateCliffs(TileMap* tilemap);
void erodeCliffs(TileMap* tilemap);

void mixGround(TileMap* tilemap);

void dilateForests(TileMap* tilemap);
void erodeForests(TileMap* tilemap);

void spawnRessources(TileMap* tilemap);
void burnRessources(TileMap* tilemap);

void spawnEntities(TileMap* tilemap);
void killEntities(TileMap* tilemap);

void citizenFeeding(TileMap* tilemap);
void citizenSicken(TileMap* tilemap);
void citizenBirth(TileMap* tilemap);
void citizenJobUpdate(TileMap* tilemap);

void bonusPI(TileMap* tilemap);

#endif
