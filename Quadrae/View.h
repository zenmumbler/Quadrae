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
#include "Shape.h"

class View {
	std::shared_ptr<sf::RenderWindow> window_;

public:
	View(const std::shared_ptr<sf::RenderWindow> & window);

	void renderBG() const;
	void renderShape(const Shape & shape, float x, float y) const;

	void renderTile(const Tile & tile, float x, float y) const;
	void renderLineCounter(int lines) const;
};

#endif /* defined(__Quadrae__View__) */
