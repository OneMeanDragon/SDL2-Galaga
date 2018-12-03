#include "Player.h"


Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;

	mShip = new Texture("playership.png");
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(32.0f, 768.0f);

	mDeathAnimation = new AnimatedTexture("explode.png", 0, 0, 128, 144, 4, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		mBullets[i] = new Bullet();
	}
}


Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mShip;
	mShip = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}

}

void Player::HandleMovement()
{
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime(), world);
	} else if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(-VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime(), world);
	}

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x)
	{
		pos.x = mMoveBounds.x;
	} else if (pos.x > mMoveBounds.y)
	{
		pos.x = mMoveBounds.y;
	}
	Pos(pos);


}

void Player::HandleFiring()
{
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_BULLETS; ++i)
		{
			if (!mBullets[i]->Active())
			{
				mBullets[i]->Fire(Pos());
				mAudio->PlaySFX("pew.wav");
				break;
			}
		}
	}
}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::IsAnimating()
{
	return mAnimating;
}

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}

void Player::WasHit()
{
	mLives--;
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("explosion.wav");

}

void Player::Update()
{
	if (mAnimating)
	{
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	} else {
		if (Active()) {
			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		mBullets[i]->Update();
	}

}

void Player::Render()
{
	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		} else {
			mShip->Render();
		}
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		mBullets[i]->Render();
	}

}