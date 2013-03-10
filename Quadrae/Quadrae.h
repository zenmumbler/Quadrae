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
	Shape grid_;

public:
	Quadrae();
	
	void clear();
	void setLine(int lineNr, const Shape::Row & line);
	Shape::Row getLine(int lineNr) const;
	const Shape & shape() const { return grid_; }

	std::vector<int> completedLines() const;
	void collapseCompletedLines();
	
	bool canFitShapeAt(const Shape & shape, int col, int row) const;
	void placeShapeAt(const Shape & shape, int col, int row);
};


#endif /* defined(__Quadrae__Quadrae__) */
