//
//  RandomGenerator.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/16.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <algorithm>
#include "RandomGenerator.h"

RandomGenerator::RandomGenerator() {
	bag_.reserve(7);
}


void RandomGenerator::nextBag() {
	using ST = ShapeType;
	decltype(bag_) src = { ST::TBone, ST::RightHook, ST::LeftStair, ST::Square, ST::RightStair, ST::LeftHook, ST::Bar };
	
	while (src.size()) {
		auto it = src.begin() + Random::intInRange(0, (int)src.size() - 1);
		bag_.push_back(*it);
		src.erase(it);
	}
}


ShapeType RandomGenerator::next() {
	if (bag_.empty())
		nextBag();
	auto st = bag_.back();
	bag_.pop_back();
	return st;
}
