//
//  GameView.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <map>
#include "Assets.h"
#include "ShapeRender.h"
#include "GameView.h"

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


void View::renderShape(const Shape & shape, float x, float y) const {
	ShapeRender::render(*window_, shape, x, y);
}


void View::renderGridShape(const Shape & shape, int col, int row) const {
	auto x = (col + 1) * 24.f;
	auto y = (row + 1) * 24.f;
	ShapeRender::render(shape, x, y, [=](const sf::Sprite & sp) {
		if (sp.GetPosition().y > 23.f)
			window_->Draw(sp);
	});
}


void View::renderLineCounter(int lines) const {
	sf::String copy { std::to_string(lines), Assets::font(), 36.f };
	copy.SetColor(sf::Color::White);
	copy.SetCenter(copy.GetRect().GetWidth() / 2.f, copy.GetRect().GetHeight());
	copy.SetPosition(344.f, 400.f);
	
	window_->Draw(copy);
}
