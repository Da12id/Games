#pragma once
#include <vector>
#include "Entity.h"

class Snake : public Entity
{
public:
	enum class State {
		Idle,
		Up,
		Down,
		Right,
		Left,

		Count
	};
	static constexpr int StateCount = static_cast<int>(State::Count);
	void OnUpdate() override;

private:
	State mState = State::Idle;

	int mTransition[StateCount][StateCount] =
	{//Idle  //Up //Down //Right  //Left
		{0, 1, 1, 1, 1},          //Idle
		{0, 0, 0, 1, 1},         //Up
		{0, 0, 0, 1, 1},          //Down
		{0, 1, 1, 0, 0},         //Right
		{0, 1, 1, 0, 0}         //Left
	};

public:
	bool SetState(State state);
	State GetState() { return mState; };
	sf::Vector2f OldPos;

};

