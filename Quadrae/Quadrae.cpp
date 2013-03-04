//
//  Quadrae.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <algorithm>
#include "Quadrae.h"

const unsigned long kEmptyPaddedLine     = 0b1110000000000111;
const unsigned long kCompletedPaddedLine = 0b1111111111111111;


Quadrae::Quadrae(int gridHeight)
	: grid_(gridHeight, kEmptyPaddedLine)
{}


void Quadrae::clear() {
	for (auto & line : grid_)
		line = kEmptyPaddedLine;
}


void Quadrae::setLine(int lineNr, const std::bitset<10> & line) {
	unsigned long paddedLine = kEmptyPaddedLine | (line.to_ulong() << 3);
	grid_.at(height() - lineNr) = paddedLine;
}


Quadrae::Row Quadrae::getLine(int lineNr) const {
	return { grid_.at(height() - lineNr).to_ulong() >> 3 };
}


std::vector<int> Quadrae::completedLines() const {
	decltype(completedLines()) lines;
	int lineNr = 0;

	for (const auto & line : grid_) {
		if (line.to_ulong() == kCompletedPaddedLine)
			lines.push_back(height() - lineNr);
		lineNr++;
	}
	
	return lines;
}


void Quadrae::collapseCompletedLines() {
	auto completed = completedLines();
	using Line = std::bitset<16>;

	// shift the completed lines beyond the normal ones but preserve order of normal lines
	std::stable_sort(grid_.begin(), grid_.end(), [](const Line & a, const Line & b) {
		return (a != kCompletedPaddedLine) && (b == kCompletedPaddedLine);
	});
	
	// clear the completed lines
	for (auto & line : grid_)
		if (line.to_ulong() == kCompletedPaddedLine)
			line = kEmptyPaddedLine;
}


ShapeGrid Quadrae::extractShapeGridAt(int x, int y) const {
	unsigned long bits = 0;
	
	for (auto line = y; line <= y + 4; line++) {
		unsigned long lineBits;

		// provide all 1s above and below grid area
		if (line < 0 || line >= height())
			lineBits = 0b1111;
		else
			lineBits = (grid_[height() - line] >> (16 - 4 - x)).to_ulong();
		
		bits <<= 4;
		bits |= lineBits & 0b1111;
	}

	return bits;
}


bool Quadrae::canFitShapeAt(const ShapeGrid & shape, int x, int y) const {
	// in x-coord is Row-based, offset by left padding
	auto section = extractShapeGridAt(x + 3, y);
	return (shape & section).none();
}


void Quadrae::placeShapeAt(const ShapeGrid & shape, int x, int y) {
	
}
