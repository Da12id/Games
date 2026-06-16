#include "Circle.h"

#include <iostream>

void Circle::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}

void Circle::OnUpdate()
{
	switch (mState)
	{
	case State::Good:
		break;

	case State::Bad:
		break;
	}
}

bool Circle::IsGood(Circle* circle)
{
	if(circle->GetState() == State::Bad)
		return false;
	return true;
}

