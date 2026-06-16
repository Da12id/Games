#include "Tank.h"
#include "PowerUp.h"
#include "Debug.h"

#include <iostream>

void Tank::OnInitialize()
{

}

void Tank::OnUpdate()
{
	switch (mState)
	{
	case State::Idle:
		break;

	case State::Right:
		position++;
		SetState(Tank::State::Idle);
		break;

	case State::Left:
		position--;
		SetState(Tank::State::Idle);
		break;
	}

	if (position == 4)
		position = 0;
	else if (position == -1)
		position = 3;
	switch (position)
	{
	case 0:
		direccionV = -1;
		direccionH = 0;
		break;

	case 1:
		direccionV = 0;
		direccionH = 1;
		break;

	case 2:
		direccionV = 1;
		direccionH = 0;
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

void Tank::ApplyPowerUp(PowerUp* powerUp, Tank* otherTank)
{
	switch (powerUp->GetState())
	{
	case PowerUp::State::DelayDecrease:
		this->DecreaseDelay(0.25);
		break;

	case PowerUp::State::DelayIncrease:
		this->IncreaseDelay(otherTank, 0.75);
		break;

	case PowerUp::State::SpeedDecrease:
		this->DecreaseSpeed(otherTank, 20);
		break;

	case PowerUp::State::SpeedIncrease:
		this->IncreaseSpeed(45);
		break;
	}
}
