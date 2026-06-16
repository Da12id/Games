#pragma once
#include "Entity.h"
#include <SFML/Graphics/Color.hpp>
#include <string>
class PowerUp : public Entity
{
public:
	enum class State
	{
		SpeedIncrease,
		SpeedDecrease,
		DelayIncrease,
		DelayDecrease,

		Count
	};
	void OnInitialize() override;
	void OnUpdate() override;
	State GetState() { return mState; };
	bool SetState(State state);
private:
	State mState = State::Count;
};

