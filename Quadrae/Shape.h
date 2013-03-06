//
//  Shape.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/4.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Shape__
#define __Quadrae__Shape__

#include <vector>
#include <bitset>

enum class ShapeType {
	TBone      = 0,
	RightHook  = 1,
	LeftStair  = 2,
	Square     = 3,
	RightStair = 4,
	LeftHook   = 5,
	Bar        = 6,
	None       = 7
};

using ShapeGrid = std::bitset<16>;


class Shape {
	std::vector<ShapeGrid> masks_;
	int pivotX_, pivotY_;
	int rotations_;
	
public:
	Shape(unsigned bits4x4, int pivotX, int pivotY, int rotations);
	const ShapeGrid & forRotation(int rot) const;
};


bool testShapeAt(const ShapeGrid & type, int x, int y);
ShapeGrid shapeWithRotation(ShapeType type, int rotation);


#endif /* defined(__Quadrae__Shape__) */
