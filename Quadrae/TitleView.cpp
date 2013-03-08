//
//  TitleView.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "TitleView.h"
#include <cmath>

TitleView::TitleView(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{
	font_.LoadFromFile("/Library/Fonts/Arial.ttf");
}


void TitleView::renderLetters(const std::vector<std::vector<uint8_t>> & map, float percentage) const {
	const float linePtcSeg = 1.0f / map.size();
	
	auto ease = [](float ptc) { return ptc * ptc; };

	for (int row = 0; row < map.size(); row++) {
		const auto line = map[(int)map.size() - 1 - row];

		const float fromPtc = linePtcSeg * row,
					normPtc = std::min(linePtcSeg, percentage - fromPtc) / linePtcSeg,
					fromY = -12.f,
					toY = 50.f + ((5-row) * 12.f),
					curY = fromY + (ease(normPtc) * (toY - fromY));

		if (percentage < fromPtc)
			continue;

		for (int col = 0; col < line.size() - 1; col++) {
			if (line[col])
				renderLogoTile(38.f + (col * 12.f), curY);
		}
	}
}


void TitleView::renderCopyright() const {
	sf::String copy { "(c) 2013 by Arthur Langereis", font_, 12.f };
	copy.SetColor(sf::Color::White);
	copy.SetCenter(copy.GetRect().GetWidth() / 2.f, copy.GetRect().GetHeight());
	copy.SetPosition(200.f, 515.f);
	
	window_->Draw(copy);
}


void TitleView::renderPressStart() const {
	sf::String act { "Press Return To Start", font_, 24.f };
	act.SetColor(sf::Color::White);
	act.SetCenter(act.GetRect().GetWidth() / 2.f, act.GetRect().GetHeight());
	act.SetPosition(200.f, 375.f);
	
	window_->Draw(act);
}


void TitleView::renderLogoTile(float x, float y) const {
	window_->Draw(sf::Shape::Rectangle(x, y, x + 12.f, y + 12.f, sf::Color::Green));
}
