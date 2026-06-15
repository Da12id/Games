#pragma once
#include "Entity.h"
class Tank : public Entity
{
public:
	enum class State
	{
		Idle,
		Right,
		Left,

		Count
	};
	static constexpr int StateCount = static_cast<int>(State::Count);
	void OnInitialize() override;
	void OnUpdate() override;
	bool SetState(State state);
	int const GetDireccionH() { return direccionH; };
	int const GetDireccionV() { return direccionV; };
	int life = 3;

private:
	State mState = State::Idle;
	int position;
	int direccionH;
	int direccionV;
};
