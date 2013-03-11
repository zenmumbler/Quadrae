//
//  Config.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Config__
#define __Quadrae__Config__

#include <SFML/Window.hpp>

namespace Config {
	struct KeyBinding {
		sf::Key::Code left, right, drop, rotCW, rotCCW;
	};
	
	KeyBinding keys();
	
	int baseLevel();
	void setBaseLevel(int level);
	
	void load();
};

#endif /* defined(__Quadrae__Config__) */
