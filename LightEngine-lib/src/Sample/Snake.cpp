#include "Snake.h"

#include <iostream>

void Snake::OnUpdate()
{

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
