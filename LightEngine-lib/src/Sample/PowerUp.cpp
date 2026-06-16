#include "PowerUp.h"

void PowerUp::OnInitialize()
{
}

void PowerUp::OnUpdate()
{
	switch (mState)
	{
	case State::SpeedIncrease:
		break;

	case State::SpeedDecrease:
		break;

	case State::DelayIncrease:
		break;

	case State::DelayDecrease:
		break;
	}

}

bool PowerUp::SetState(State state)
{
	mState = state;
	return true;
}

