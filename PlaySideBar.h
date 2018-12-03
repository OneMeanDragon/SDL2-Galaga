#ifndef _PLAYSIDEBAR_H
#define _PLAYSIDEBAR_H

#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity
{
private:
	Timer* mTimer;
	AudioManager* mAudio;
	Texture* mBackGround;

	Texture* mHighLabel;
	Texture* mScoreLabel;
	ScoreBoard* mHighScoreBoard;

	Texture* mPlayerOneLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mPlayerOneLabelVisable;
	ScoreBoard* mPlayerOneScore;

	static const int MAX_SHIP_TEXTURES = 5;
	GameEntity* mShips;
	Texture* mShipTextures[MAX_SHIP_TEXTURES];
	ScoreBoard* mTotalShipsLabel;
	int mTotalShips;

	GameEntity* mFlags;
	std::vector<Texture*> mFlagTextures;
	int mRemainingLevels;
	int mFlagXOffset;
	float mFlagTimer;
	float mFlagInterval;

private:
	void ClearFlags();
	void AddNextFlag();
	void AddFlag(std::string filename, float width, int value);

public:
	PlaySideBar();
	~PlaySideBar();
	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetLives(int lives);
	void SetLevel(int level);
	void Update();
	void Render();
};


#endif
