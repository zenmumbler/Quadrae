//
//  Config.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Config.h"

namespace Config {
	static int baseLevel_s = 0;
	static KeyBinding keys_s;

	
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
		
		baseLevel_s = 19;
	}
}
