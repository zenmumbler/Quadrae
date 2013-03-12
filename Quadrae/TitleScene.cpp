//
//  TitleScene.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "TitleScene.h"


Title::Title(const std::shared_ptr<sf::RenderWindow> & window)
	: Scene(window)
	, view_(window)
	, phase_(Phase::None)
{
	uint8_t _ = 0;

	logo_ = { { 1,2,2,_,_,_,_,_,_,_,_,_,_,_,3,_,_,_,_,_,_,_,_,_,_,_,_,_ },
			  { 1,_,2,_,_,_,_,_,_,_,_,_,_,_,3,_,_,_,_,_,_,_,_,_,_,_,_,_ },
			  { 1,_,2,_,4,_,5,_,6,6,_,_,_,2,2,_,4,_,5,_,7,7,_,_,2,2,2,_ },
			  { 1,_,3,_,4,_,5,_,6,_,7,_,1,_,2,_,4,5,_,_,7,_,6,_,1,1,_,_ },
			  { _,3,3,3,_,5,5,_,_,7,7,_,1,1,1,_,4,_,_,_,_,6,6,_,_,1,1,_ } };
}


void Title::handleEvent(const sf::Event & event) {
	if (event.Type == sf::Event::KeyPressed) {
		if (event.Key.Code == sf::Key::Return || event.Key.Code == sf::Key::Space)
			Scenes::setCurrent("game");
	}
}


void Title::nextPhase() {
	phase_++;
	lastAction_ = Time::now();

	if (phase_ == Phase::Wait1)
		nextAction_ = lastAction_ + Time::Duration(1000);
	else if (phase_ == Phase::Wait2)
		nextAction_ = lastAction_ + Time::Duration(750);
	else
		nextAction_ = Time::Point::max();
}


void Title::activate() {
	phase_ = Phase::None;
	nextPhase();
}


void Title::suspend() {
}


void Title::frame() {
	window_->Clear({ 64, 92, 64 });

	if (Time::now() > nextAction_)
		nextPhase();

	float letterPtc = 1.0f;
	if (phase_ == Phase::LetterDrop) {
		letterPtc = std::min(1.0f, Time::msSince(lastAction_) / 1000.f);
		if (letterPtc == 1.0f)
			nextPhase();
	}

	if (phase_ > Phase::Wait1)
		view_.renderLetters(logo_, letterPtc);

	if (phase_ == Phase::UILoop) {
		view_.renderCopyright();

		if (Time::msSince(lastAction_) & 1024)
			view_.renderPressStart();
	}
}
