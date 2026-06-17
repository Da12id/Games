#pragma once
#include "Entity.h"

#include <vector>

class Circle : public Entity
{
public:
	void OnCollision(Entity* other) override;
	
	enum class State {
		Good,
		Bad,

		Count
	};
	static constexpr int StateCount = static_cast<int>(State::Count);

	void OnUpdate() override;
	void SetState(State state) {mState = state;};
	State GetState() { return mState; };
	bool IsGood(Circle* circle);
	sf::Vector2f pos;
	float dt;

private:
	State mState = State::Count;
};

