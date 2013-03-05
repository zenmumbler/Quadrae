//
//  Common.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <random>
#include <chrono>
#include "Common.h"

namespace Random {
	static std::mt19937 randEngine;
	static std::uniform_real_distribution<float> unitDist { 0.0f, 1.0f };

	void seed() {
		auto x = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		randEngine.seed(static_cast<unsigned>(x));
	}

	float unitFloat() {
		return unitDist(randEngine);
	}
	
	int rangedInt(int min, int max) {
		std::uniform_int_distribution<int> dist { min, max };
		return dist(randEngine);
	}
	
}


namespace Time {
	namespace detail {
		static Point now_s = Clock::now();
	}
	
	void step() {
		detail::now_s = Clock::now();
	}

	Point now() {
		return detail::now_s;
	}

	int msDistance(Point from, Point to) {
		using namespace std::chrono;
		
		auto deltaMs = duration_cast<milliseconds>(to - from);
		return static_cast<int>(deltaMs.count());
	}
	
	int msSince(Point since) {
		return msDistance(since, detail::now_s);
	}
}
