//
//  Scene.cpp
//  Quadrae
//
//  Created by Arthur Langereis
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <unordered_map>
#include "Scene.h"

namespace Scenes {
	static std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_s;
	static std::weak_ptr<Scene> curScene_s;

	void add(const std::string & name, const std::shared_ptr<Scene> & scene) {
		scenes_s.insert({ name, scene });
	}

	std::shared_ptr<Scene> current() noexcept {
		return curScene_s.lock();
	}

	void setCurrent(const std::string & name) {
		if (! curScene_s.expired())
			curScene_s.lock()->suspend();
			
		// will throw on bad key
		curScene_s = scenes_s.at(name);
		curScene_s.lock()->activate();
	}
}
