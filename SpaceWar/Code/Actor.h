#pragma once
#ifndef ACTOR_HEAD
#define ACTOR_HEAD
#include <vector>
#include <string>
#include <SDL_image.h>
#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPause,
		EDead
	};
	Actor();
	Actor(const Vector2 &pos, const float &width, const float &height,
		  const float &rockSpeed_, const std::vector<SDL_Texture *> &actions,
		  const int actionIndex = 0, State state_ = EActive);

	virtual ~Actor();

	// Getters/setters
	const Vector2 &GetPosition() const { return mPosition; }
	void SetPosition(const Vector2 &pos) { mPosition = pos; }
	const float &GetHeight() const { return mRect.h; }
	const float &GetWidth() const { return mRect.w; }
	const float &GetRockSpeed() const { return rockSpeed; }
	void SetRockSpeed(const float &speed) { rockSpeed = speed; }
	const SDL_Rect &GetRect() const { return mRect; }
	const State &GetState() const { return state; }
	void SetState(const State &state_) { state = state_; }
	const int &GetActionIndex() const { return mActionIndex; }
	void SetActionIndex(const int &index) { mActionIndex = index; }
	const float &GetRockIndex() const { return rockIndex; }
	void SetRockIndex(const float &index) { rockIndex = index; }
	const std::vector<SDL_Texture *> &GetActorTextures() const { return mActorTextures; }
	void SetActorTextures(const std::vector<SDL_Texture *> &textures) { mActorTextures = textures; }
	// Update actor
	void virtual UpdateActor(const float &deltaTime);

protected:
	// Actor's state
	State state;
	// Actor's Block
	SDL_Rect mRect;
	// Actor's position
	Vector2 mPosition;
	// picture rock speed
	float rockSpeed;
	// RockIndex
	float rockIndex;
	// Action index
	int mActionIndex;
	std::vector<SDL_Texture *> mActorTextures;
};
#endif // !ACTOR_HEAD
