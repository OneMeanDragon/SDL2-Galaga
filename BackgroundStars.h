#ifndef _BACKGROUNDSTARS_H
#define _BACKGROUNDSTARS_H

#include "StarLayer.h"

class BackgroundStars
{
private:
	static const int LAYER_COUNT = 3;

	static BackgroundStars* sInstance;

	StarLayer* mLayer[LAYER_COUNT];

public:
	static BackgroundStars* Instance();
	static void Release();

	void Scroll(bool b);

	void Update();
	void Render();

private:
	BackgroundStars();
	~BackgroundStars();
};


#endif
