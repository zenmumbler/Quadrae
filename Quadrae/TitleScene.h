//
//  TitleScene.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/7.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__TitleScene__
#define __Quadrae__TitleScene__

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Shape.h"
#include "Scene.h"
#include "TitleView.h"


class Title : public Scene {
	enum Phase {
		None = 0,
		Wait1,
		LetterDrop,
		Wait2,
		BlinkLoop
	};

	TitleView view_;
	Phase phase_;
	std::vector<std::vector<uint8_t>> logo_;
	Time::Point lastAction_, nextAction_;
	
	
	void nextPhase();

public:
	Title(const std::shared_ptr<sf::RenderWindow> & window);
	
	virtual void handleEvent(const sf::Event & event) override;
	
	virtual void activate() override;
	virtual void suspend() override;
	virtual void frame() override;
};


#endif /* defined(__Quadrae__TitleScene__) */
