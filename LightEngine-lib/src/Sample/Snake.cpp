#include "Snake.h"

#include <iostream>

void Snake::OnUpdate()
{
	//OldPosition = GetPosition();
	switch (mState)
	{
	case State::Up:
		SetDirection(0, -10, 30);
		break;

	case State::Right:
		SetDirection(10, 0, 30);
		break;

	case State::Down:
		SetDirection(0, 10, 30);
		break;

	case State::Left:
		SetDirection(-10, 0, 30);
		break;
	}
}

bool Snake::SetState(State state)
{	
	int currentState = static_cast<int>(mState);
	int newState = static_cast<int>(state);

	if(mTransition[currentState][newState] == 0)
		return false;
	mState = state;
	return true;
}
