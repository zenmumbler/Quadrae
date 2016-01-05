//
//  PlayField.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef Quadrae_PlayField_H
#define Quadrae_PlayField_H

#include <vector>
#include "Shape.h"


class PlayField {
	Shape grid_;

public:
	PlayField();
	
	void clear();
	void setLine(int lineNr, const Shape::Row & line);
	Shape::Row getLine(int lineNr) const;
	const Shape & shape() const { return grid_; }

	std::vector<int> completedLines() const;
	void collapseCompletedLines();
	
	bool canFitShapeAt(const Shape & shape, int col, int row) const;
	void placeShapeAt(const Shape & shape, int col, int row);
};


#endif /* defined(__Quadrae__PlayField__) */
