//
//  Scene.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/7.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Scene__
#define __Quadrae__Scene__

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

// Scene, a controller class interface

class Scene {
protected:
	std::shared_ptr<sf::RenderWindow> window_;

public:
	Scene(const std::shared_ptr<sf::RenderWindow> & window) : window_(window) {}
	virtual ~Scene() = default;

	virtual void handleEvent(const sf::Event & event) = 0;

	virtual void activate() {}
	virtual void suspend() {}
	virtual void frame() = 0;
};


// Scene Management

namespace Scenes {
	void add(const std::string & name, const std::shared_ptr<Scene> & scene);
	std::shared_ptr<Scene> current() noexcept;
	void setCurrent(const std::string & name);
}


#endif /* defined(__Quadrae__Scene__) */
