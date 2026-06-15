#include "Tank.h"
#include "Debug.h"
#include <iostream>

void Tank::OnInitialize()
{

}

void Tank::OnUpdate()
{
	switch (mState)
	{
	case State::Right:
		position++;
		break;

	case State::Left:
		position++;
		break;
	}
	
	if (position == 4)
		position = 0;
	else if (position == -1)
		position = 3;

	switch (position)
	{
	case 0:
		direccionV = 1;
		direccionH = 0;
		break;

	case 1:
		direccionV = -1;
		direccionH = 0;
		break;

	case 2:
		direccionV = 0;
		direccionH = 1;
		break;

	case 3:
		direccionV = 0;
		direccionH = -1;
		break;
	}
}

bool Tank::SetState(State state)
{
	mState = state;
	return true;
}
