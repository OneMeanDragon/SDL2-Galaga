#include "PlaySideBar.h"

PlaySideBar::PlaySideBar()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackGround = new Texture("black.png");
	mBackGround->Parent(this);
	mBackGround->Pos(Vector2(45.0f, 380.0f));
	mBackGround->Scale(Vector2(3.0f, 10.0f));

	mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, { 150, 0, 0 });
	mHighLabel->Parent(this);
	mHighLabel->Pos(Vector2(-26.0f, 0.0f));
	mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, { 150, 0, 0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(Vector2(26.0f, 32.0f));

	mHighScoreBoard = new ScoreBoard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Pos(Vector2(132.0f, 75.0f));

	mPlayerOneLabel = new Texture("1UP ", "emulogic.ttf", 32, { 150, 0, 0 });
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(Vector2(-26.0f, 160.0f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mPlayerOneLabelVisable = true;

	mPlayerOneScore = new ScoreBoard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(Vector2(132.0f, 203.0f));

	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Pos(Vector2(-40.0f, 420.0f));

	int i;
	for (i = 0; i < MAX_SHIP_TEXTURES; ++i)
	{
		mShipTextures[i] = new Texture("playership.png");
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Pos(Vector2(62.0f*(i % 3), 62.0f*(i/3))); //image is 60x60 (additional 2 is for space on screen between the extra ships)
	}

	mTotalShipsLabel = new ScoreBoard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Pos(Vector2( 16.0f + (62.0f*(i % 3)), 10.0f + (62.0f*(i / 3))));
	++i;
	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Pos(Vector2(-50.0f, 650.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.2f;

}

PlaySideBar::~PlaySideBar()
{
	mTimer = NULL;
	mAudio = NULL;

	delete mBackGround;
	mBackGround = NULL;

	delete mHighLabel;
	mHighLabel = NULL;
	delete mScoreLabel;
	mScoreLabel = NULL;

	delete mHighScoreBoard;
	mHighScoreBoard = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;

	delete mShips;
	mShips = NULL;

	for (int i = 0; i < MAX_SHIP_TEXTURES; ++i)
	{
		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}

	delete mTotalShipsLabel;
	mTotalShipsLabel = NULL;

	delete mFlags;
	mFlags = NULL;

	ClearFlags();
}

void PlaySideBar::ClearFlags()
{
	for (int i = 0; i < mFlagTextures.size(); ++i)
	{
		delete mFlagTextures[i];
		mFlagTextures[i] = NULL;
	}
	mFlagTextures.clear();
}

void PlaySideBar::AddNextFlag()
{
	if (mRemainingLevels >= 50)
	{
		AddFlag("level50flag.png", 62.0f, 50);
	}
	else if (mRemainingLevels >= 30) {
		AddFlag("level30flag.png", 62.0f, 30);
	}
	else if (mRemainingLevels >= 20) {
		AddFlag("level20flag.png", 62.0f, 20);
	}
	else if (mRemainingLevels >= 10) {
		AddFlag("level10flag.png", 52.0f, 10);
	}
	else if (mRemainingLevels >= 5) {
		AddFlag("level05flag.png", 27.0f, 5); //width is half that
	}
	else
	{
		AddFlag("level01flag.png", 27.0f, 1);
	}
}

void PlaySideBar::AddFlag(std::string filename, float width, int value)
{
	int index = mFlagTextures.size();
	if (index > 0)
	{
		mFlagXOffset += width * 0.5f;
	}

	mRemainingLevels -= value;
	mFlagTextures.push_back(new Texture(filename));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Pos(VEC2_RIGHT*mFlagXOffset);// Vector2());
	//whut
	mFlagXOffset += width * 0.5f;

	mAudio->PlaySFX("flag.wav");
}

void PlaySideBar::SetHighScore(int score)
{
	mHighScoreBoard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlaySideBar::SetLives(int lives)
{
	mTotalShips = lives;
	if (lives > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Score(mTotalShips);
	}
}

void PlaySideBar::SetLevel(int level)
{
	ClearFlags();
	mRemainingLevels = level;
	mFlagXOffset = 0.0f;
}


void PlaySideBar::Update()
{
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mPlayerOneLabelVisable = !mPlayerOneLabelVisable;
		mBlinkTimer = 0.0f;
	}
	if (mRemainingLevels > 0)
	{
		mFlagTimer += mTimer->DeltaTime();
		if (mFlagTimer >= mFlagInterval)
		{
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlaySideBar::Render()
{
	mBackGround->Render();
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreBoard->Render();
	if (mPlayerOneLabelVisable)
	{
		mPlayerOneLabel->Render();
	}
	mPlayerOneScore->Render();
	for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; ++i)
	{
		mShipTextures[i]->Render();
	}
	if (mTotalShips > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Render();
	}
	for (int f_i = 0; f_i < mFlagTextures.size(); ++f_i)
	{
		mFlagTextures[f_i]->Render();
	}

}