//
//  TitleView.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <cmath>
#include "Assets.h"
#include "ShapeRender.h"
#include "BGRender.h"
#include "TitleView.h"

TitleView::TitleView(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{}


void TitleView::renderBG() const {
	BGRender::renderStep(*window_);
}


void TitleView::renderLevelBox(float x, float y, int level, bool selected) const {
	const float borderDim = 1.f;
	const float dim = 58.f;

	const sf::Color bgNormal { 0,0,0, 128 };
	const sf::Color bgSelected = sf::Color::Green;
	const sf::Color borderNormal { 32,32,32, 255 };
	const sf::Color borderSelected { 0,128,0, 255 };
	
	auto & bgColor = (selected ? bgSelected : bgNormal);
	auto & borderColor = (selected ? borderSelected : borderNormal);
	
	auto box = sf::Shape::Rectangle(x - borderDim, y - borderDim, x + dim + borderDim, y + dim + borderDim,
									bgColor, borderDim, borderColor);
	window_->Draw(box);

	// draw level number with shadow in the center
	sf::String c { std::to_string(level), Assets::font(), 24.f };
	c.SetColor(sf::Color::Black);
	c.SetCenter(c.GetRect().GetWidth() / 2.f, c.GetRect().GetHeight());
	c.SetPosition(x + 30.f, y + 37.f);
	window_->Draw(c);
	c.SetColor(sf::Color::White);
	c.SetPosition(x + 29.f, y + 36.f);
	window_->Draw(c);
}


void TitleView::renderLevelSelect(int baseLevel, bool highlight) const {
	const float baseX = 50.f;
	const float baseY = 200.f;
	const float boxDim = 60.f;

	for (int i=0; i<10; i++) {
		renderLevelBox(baseX + ((i%5) * boxDim), baseY + ((i/5) * boxDim), i, (i == baseLevel) && highlight);
	}
}


void TitleView::renderLetters(const std::vector<std::vector<uint8_t>> & map, float percentage) const {
	const float linePtcSeg = 1.0f / map.size();
	
	auto ease = [](float ptc) { return ptc * ptc; };

	for (auto row = 0u; row < map.size(); row++) {
		const auto line = map[(int)map.size() - 1 - row];

		const float fromPtc = linePtcSeg * row,
					normPtc = std::min(linePtcSeg, percentage - fromPtc) / linePtcSeg,
					fromY = -12.f,
					toY = 50.f + ((5-row) * 12.f),
					curY = fromY + (ease(normPtc) * (toY - fromY));

		if (percentage < fromPtc)
			continue;

		for (auto col = 0u; col < line.size() - 1; col++) {
			if (line[col])
				renderLogoTile(38.f + (col * 12.f), curY);
		}
	}
}


void TitleView::renderCopyright() const {
	sf::String copy { "Game Code (c) 2013 by Arthur Langereis", Assets::font(), 12.f };
	copy.SetColor(sf::Color::White);
	copy.SetCenter(copy.GetRect().GetWidth() / 2.f, copy.GetRect().GetHeight());
	copy.SetPosition(200.f, 470.f);
	window_->Draw(copy);

	copy.SetText("Game concept, design and look and feel (c) 1985~2013 Tetris Holding");
	copy.SetCenter(copy.GetRect().GetWidth() / 2.f, copy.GetRect().GetHeight());
	copy.SetPosition(200.f, 485.f);
	window_->Draw(copy);

	copy.SetText("This game is a technical experiment and homage and is");
	copy.SetCenter(copy.GetRect().GetWidth() / 2.f, copy.GetRect().GetHeight());
	copy.SetPosition(200.f, 500.f);
	window_->Draw(copy);
	
	copy.SetText("NOT affiliated with or endorsed by Tetris Holding or The Tetris Company");
	copy.SetCenter(copy.GetRect().GetWidth() / 2.f, copy.GetRect().GetHeight());
	copy.SetPosition(200.f, 515.f);
	window_->Draw(copy);
}


void TitleView::renderPressStart() const {
	sf::String act { "Press Return To Start", Assets::font(), 24.f };
	act.SetColor(sf::Color::White);
	act.SetCenter(act.GetRect().GetWidth() / 2.f, act.GetRect().GetHeight());
	act.SetPosition(200.f, 375.f);
	window_->Draw(act);
}


void TitleView::renderLogoTile(float x, float y) const {
	window_->Draw(sf::Shape::Rectangle(x, y, x + 12.f, y + 12.f, sf::Color::Green));
}
