//
//  TitleView.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "TitleView.h"


TitleView::TitleView(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
{
	font_.LoadFromFile("/Library/Fonts/Arial.ttf");
}


void TitleView::renderLetters(float percentage) const {
	sf::String product { "Quadrae", font_, 60.f };
	product.SetColor(sf::Color::White);
	product.SetCenter(product.GetRect().GetWidth() / 2, product.GetRect().GetHeight());
	product.SetPosition(200., 70.);
	
	window_->Draw(product);
}


void TitleView::renderCopyright() const {
	sf::String copy { "(c) 2013 by Arthur Langereis", font_, 12.f };
	copy.SetColor(sf::Color::White);
	copy.SetCenter(copy.GetRect().GetWidth() / 2, copy.GetRect().GetHeight());
	copy.SetPosition(200., 515.);
	
	window_->Draw(copy);
}


void TitleView::renderPressStart() const {
	sf::String act { "Press Return To Start", font_, 24.f };
	act.SetColor(sf::Color::White);
	act.SetCenter(act.GetRect().GetWidth() / 2, act.GetRect().GetHeight());
	act.SetPosition(200., 375.);
	
	window_->Draw(act);
}
