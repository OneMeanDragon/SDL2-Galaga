#include "BackgroundStars.h"

BackgroundStars* BackgroundStars::sInstance = NULL;

BackgroundStars* BackgroundStars::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new BackgroundStars();
	}
	return sInstance;
}

void BackgroundStars::Release()
{
	delete sInstance;
	sInstance = NULL;
}

BackgroundStars::BackgroundStars()
{
	for (int i = 0; i < LAYER_COUNT; ++i)
	{
		mLayer[i] = new StarLayer(i);
	}
}

BackgroundStars::~BackgroundStars()
{
	for (int i = 0; i < LAYER_COUNT; ++i)
	{
		delete mLayer[i];
		mLayer[i] = NULL;
	}
}

void BackgroundStars::Scroll(bool b)
{
	Star::Scroll(b);
}

void BackgroundStars::Update()
{
	for (int i = 0; i < LAYER_COUNT; ++i)
	{
		mLayer[i]->Update();
	}
}

void BackgroundStars::Render()
{
	for (int i = 0; i < LAYER_COUNT; ++i)
	{
		mLayer[i]->Render();
	}
}
