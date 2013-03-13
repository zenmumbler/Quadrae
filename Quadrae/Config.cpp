//
//  Config.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <cmath>
#include "Common.h"
#include "Config.h"

namespace Config {
	static int baseLevel_s = 0;
	static KeyBinding keys_s;
	static float bgOffX_s = 0.f;
	static float bgOffY_s = 0.f;
	static float bgScale_s = 1.f;
	
	KeyBinding keys() { return keys_s; }
	
	int baseLevel() { return baseLevel_s; }
	
	void setBaseLevel(int level) {
		baseLevel_s = level;
	}
	
	void load() {
		keys_s.left = sf::Key::Left;
		keys_s.right = sf::Key::Right;
		keys_s.drop = sf::Key::Down;
		
		keys_s.rotCW = sf::Key::Z;
		keys_s.rotCCW = sf::Key::A;
		
		baseLevel_s = 8;
	}
	
	
	void stepBGAnim() {
		using namespace std::chrono;
		using std::sinf; using std::cosf;
		
		float t = duration_cast<microseconds>(Time::now().time_since_epoch()).count() / 1000000.f;
		const float displace = 400.f;
		
		bgOffX_s = displace * (cosf(t / 15.f));
		bgOffY_s = displace * (sinf((t + 2.f) / 18.f));
		bgScale_s = 1.f + (0.3f * sinf( (t / 14.f) ));
	}
	
	float bgOffX() { return bgOffX_s; }
	float bgOffY() { return bgOffY_s; }
	float bgScale() { return bgScale_s; }

}
