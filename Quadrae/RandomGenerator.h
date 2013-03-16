//
//  RandomGenerator.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/16.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__RandomGenerator__
#define __Quadrae__RandomGenerator__

#include <vector>
#include "Common.h"
#include "Shape.h"

class RandomGenerator {
	std::vector<ShapeType> bag_;

	void nextBag();
	
public:
	RandomGenerator();
	ShapeType next();
};

#endif /* defined(__Quadrae__RandomGenerator__) */
