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


sf::Color colorForTile(const Tile t) {
	switch (t.type()) {
		case ShapeType::TBone:
			return sf::Color::Red;
		case ShapeType::RightHook:
			return sf::Color::Green;
		case ShapeType::LeftStair:
			return sf::Color::Blue;
		case ShapeType::Square:
			return sf::Color::Cyan;
		case ShapeType::RightStair:
			return sf::Color::Yellow;
		case ShapeType::LeftHook:
			return sf::Color::Magenta;
		case ShapeType::Bar:
			return sf::Color::White;
		default:
			break;
	}

	return sf::Color::Black;
}


void View::renderTile(const Tile & tile, float x, float y) {
	window_->Draw(sf::Shape::Rectangle(x, y, x + 24., y + 24., colorForTile(tile)));
}


void View::renderShape(const Shape & shape, float x, float y) {
	for (int row = 0; row < shape.rows(); row++) {
		for (int col = 0; col < shape.cols(); col++) {
			Tile tile = shape.at(col, row);
			if (tile.occupied())
				renderTile(tile, x + (col * 24.f), y + (row * 24.f));
		}
	}
}
