//
//  View.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__View__
#define __Quadrae__View__

#include <memory>
#include <SFML/Graphics.hpp>
#include "Common.h"

class View {
	std::shared_ptr<sf::RenderWindow> window_;

public:
	View(const std::shared_ptr<sf::RenderWindow> & window);

	void render();
};

#endif /* defined(__Quadrae__View__) */
