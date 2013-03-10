//
//  Quadrae.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <algorithm>
#include "Quadrae.h"


// util funcs
static bool completed(const Shape::Row & row) {
	return std::all_of(row.begin(), row.end(), [](const Tile & t){ return t.occupied(); });
}


static void clearLine(Shape::Row & line) {
	std::fill(line.begin(), line.end(), 0);
}


// Quadrae class
Quadrae::Quadrae()
	: grid_(10, 20)
{}


void Quadrae::clear() {
	for (auto & line : grid_)
		clearLine(line);
}


void Quadrae::setLine(int lineNr, const Shape::Row & line) {
	grid_.row(lineNr) = line;
}


Shape::Row Quadrae::getLine(int lineNr) const {
	return grid_.row(lineNr);
}


std::vector<int> Quadrae::completedLines() const {
	decltype(completedLines()) lines;
	int lineNr = 0;

	for (const auto & line : grid_) {
		if (completed(line))
			lines.push_back(lineNr);
		lineNr++;
	}
	
	return lines;
}


void Quadrae::collapseCompletedLines() {
	// shift the completed lines beyond the normal ones but preserve order of normal lines
	std::stable_sort(grid_.begin(), grid_.end(), [](const Shape::Row & a, const Shape::Row & b) {
		return completed(a) && !completed(b);
	});
	
	// clear the completed lines
	for (auto & line : grid_)
		if (completed(line))
			clearLine(line);
}


bool Quadrae::canFitShapeAt(const Shape & shape, int col, int row) const {
	for (int y = row; y < row + (int)shape.rows(); y++)
		for (int x = col; x < col + (int)shape.cols(); x++) {
			if (shape.at(x - col, y - row).occupied()) {
				if (x < 0 || x >= (int)grid_.cols() || y >= (int)grid_.rows())
					return false;
				if (y >= 0 && grid_.at(x, y).occupied())
					return false;
			}
		}
	return true;
}


void Quadrae::placeShapeAt(const Shape & shape, int col, int row) {
	for (int y = row; y < row + (int)shape.rows(); y++)
		if (y >= 0 && y < (int)grid_.rows())
			for (int x = col; x < col + (int)shape.cols(); x++) {
				if (x >= 0 && x < (int)grid_.cols() && shape.at(x - col, y - row).occupied())
					grid_.at(x, y) = shape.at(x - col, y - row);
			}
}
