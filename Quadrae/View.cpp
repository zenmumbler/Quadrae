//
//  View.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "View.h"

View::View(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{}

/*
 
 tile size: 24 x 24
 window: 400 x 528  (22 tiles high)
 play grid: 240 x 480 (10x20) @ 24,24 (1,1)
 
 */

void View::renderBG() {
	window_->Clear();
	
	auto border = sf::Shape::Rectangle(23, 23, 23 + 242, 23 + 482, { 32,32,32 }, 1.f, sf::Color::White);
	window_->Draw(border);
}


void View::renderShape(const ShapeGrid & shape, float x, float y) {
	auto tile = sf::Shape::Rectangle(x, y, x + 24., y + 24., sf::Color::Green);
	
	for (int b = 15; b > -1; b--) {
		if (shape.test(b))
			window_->Draw(tile);
		
		if ((b & 3) == 0)
			tile.Move(-72., 24.);
		else
			tile.Move(24., 0.);
	}
}
