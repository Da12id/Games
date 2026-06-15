#include "SampleScene.h"

#include "DummyEntity.h"
#include "Tank.h"

#include "Debug.h"
#include <iostream>

void SampleScene::OnInitialize()
{
	Tank1 = CreateEntity<Tank>(50, sf::Color::Blue);
	Tank1->SetPosition(100, 100);
	Tank1->SetRigidBody(true);

	Tank2 = CreateEntity<Tank>(50, sf::Color::Green);
	Tank2->SetPosition(500, 500);
	Tank2->SetRigidBody(true);
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Z)
			Tank1->SetDirection(10 * Tank1->direccionH, 10 * Tank1->direccionV, 30);

		if (event.key.code == sf::Keyboard::S)
			Tank1->SetDirection(-10 * Tank1->direccionH, -10 * Tank1->direccionV, 30);
		
		if (event.key.code == sf::Keyboard::D)
			Tank1->SetState(Tank::State::Right);
		
		if (event.key.code == sf::Keyboard::Q)
			Tank1->SetState(Tank::State::Left);
		
		if (event.key.code == sf::Keyboard::Up)
			Tank2->SetDirection(10 * Tank2->direccionH, 10 * Tank2->direccionV, 30);

		if (event.key.code == sf::Keyboard::Down)
			Tank2->SetDirection(-10 * Tank2->direccionH, -10 * Tank2->direccionV, 50);
		
		if (event.key.code == sf::Keyboard::Right)
			Tank2->SetState(Tank::State::Right);
		
		if (event.key.code == sf::Keyboard::Left)
			Tank2->SetState(Tank::State::Left);
	}
	if(event.type == sf::Event::KeyReleased)
	{
		Tank1->SetDirection(0, 0, 0);
		Tank2->SetDirection(0, 0, 0);
	}

}

void SampleScene::OnUpdate()
{
	position1 = Tank1->GetPosition();
	position2 = Tank2->GetPosition();
	Debug::DrawCircle(position1.x + 50 * Tank1->direccionH, position1.y + 50 * Tank1->direccionV, 20, sf::Color::Blue);
	Debug::DrawCircle(position2.x + 50 * Tank2->direccionH, position2.y + 50 * Tank2->direccionV, 20, sf::Color::Green);
}
