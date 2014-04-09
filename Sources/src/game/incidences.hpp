#ifndef INCIDENCES_HPP
#define INCIDENCES_HPP

#include "level/tilemap.hpp"

#include <vector>

void doIncidences();

void erodeFluids(TileMap* tilemap);
void dilateFluids(TileMap* tilemap);
void spreadGround(TileMap* tilemap, int type, sf::Vector2i position);

void expandForests(TileMap* tilemap);
void burnForests(TileMap* tilemap);

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
