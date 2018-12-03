#ifndef _BULLET_H
#define _BULLET_H

#include "Texture.h"
#include "Timer.h"

using namespace QuickSDL;

class Bullet : public GameEntity
{
private:
	const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;
	
	float mSpeed;

	Texture* mTexture;

public:
	Bullet();
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	void Update();
	void Render();
};


#endif
