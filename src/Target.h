#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"

class Target final : public DisplayObject {

private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	glm::vec2 m_gridPos;

	public:
	Target();
	~Target();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// set/get
	glm::vec2 GetGridPos();
	void SetGridPos(const float, const float);


};

#endif /* defined (__TARGET__) */