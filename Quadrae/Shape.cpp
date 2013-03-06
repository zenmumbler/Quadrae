//
//  Shape.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <memory>
#include "Shape.h"

static ShapeGrid rotateCW(const ShapeGrid & field, int px, int py) {
	ShapeGrid out;
	int dx, dy;
	
	for (int sy = 0; sy < 4; sy++)
		for (int sx = 0; sx < 4; ++sx) {
			// px, py == 0, 0 means rotate around center (1.5, 1.5)
			if (px == 0 && py == 0) {
				dx = 3 - sy;
				dy = sx;
			}
			else {
				dx = 3 - sy - (3 - (px + py));
				dy = sx - (px - py);
			}
			
			if (dx < 0 || dx > 3 || dy < 0 || dy > 3)
				continue;
			
			if (field[(sy * 4) + sx])
				out.set((dy * 4) + dx);
		}
	
	return out;
}


Shape::Shape(unsigned bits4x4, int pivotX, int pivotY, int rotations)
	: pivotX_(pivotX), pivotY_(pivotY), rotations_(rotations)
{
	ShapeGrid mask { bits4x4 };
	for (int r = 0; r < rotations_; r++) {
		masks_.emplace_back(mask);
		mask = rotateCW(mask, pivotX_, pivotY_);
	}
}


const ShapeGrid & Shape::forRotation(int rot) const {
	return masks_[rot % rotations_];
}


// -- global shape set


static constexpr unsigned makeMask(unsigned a, unsigned b, unsigned c, unsigned d) {
	return (a << 12) | (b << 8) | (c << 4) | d;
}


static std::vector<Shape> * createShapes() {
	auto shapes = new std::vector<Shape>;

	// T Bone
	shapes->emplace_back(makeMask(0b0000,
								  0b1110,
								  0b0100,
								  0b0000), 2, 2, 4);
	
	// Right Hook
	shapes->emplace_back(makeMask(0b0000,
								  0b1110,
								  0b0010,
								  0b0000), 2, 2, 4);
	
	// Left Stair
	shapes->emplace_back(makeMask(0b0000,
								  0b1100,
								  0b0110,
								  0b0000), 0, 0, 2);
	
	// Square
	shapes->emplace_back(makeMask(0b0000,
								  0b0110,
								  0b0110,
								  0b0000), 0, 0, 1);
	
	// Right Stair
	shapes->emplace_back(makeMask(0b0000,
								  0b0110,
								  0b1100,
								  0b0000), 0, 0, 2);
	
	// Left Hook
	shapes->emplace_back(makeMask(0b0000,
								  0b1110,
								  0b1000,
								  0b0000), 2, 2, 4);
	
	// Bar
	shapes->emplace_back(makeMask(0b0000,
								  0b0000,
								  0b1111,
								  0b0000), 1, 1, 2);
	
	return shapes;
}


bool testShapeAt(const ShapeGrid & type, int x, int y) {
	return type.test(15 - ((y * 4) + x));
}


ShapeGrid shapeWithRotation(ShapeType type, int rotation) {
	static std::unique_ptr<std::vector<Shape>> allShapes_s;

	if (! allShapes_s)
		allShapes_s.reset(createShapes());
	
	return allShapes_s->at(static_cast<int>(type)).forRotation(rotation);
}
