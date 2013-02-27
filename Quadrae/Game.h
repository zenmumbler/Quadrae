//
//  Game.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Game__
#define __Quadrae__Game__

#include <SFML/Graphics.hpp>
#include "Common.h"
#include "View.h"

class Game {
	Time::Point lastStep_;
	std::shared_ptr<sf::RenderWindow> window_;
	std::unique_ptr<View> view_;

public:
	Game(const std::shared_ptr<sf::RenderWindow> & window);
	
	void handleEvent(const sf::Event & event);
	void step();
};


#endif /* defined(__Quadrae__Game__) */
