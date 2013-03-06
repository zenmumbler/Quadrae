//
//  Common.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef Quadrae_Common_h
#define Quadrae_Common_h

#include <chrono>


namespace Time {
	using Clock = std::chrono::high_resolution_clock;
	using Point = Clock::time_point;
	using Duration = std::chrono::milliseconds;
	
	void step();
	Point now();
	int msSince(Point since);
};


namespace Random {
	void seed();
	float unitFloat();
	int intInRange(int min, int max);
}


#endif
