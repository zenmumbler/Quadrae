//
//  Assets.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Assets.h"

namespace Assets {

	static sf::Image tilesTex_s, bgTex_s;
	static sf::SoundBuffer moveBuf_s, lockBuf_s, clearBuf_s, clear4Buf_s;
	static sf::Sound moveSnd_s, lockSnd_s, clearSnd_s, clear4Snd_s;
	static sf::Font font_s;

	const sf::Image & tileTexture() { return tilesTex_s; }
	const sf::Image & bgTexture() { return bgTex_s; }

	const sf::Font & font() { return font_s; }

	void playMove() { moveSnd_s.Play(); }
	void playLock() { lockSnd_s.Play(); }
	void playClear() { clearSnd_s.Play(); }
	void playClear4() { clear4Snd_s.Play(); }

	bool loadAll() {
		bool ok = true;

#if __APPLE__
		if (ok) ok = font_s.LoadFromFile("/Library/Fonts/Arial.ttf");
#else
		if (ok) ok = font_s.LoadFromFile("data/arial.ttf");
#endif
		if (ok)	ok = tilesTex_s.LoadFromFile("data/texture.png");
		if (ok)	ok = bgTex_s.LoadFromFile("data/bg.png");

		if (ok)	ok = moveBuf_s.LoadFromFile("data/move.wav");
		if (ok)	ok = lockBuf_s.LoadFromFile("data/lock.wav");
		if (ok)	ok = clearBuf_s.LoadFromFile("data/clear.wav");
		if (ok)	ok = clear4Buf_s.LoadFromFile("data/clear4.wav");

		if (ok) {
			tilesTex_s.SetSmooth(false);

			moveSnd_s.SetBuffer(moveBuf_s);
			moveSnd_s.SetVolume(12.0f);
			lockSnd_s.SetBuffer(lockBuf_s);
			lockSnd_s.SetVolume(50.0f);
			clearSnd_s.SetBuffer(clearBuf_s);
			clearSnd_s.SetVolume(8.0f);
			clear4Snd_s.SetBuffer(clear4Buf_s);
			clear4Snd_s.SetVolume(8.0f);
		}

		return ok;
	}
}
