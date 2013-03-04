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
#include "Shape.h"


class Quadrae {
	std::vector<std::bitset<16>> grid_;
	
	ShapeGrid extractShapeGridAt(int x, int y) const;

public:
	Quadrae(int gridHeight);
	
	using Row = std::bitset<10>;
	
	int height() const noexcept { return static_cast<int>(grid_.size()); }
	
	void clear();
	void setLine(int lineNr, const Row & line);
	Row getLine(int lineNr) const;

	std::vector<int> completedLines() const;
	void collapseCompletedLines();
	
	bool canFitShapeAt(const ShapeGrid & shape, int x, int y) const;
	void placeShapeAt(const ShapeGrid & shape, int x, int y);
};


#endif /* defined(__Quadrae__Quadrae__) */
