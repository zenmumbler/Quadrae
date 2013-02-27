//
//  Quadrae.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Quadrae__
#define __Quadrae__Quadrae__

#include <vector>
#include <bitset>

enum class Direction {
	None,
	Left,
	Right,
	Down,
	Drop
};

enum class PieceType : uint8_t {
	None = 0,
	Square = 1,
	Bar = 2,
	LeftStair = 3,
	RightStair = 4,
	LeftL = 5,
	RightL = 6,
	TBlock = 7
};

using PieceShape = std::vector<std::bitset<16>>;



// the model
class Quadrae {
	Direction direction_;
	PieceType curPiece_, nextPiece_;
	int height_;
	std::vector<PieceType> grid_;
	std::vector<PieceShape> shapes_;

public:
	Quadrae(int gridHeight);

	void setDirection(Direction newDir);

	void quarterTick();
	void tick();

	PieceType piece(int col, int row) const;
	void piece(int col, int row, PieceType newPiece);
	
};


#endif /* defined(__Quadrae__Quadrae__) */
