#pragma once
#include "Entity.h"
class Tank : public Entity
{
public:
	enum class State
	{
		Idle,
		Up,
		Down,
		Right,
		Left,

		Count
	};
	static constexpr int StateCount = static_cast<int>(State::Count);
	void OnInitialize() override;
	void OnUpdate() override;
	bool SetState(State state);
	const int GetdireccionH() { return direccionH; };
	const int GetdireccionV() { return direccionV; };
private:
	State mState = State::Idle;
	int direccionH;
	int direccionV;
	int position;

};
