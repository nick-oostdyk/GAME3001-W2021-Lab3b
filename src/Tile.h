#pragma once
#ifndef __TILE__
#define __TILE__
#include "DisplayObject.h"
#include "NeighbourTile.h"
#include "Label.h"

class Tile : public DisplayObject {

	private:
	Label *m_costLabel, 
		*m_statusLabel;

	Tile *m_neighbors[NUM_NEIGHBOURS];

	float m_cost;

	public:
	// Constructor
	Tile();

	// Destructor
	~Tile();

	// Life-Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;

	// funcs
	Tile *GetNeighbourTile(NeighbourTile position) const;
	void SetNeighbourTile(NeighbourTile position, Tile* _tile);

	float GetTileCost() const;
	void SetTileCost(float _cost);

	void AddLabels();
	void SetLabelsEnabled(bool _state);
};

#endif /* defined (__TILE__) */