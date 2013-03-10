//
//  View.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <map>
#include "Assets.h"
#include "View.h"

View::View(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{}

/*
 
 tile size: 24 x 24
 window: 400 x 528  (22 tiles high)
 play grid: 240 x 480 (10x20) @ 24,24 (1,1)
 
 */

void View::renderBG() const {
	window_->Clear();
	
	auto border = sf::Shape::Rectangle(23, 23, 23 + 242, 23 + 482, { 32,32,32 }, 1.f, sf::Color::White);
	window_->Draw(border);
}


static sf::IntRect texRectForTile(const Tile t) {
	static std::map<ShapeType, std::vector<sf::Vector2i>> tileUV_s;
	
	if (tileUV_s.size() == 0) {
		tileUV_s.insert({ ShapeType::None,       { { 0,3 }, { 0,3 }, { 0,3 }, { 0,3 } } });
		tileUV_s.insert({ ShapeType::TBone,      { { 1,4 }, { 2,4 }, { 3,4 }, { 2,5 } } });
		tileUV_s.insert({ ShapeType::RightHook,  { { 0,0 }, { 1,0 }, { 2,0 }, { 2,1 } } });
		tileUV_s.insert({ ShapeType::LeftStair,  { { 3,3 }, { 4,3 }, { 4,4 }, { 5,4 } } });
		tileUV_s.insert({ ShapeType::Square,     { { 0,1 }, { 1,1 }, { 0,2 }, { 1,2 } } });
		tileUV_s.insert({ ShapeType::RightStair, { { 3,1 }, { 4,1 }, { 4,0 }, { 5,0 } } });
		tileUV_s.insert({ ShapeType::LeftHook,   { { 0,4 }, { 0,3 }, { 1,3 }, { 2,3 } } });
		tileUV_s.insert({ ShapeType::Bar,        { { 2,2 }, { 3,2 }, { 4,2 }, { 5,2 } } });
	}
	
	auto txy = tileUV_s[t.type()][t.segment()];

	return { txy.x * 24, txy.y * 24, (txy.x + 1) * 24, (txy.y + 1) * 24 };
}


void View::renderTile(const Tile & tile, float x, float y) const {
	sf::Sprite ts { Assets::tileTexture(), { x + 12.f, y + 12.f } };
	ts.SetSubRect(texRectForTile(tile));
	ts.SetCenter(12.f, 12.f);
	ts.SetRotation(-90.f * tile.rotation());
	window_->Draw(ts);
}


void View::renderShape(const Shape & shape, float x, float y) const {
	for (auto row = 0u; row < shape.rows(); row++) {
		for (auto col = 0u; col < shape.cols(); col++) {
			Tile tile = shape.at(col, row);
			if (tile.occupied())
				renderTile(tile, x + (col * 24.f), y + (row * 24.f));
		}
	}
}


void View::renderLineCounter(int lines) const {
	
}
