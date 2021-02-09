#include "Tile.h"

#include <iomanip>
#include <sstream>

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

void Tile::SetTileCost(const float _cost) {
	
	this->m_cost = _cost;

	// format string to 1 decimal place
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << m_cost;

	m_costLabel->setText(ss.str());
}

void Tile::AddLabels() {

	auto offset = glm::vec2(Config::TILE_SIZE / 2, Config::TILE_SIZE / 2);

	m_costLabel = new Label("99.9", "Consolas", 12);
	m_costLabel->getTransform()->position = getTransform()->position + offset + glm::vec2(0.0f, -6.0f);
	getParent()->addChild(m_costLabel);
	m_costLabel->setEnabled(false);

	m_statusLabel = new Label("--", "Consolas", 12);
	m_statusLabel->getTransform()->position = getTransform()->position + offset + glm::vec2(0.0f, 6.0f);
	getParent()->addChild(m_statusLabel);
	m_statusLabel->setEnabled(false);
}

void Tile::SetLabelsEnabled(const bool _state) {

	m_costLabel->setEnabled(_state);
	m_statusLabel->setEnabled(_state);
}

glm::vec2 Tile::GetGridPos() {
	return m_gridPos;
}

void Tile::SetGridPos(const float _col, const float _row) {
	m_gridPos = glm::vec2(_col, _row);
}
