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
{}


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
		nextAction_ = lastAction_ + Time::Duration(1000);
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
	window_->Clear({ 64, 64, 64 });
	
	if (Time::now() > nextAction_)
		nextPhase();
	
	float letterPtc = 1.0f;
	if (phase_ == Phase::LetterDrop) {
		letterPtc = std::min(1.0f, Time::msSince(lastAction_) / 4000.f);
		if (letterPtc == 1.0f)
			nextPhase();
	}

	if (phase_ > Phase::Wait1)
		view_.renderLetters(letterPtc);

	if (phase_ == Phase::BlinkLoop) {
		view_.renderCopyright();

		if (Time::msSince(lastAction_) & 1024)
			view_.renderPressStart();
	}
}
