#include "SampleScene.h"

#include "DummyEntity.h"
#include "Tank.h"
#include "Projectile.h"

#include "Debug.h"
#include <iostream>
#include <vector>

void SampleScene::OnInitialize()
{
	dt = 0;
	Tank1 = CreateEntity<Tank>(50, sf::Color::Blue);
	Tank1->SetPosition(100, 100);
	Tank1->SetRigidBody(true);

	Tank2 = CreateEntity<Tank>(50, sf::Color::Green);
	Tank2->SetPosition(500, 500);
	Tank2->SetRigidBody(true);

}

void SampleScene::OnEvent(const sf::Event& event)
{
	if(Tank1 != nullptr && Tank2 != nullptr)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Z)
				Tank1->SetDirection(10 * Tank1->GetDireccionH(), 10 * Tank1->GetDireccionV(), 30);

			if (event.key.code == sf::Keyboard::S)
				Tank1->SetDirection(-10 * Tank1->GetDireccionH(), -10 * Tank1->GetDireccionV(), 30);

			if (event.key.code == sf::Keyboard::D)
				Tank1->SetState(Tank::State::Right);

			if (event.key.code == sf::Keyboard::Q)
				Tank1->SetState(Tank::State::Left);

			if (event.key.code == sf::Keyboard::A)
				CreateProjectile();

			if (event.key.code == sf::Keyboard::Up)
				Tank2->SetDirection(10 * Tank2->GetDireccionH(), 10 * Tank2->GetDireccionV(), 30);

			if (event.key.code == sf::Keyboard::Down)
				Tank2->SetDirection(-10 * Tank2->GetDireccionH(), -10 * Tank2->GetDireccionV(), 50);

			if (event.key.code == sf::Keyboard::Right)
				Tank2->SetState(Tank::State::Right);

			if (event.key.code == sf::Keyboard::Space)
				CreateProjectile2();

			if (event.key.code == sf::Keyboard::Left)
				Tank2->SetState(Tank::State::Left);
		}
		if (event.type == sf::Event::KeyReleased)
		{
			Tank1->SetDirection(0, 0, 0);
			Tank2->SetDirection(0, 0, 0);
		}
	}
}

void SampleScene::OnUpdate()
{
	dt += GetDeltaTime();
	while(Tank1 != nullptr && Tank2 != nullptr)
	{
		position1 = Tank1->GetPosition();
		position2 = Tank2->GetPosition();
		Debug::DrawCircle(position1.x + 50 * Tank1->GetDireccionH(), position1.y + 50 * Tank1->GetDireccionV(), 20, sf::Color::Blue);
		Debug::DrawCircle(position2.x + 50 * Tank2->GetDireccionH(), position2.y + 50 * Tank2->GetDireccionV(), 20, sf::Color::Green);

		for (int x = 0; x < projectiles2.size(); x++)
		{
			if (Tank1->IsColliding(projectiles2[x]))
			{
				Tank1->life--;
				projectiles2[x]->Destroy();
				std::cout << "Tank 1 a " << Tank1->life << " vies\n";
			}
			if (Tank1->life == 0)
			{
				Tank1->Destroy();
				Tank1 = nullptr;
				break;
			}
		}

		for (int x = 0; x < projectiles.size(); x++)
		{
			if (Tank2->IsColliding(projectiles[x]))
			{
				Tank2->life--;
				projectiles[x]->Destroy();
				std::cout << "Tank 2 a " << Tank2->life << " vies\n";
			}
			if (Tank2->life == 0)
			{
				Tank2->Destroy();
				Tank2 = nullptr;
				break;
			}
		}
		break;
	}
}

void SampleScene::CreateProjectile()
{
	if (dt >= 0.5f)
	{
		bulletTank1 = CreateEntity<Projectile>(25, sf::Color::Red);
		bulletTank1->SetPosition(position1.x + 50 * Tank1->GetDireccionH(), position1.y + 50 * Tank1->GetDireccionV());
		bulletTank1->SetDirection(10 * Tank1->GetDireccionH(), 10 * Tank1->GetDireccionV(), 40);
		projectiles.push_back(bulletTank1);
		dt = 0;
	}
}

void SampleScene::CreateProjectile2()
{
	if (dt >= 0.5)
	{
		bulletTank2 = CreateEntity<Projectile>(25, sf::Color::Yellow);
		bulletTank2->SetPosition(position2.x + 50 * Tank2->GetDireccionH(), position2.y + 50 * Tank2->GetDireccionV());
		bulletTank2->SetDirection(10 * Tank2->GetDireccionH(), 10 * Tank2->GetDireccionV(), 40);
		projectiles2.push_back(bulletTank2);
		dt = 0;
	}
}
