#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Cube.h"

class Player
{
public:

	Player();
	~Player();

	void draw(unsigned int shader, const glm::mat4& p, const glm::mat4& v);
};


#endif