#pragma once
#include "Entity.h"

class PowerUp;

class Tank : public Entity
{
public:
	enum class State
	{
		Idle,
		Right,
		Left,
		Up,
		Down,
		Stop,

		Count
	};
	static constexpr int StateCount = static_cast<int>(State::Count);
	void OnInitialize() override;
	void OnUpdate() override;
	bool SetState(State state);
	int const GetDireccionH() { return direccionH; };
	int const GetDireccionV() { return direccionV; };
	int const GetLife() { return life; };
	float const GetDelay() { return delay; };
	float const GetSpeed() {return mSpeed; };
	State const GetState() { return mState; };
	void DecrementLife() { life--; };
	void SetDelay(float newDelay) { delay = newDelay; };
	void ApplyPowerUp(PowerUp* powerUp, Tank* otherTank);
	void IncreaseSpeed(float newSpeed) { this->SetSpeed(newSpeed); };
	void DecreaseSpeed(Tank* otherTank, float newSpeed) { otherTank->SetSpeed(newSpeed); };
	void DecreaseDelay(float newDelay) { this->SetDelay(newDelay); };
	void IncreaseDelay(Tank* otherTank, float newDelay){otherTank->SetDelay(newDelay);};
	bool CanShoot = false;

private:
	State mState = State::Idle;
	int position;
	int direccionH;
	int direccionV;
	float delay = 0.5f;
	int life = 3;
};
