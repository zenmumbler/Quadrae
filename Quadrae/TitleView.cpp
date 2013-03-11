//
//  TitleView.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <cmath>
#include "Assets.h"
#include "TitleView.h"

TitleView::TitleView(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{}


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
