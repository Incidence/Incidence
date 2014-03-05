#include "TileSet.hpp"

TileSet::TileSet() { 
	//TODO 
}

TileSet::TileSet(sf::Vector2u tilesize) { m_tilesize = tilesize; }

TileSet::~TileSet() {
	//TODO
}

sf::Vector2u TileSet::getTileSize() { return m_tilesize; }

void TileSet::setTileSize(sf::Vector2u tilesize) { m_tilesize = tilesize; }

sf::Texture TileSet::getTile(int type, int colonne) {
	//TODO -> renvoyer un quad et non une texture
}

bool TileSet::loadTilesetSol(const std::string& path) { return m_tileset_sol.loadFromFile(path); }

bool TileSet::loadTilesetObj(const std::string& path) { return m_tileset_obj.loadFromFile(path); }

bool TileSet::loadTilesetEnt(const std::string& path) { return m_tileset_ent.loadFromFile(path); }
