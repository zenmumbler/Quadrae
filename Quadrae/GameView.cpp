//
//  GameView.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <cmath>
#include "Assets.h"
#include "ShapeRender.h"
#include "BGRender.h"
#include "GameView.h"

GameView::GameView(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{}

/*
 
 tile size: 24 x 24
 window: 400 x 528  (22 tiles high)
 play grid: 240 x 480 (10x20) @ 24,24 (1,1)
 
 */

void GameView::renderBox(float x, float y, float w, float h, const std::string & title) const {
	const float borderDim = 2.f;
	auto box = sf::Shape::Rectangle(x - borderDim, y - borderDim, x + w + borderDim, y + h + borderDim,
									{ 32,32,32, 240 }, borderDim, sf::Color::White);
	window_->Draw(box);

	sf::String c { title, Assets::font(), 24.f };
	c.SetColor(sf::Color::Black);
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(x + 29.f, y - 5.f);
	window_->Draw(c);
	c.SetColor(sf::Color::White);
	c.SetPosition(x + 28.f, y - 6.f);
	window_->Draw(c);
}


void GameView::renderBG() const {
	BGRender::renderStep(*window_);

	renderBox(24.f, 24.f, 240.f, 480.f); // playfield

	renderBox(286.f, 56.f, 104.f, 104.f, "NEXT");
	renderBox(286.f, 240.f, 104.f, 94.f, "level");
	renderBox(286.f, 370.f, 104.f, 94.f, "lines");
}


void GameView::renderShape(const Shape & shape, float x, float y) const {
	ShapeRender::render(*window_, shape, x, y);
}


void GameView::renderGridShape(const Shape & shape, int col, int row) const {
	auto x = (col + 1) * 24.f;
	auto y = (row + 1) * 24.f;
	ShapeRender::render(shape, x, y, [=](const sf::Sprite & sp) {
		if (sp.GetPosition().y > 23.f)
			window_->Draw(sp);
	});
}


void GameView::fadeClearedLines(const PlayField & field, float progress) const {
	auto lineNrs = field.completedLines();

	for (int l : lineNrs) {
		auto lineShape = Shape(std::vector<Shape::Row> { field.getLine(l) });
		auto x = (0 + 1) * 24.f;
		auto y = (l + 1) * 24.f;
		int step = std::max(0, 5 - (int)std::floor(progress * 6.f));

		ShapeRender::render(lineShape, x, y, [=](sf::Sprite && sp) {
			// blink, blink, hold, disappear
			if (step == 5 || (step & 1) == 0)
				sp.SetColor({ 42, 85, 107, 255 });
			window_->Draw(sp);
		});
	}
}


void GameView::fadePlayField(float progress) const {
	auto border = sf::Shape::Rectangle(24, 24, 24 + 240, 24 + 480, { 142,131,0, 255 * (1.0f - progress) });
	window_->Draw(border);
}


void GameView::renderCounters(int level, int lines) const {
	sf::String c { std::to_string(lines), Assets::font(), 36.f };
	c.SetColor(sf::Color::White);
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(338.f, 430.f);
	window_->Draw(c);
	
	c.SetText(std::to_string(level));
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(338.f, 300.f);
	window_->Draw(c);
}


void GameView::renderPause() const {
	sf::String c { "Pause", Assets::font(), 24.f };
	c.SetColor({ 128, 128, 128 });
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(6 * 24.f, 250.f);
	window_->Draw(c);
}


void GameView::renderGameOver() const {
	sf::String c { "Game", Assets::font(), 36.f };
	c.SetColor({ 141, 71, 108 });
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(6 * 24.f, 250.f);
	window_->Draw(c);

	c.SetText("Over");
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(6 * 24.f, 300.f);
	window_->Draw(c);
}
