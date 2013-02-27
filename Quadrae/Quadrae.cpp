//
//  Quadrae.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <algorithm>
#include "Quadrae.h"


Quadrae::Quadrae(int gridHeight)
	: direction_ { Direction::None }
	, height_ { gridHeight }
	, grid_(10 * height_, PieceType::None)
{
}

void Quadrae::setDirection(Direction newDir) {
	direction_ = newDir;
}

void Quadrae::quarterTick() {
	
}

void Quadrae::tick() {
	
}

PieceType Quadrae::piece(int col, int row) const {
	return grid_[(row * 10) + col];
}

void Quadrae::piece(int col, int row, PieceType newPiece) {
	grid_[(row * 10) + col] = newPiece;
}
