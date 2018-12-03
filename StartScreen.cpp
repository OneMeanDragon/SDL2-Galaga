#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top bar entitys
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200,0,0 });
	mHiScore = new Texture("HI-SCORE", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerOneScore = new ScoreBoard();
	mTopScore = new ScoreBoard();
	mPlayerTwoScore = new ScoreBoard();

	
	mPlayerOne->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);
	
	mPlayerOne->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * -0.21f, 0.0f));// Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.f));
	mHiScore->Pos(Vector2(0.0f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.21f, 0.f));
	
	mPlayerOneScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * -0.18f, 40.0f));
	mTopScore->Pos(Vector2((28.0f*4), 40.0f));
	mPlayerTwoScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.3985f, 40.0f));

	/*
		mPlayerOneScore->Score(99999999);
		mTopScore->Score(99999999);			//Debug positions.
		mPlayerTwoScore->Score(99999999);
	*/
	mTopScore->Score(30000); //Default HI-SCORE 30000

	mTopBar->Parent(this);

	//Logo entitys
	mLogo = new Texture("galagalogo.png", 0, 0, 360, 161);
	mAnimatedLogo = new AnimatedTexture("galagalogo.png", 0, 0, 360, 161, 3, 0.16f, AnimatedTexture::horizontal);
	
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));

	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	//Play modes entitys
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("1 Player ", "emulogic.ttf", 32, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("cursor.png");

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2(0.f, -35.f));
	mTwoPlayerMode->Pos(Vector2(0.f,  35.f));
	mCursor->Pos(Vector2(-176.0f, -35.0f));

	mPlayModes->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;


	//bottom bar entitys
	mBotBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.70f));
	mNamco = new Texture("namco", "namco__.ttf", 36,    { 200,   0,   0 });
	mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32,   { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

	mNamco->Parent(mBotBar);
	mDates->Parent(mBotBar);
	mRights->Parent(mBotBar);

	mNamco->Pos(Vector2(0.f, 0.f));
	mDates->Pos(Vector2(0.f, 90.f));
	mRights->Pos(Vector2(0.f, 132.f));

	mBotBar->Parent(this);

	//screen animation vars
	ResetAnimation();

	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen()
{
	//free top bar entitys
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mHiScore;
	mHiScore = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
	delete mTopScore;
	mTopScore = NULL;
	delete mPlayerTwoScore;
	mPlayerTwoScore = NULL;

	//free logo
	delete mLogo;
	mLogo = NULL;
	delete mAnimatedLogo;
	mAnimatedLogo = NULL;

	//free Play modes entitys
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
	delete mCursor;
	mCursor = NULL;

	//bottom bar entitys
	delete mBotBar;
	mBotBar = NULL;
	delete mNamco;
	mNamco = NULL;
	delete mDates;
	mDates = NULL;
	delete mRights;
	mRights = NULL;
}

void StartScreen::ResetAnimation()
{
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode()
{
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	mSelectedMode += change;
	if (mSelectedMode < 0)
	{
		mSelectedMode = 1;
	} else if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}
	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

void StartScreen::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		Pos(lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));
		if (mAnimationTimer >= mAnimationTotalTime)
		{
			mAnimationDone = true;
			mStars->Scroll(false);
		}
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
		{
			mAnimationTimer = mAnimationTotalTime;
		}
	} else {
		mAnimatedLogo->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
		{
			ChangeSelectedMode(1);
		} else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}
}

void StartScreen::Render()
{
	mPlayerOne->Render();
	mHiScore->Render();
	mPlayerTwo->Render();
	mPlayerOneScore->Render();
	mTopScore->Render();
	mPlayerTwoScore->Render();


	if (!mAnimationDone) {
		mLogo->Render();
	} else {
		mAnimatedLogo->Render();
	}

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mNamco->Render();
	mDates->Render();
	mRights->Render();
}