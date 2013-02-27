//
//  Common.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <random>
#include "Common.h"

static std::mt19937 randEngine;
static std::uniform_real_distribution<float> normalDistribution { 0.0f, 1.0f };

float frandom() {
	return normalDistribution(randEngine);
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
	
	int msSince(Point since) {
		using namespace std::chrono;
		
		auto deltaMs = duration_cast<milliseconds>(detail::now_s - since);
		return static_cast<int>(deltaMs.count());
	}
}
