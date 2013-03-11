//
//  ShapeRender.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__ShapeRender__
#define __Quadrae__ShapeRender__

#include <functional>
#include <SFML/Graphics.hpp>
#include "Shape.h"

namespace ShapeRender {
	sf::IntRect texRectForTile(const Tile t);
	sf::Sprite genTileSprite(const Tile & tile, float x, float y);
	void render(const Shape & shape, float x, float y, const std::function<void(sf::Sprite)> act);
	void render(sf::RenderTarget & rt, const Shape & shape, float x, float y);
}

#endif /* defined(__Quadrae__ShapeRender__) */
