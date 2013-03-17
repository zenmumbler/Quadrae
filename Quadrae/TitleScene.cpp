//
//  TitleScene.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Config.h"
#include "Assets.h"
#include "TitleScene.h"


TitleScene::TitleScene(const std::shared_ptr<sf::RenderWindow> & window)
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


void TitleScene::trySetBaseLevel(int newLevel) const {
	Config::setBaseLevel(std::min(9, std::max(0, newLevel)));
	Assets::playMove();
}


void TitleScene::handleEvent(const sf::Event & event) {
	if (event.Type == sf::Event::KeyPressed) {
		if (phase_ == Phase::UILoop) {
			if (event.Key.Code == sf::Key::Left)
				trySetBaseLevel(Config::baseLevel() - 1);
			else if (event.Key.Code == sf::Key::Right)
				trySetBaseLevel(Config::baseLevel() + 1);
			else if (event.Key.Code == sf::Key::Up)
				trySetBaseLevel(Config::baseLevel() - 5);
			else if (event.Key.Code == sf::Key::Down)
				trySetBaseLevel(Config::baseLevel() + 5);
		}
			
		if (event.Key.Code == sf::Key::Return || event.Key.Code == sf::Key::Space) {
			if (phase_ != Phase::UILoop) {
				// force phase change to final one
				phase_ = Phase::Wait2;
				nextPhase();
			} else
				Scenes::setCurrent("game");
		}
	}
}


void TitleScene::nextPhase() {
	phase_++;
	lastAction_ = Time::now();

	if (phase_ == Phase::Wait1)
		nextAction_ = lastAction_ + Time::Duration(1000);
	else if (phase_ == Phase::Wait2)
		nextAction_ = lastAction_ + Time::Duration(750);
	else
		nextAction_ = Time::Point::max();
}


void TitleScene::activate() {
	phase_ = Phase::None;
	nextPhase();
}


void TitleScene::suspend() {
}


void TitleScene::frame() {
	view_.renderBG();

	if (Time::now() > nextAction_)
		nextPhase();

	auto ms = Time::msSince(lastAction_);

	float letterPtc = 1.0f;
	if (phase_ == Phase::LetterDrop) {
		letterPtc = std::min(1.0f, ms / 1000.f);
		if (letterPtc == 1.0f)
			nextPhase();
	}

	if (phase_ > Phase::Wait1)
		view_.renderLetters(logo_, letterPtc);

	if (phase_ == Phase::UILoop) {
		view_.renderCopyright();

		if (ms & 1024)
			view_.renderPressStart();
		
		view_.renderLevelSelect(Config::baseLevel(), true);
	}
}
