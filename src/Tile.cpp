#include "Tile.h"

#include "Config.h"
#include "TextureManager.h"
#include "Util.h"

Tile::Tile() : m_cost(0.0f) {
	setWidth(Config::TILE_SIZE);
	setHeight(Config::TILE_SIZE);
}

Tile::~Tile()
= default;

void Tile::draw() {
	Util::DrawRect(getTransform()->position, getWidth(), getHeight());
}

void Tile::update() { }

void Tile::clean() { }

Tile *Tile::GetNeighbourTile(const NeighbourTile position) const {
	return m_neighbors[position];
}

void Tile::SetNeighbourTile(const NeighbourTile position, Tile * _tile) {
	m_neighbors[position] = _tile;
}

float Tile::GetTileCost() const { 
	return m_cost;
}

void Tile::SetTileCost(float _cost) {
	this->m_cost = _cost;
	// TODO: Display cost in label
}