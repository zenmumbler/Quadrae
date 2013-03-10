//
//  Shape.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <memory>
#include <map>
#include "Shape.h"

Shape::Shape(size_t cols, size_t rows)
	: data_(rows)
{
	for (auto & row : data_)
		row.resize(cols);
}


Tile & Shape::at(size_t col, size_t row) {
	return data_.at(row).at(col);
}


Tile Shape::at(size_t col, size_t row) const {
	return data_.at(row).at(col);
}


Shape Shape::rotateCW(int pivotX, int pivotY) const {
	Shape out { cols(), rows() };
	int dx, dy;
	int w = static_cast<int>(cols()), h = static_cast<int>(rows());
	int xmax = w - 1, ymax = h - 1;
	
	for (int sy = 0; sy < h; sy++)
		for (int sx = 0; sx < w; ++sx) {
			// px, py == 0, 0 means rotate around center
			if (pivotX == 0 && pivotY == 0) {
				dx = ymax - sy;
				dy = sx;
			}
			else {
				dx = ymax - sy - (ymax - (pivotX + pivotY));
				dy = sx - (pivotX - pivotY);
			}
			
			if (dx < 0 || dx > xmax || dy < 0 || dy > ymax)
				continue;
			
			Tile tile = at(sx, sy);
			if (tile.occupied()) {
				tile.setRotation(tile.rotation() + 1);
				out.at(dx, dy) = tile;
			}
		}
	
	return out;
}


// -- global shape set


static std::pair<ShapeType,std::vector<Shape>>
genShapes(ShapeType type, const Shape & segs, int pivotX, int pivotY, int numRotations)
{
	Shape base { segs };
	for (auto & row : base)
		for (Tile & t : row)
			if (t.occupied())
				t.setSegment((uint8_t)t.type() - 1).setType(type);

	std::vector<Shape> shapes { base };

	for (int n = 0; n < numRotations - 1; n++)
		shapes.push_back(shapes.back().rotateCW(pivotX, pivotY));
	
	return std::make_pair(type, shapes);
}


const Shape & shapeWithRotation(ShapeType type, size_t rotation) {
	static std::map<ShapeType, std::vector<Shape>> allShapes_s;

	if (! allShapes_s.size()) {
		Shape shp(1,1);

		// To initialize shapes, we abuse the structure a bit by creating a map
		// of the segment indexes + 1 where the ShapeType would usually be.
		// The genShapes function will transform this into a valid shape
		// with proper tile data.

		shp = { { 0,0,0,0 },
				{ 1,2,3,0 },
				{ 0,4,0,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::TBone, shp, 1, 1, 4));

		shp = { { 0,0,0,0 },
				{ 1,2,3,0 },
				{ 0,0,4,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::RightHook, shp, 1, 1, 4));

		shp = { { 0,0,0,0 },
				{ 1,2,0,0 },
				{ 0,3,4,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::LeftStair, shp, 0, 0, 2));

		shp = { { 0,0,0,0 },
				{ 0,1,2,0 },
				{ 0,3,4,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::Square, shp, 0, 0, 1));

		shp = { { 0,0,0,0 },
				{ 0,3,4,0 },
				{ 1,2,0,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::RightStair, shp, 0, 0, 2));

		shp = { { 0,0,0,0 },
				{ 1,2,3,0 },
				{ 4,0,0,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::LeftHook, shp, 1, 1, 4));

		shp = { { 0,0,0,0 },
				{ 1,2,3,4 },
				{ 0,0,0,0 },
				{ 0,0,0,0 } };
		allShapes_s.insert(genShapes(ShapeType::Bar, shp, 0, 0, 2));
	}
	
	auto & rsv = allShapes_s.at(type);
	return rsv.at(rotation % rsv.size());
}
