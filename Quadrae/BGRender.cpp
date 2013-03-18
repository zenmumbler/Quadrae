//
//  BGRender.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/16.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <chrono>
#include <cmath>
#include "Common.h"
#include "Assets.h"
#include "BGRender.h"

namespace BGRender {
	static float bgOffX_s = 0.f;
	static float bgOffY_s = 0.f;
	static float bgScale_s = 1.f;

	static void render(sf::RenderTarget & rt, float x, float y, float scale) {
		auto & bg = Assets::bgTexture();
		float scaledWidth = bg.GetWidth() * scale;
		float scaledHeight = bg.GetHeight() * scale;

		x = fmodf(x, scaledWidth);
		if (x > 0.f) x -= scaledWidth;
		y = fmodf(y, scaledHeight);
		if (y > 0.f) y -= scaledHeight;

		int tilesX = ceilf((rt.GetWidth() - x) / scaledWidth);
		int tilesY = ceilf((rt.GetHeight() - y) / scaledHeight);

		sf::Sprite sp { bg, { x, y }, { scale, scale } };

		while (tilesY--) {
			int ttx = tilesX;
			while (ttx--) {
				rt.Draw(sp);
				sp.Move(scaledWidth, 0.f);
			}
			sp.Move(0.f, scaledHeight);
			sp.SetX(x);
		}
	}

	void renderStep(sf::RenderTarget & rt) {
		using namespace std::chrono;

		double t = duration_cast<microseconds>(Time::now().time_since_epoch()).count() / 1000000.;
		const double displace = 400.;

		bgOffX_s = displace * (cos(t / 13.));
		bgOffY_s = displace * (sin((t + 2.) / 17.));
		bgScale_s = 1. + (0.3 * sin( (t / 13.) ));

		render(rt, bgOffX_s, bgOffY_s, bgScale_s);
	}
}
