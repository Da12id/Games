#include "SampleScene.h"

#include "DummyEntity.h"
#include "Tank.h"
#include "Projectile.h"
#include "PowerUp.h"

#include "Debug.h"
#include <iostream>
#include <vector>

void SampleScene::OnInitialize()
{
	srand(time(nullptr));
	width = GetWindowWidth();
	height = GetWindowHeight();
	HorizontalLane = height / 9;
	VerticalLane = width / 5;
	Tank1 = CreateEntity<Tank>(50, sf::Color::Blue);
	Tank1->SetPosition(100, 100);
	Tank1->SetRigidBody(true);

	Tank2 = CreateEntity<Tank>(50, sf::Color::Green);
	Tank2->SetPosition(500, 500);
	Tank2->SetRigidBody(true);

	Tank1->SetSpeed(30);
	Tank2->SetSpeed(30);

}

void SampleScene::OnEvent(const sf::Event& event)
{
	if(Tank1 != nullptr && Tank2 != nullptr)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Z)
			{
				Tank1->SetState(Tank::State::Up);
			}

			if (event.key.code == sf::Keyboard::S)
			{
				Tank1->SetState(Tank::State::Down);
			}

			if (event.key.code == sf::Keyboard::D)
			{
				Tank1->SetState(Tank::State::Right);
			}

			if (event.key.code == sf::Keyboard::Q)
			{
				Tank1->SetState(Tank::State::Left);
			}

			if (event.key.code == sf::Keyboard::A)
			{
				Tank1->CanShoot = true;
			}
		
			if (event.key.code == sf::Keyboard::Up)
			{
				Tank2->SetState(Tank::State::Up);
			}

			if (event.key.code == sf::Keyboard::Down)
			{
				Tank2->SetState(Tank::State::Down);
			}

			if (event.key.code == sf::Keyboard::Right)
			{
				Tank2->SetState(Tank::State::Right);
			}

			if (event.key.code == sf::Keyboard::Left)
			{
				Tank2->SetState(Tank::State::Left);
			}

			if (event.key.code == sf::Keyboard::Space)
			{
				Tank2->CanShoot = true;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{

			if (event.key.code == sf::Keyboard::Z)
			{
				Tank1->SetState(Tank::State::Stop);
			}

			if (event.key.code == sf::Keyboard::S)
			{
				Tank1->SetState(Tank::State::Stop);
			}

			if (event.key.code == sf::Keyboard::A)
			{
				Tank1->CanShoot = false;
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				Tank2->SetState(Tank::State::Stop);
			}

			if (event.key.code == sf::Keyboard::Down)
			{
				Tank2->SetState(Tank::State::Stop);
			}

			if (event.key.code == sf::Keyboard::Space)
			{
				Tank2->CanShoot = false;
			}
		}
	}

	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::R)
			Restart();
}

void SampleScene::OnUpdate()
{
	dtTank1 += GetDeltaTime();
	dtTank2 += GetDeltaTime();
	dtPowerUp += GetDeltaTime();
	dtPowerUpEffect += GetDeltaTime();
	int i = (int)dtPowerUp;
	std::cout << i << std::endl;

	while(Tank1 != nullptr && Tank2 != nullptr)
	{
		if (Tank1->GetPosition().y <= 0)
			Tank1->SetPosition(Tank1->GetPosition().x, 10);

		if (Tank1->GetPosition().y >= height)
			Tank1->SetPosition(Tank1->GetPosition().x, height - 10);

		if (Tank1->GetPosition().x <= 0)
			Tank1->SetPosition(20, Tank1->GetPosition().y);

		if (Tank1->GetPosition().x >= width)
			Tank1->SetPosition(width - 10, Tank1->GetPosition().y);

		if (Tank2->GetPosition().y <= 0)
			Tank2->SetPosition(Tank2->GetPosition().x, 10);

		if (Tank2->GetPosition().y >= height)
			Tank2->SetPosition(Tank2->GetPosition().x, height - 10);

		if (Tank2->GetPosition().x <= 0)
			Tank2->SetPosition(20, Tank2->GetPosition().y);

		if (Tank2->GetPosition().x >= width)
			Tank2->SetPosition(width - 10, Tank2->GetPosition().y);

		if(Tank1->CanShoot == true)
			CreateProjectile();

		if(Tank2->CanShoot == true)
			CreateProjectile2();

		if (bulletTank1 != nullptr)
		{
			for (int x = 0; x < projectiles.size(); x++)
			{
				if (projectiles[x]->GetPosition().y <= 0)
				{
					projectiles[x]->Destroy();
					projectiles.erase(projectiles.begin() + x);
					break;
				}

				if (projectiles[x]->GetPosition().y >= height)
				{
					projectiles[x]->Destroy();
					projectiles.erase(projectiles.begin() + x);
					break;
				}

				if (projectiles[x]->GetPosition().x <= 0)
				{
					projectiles[x]->Destroy();
					projectiles.erase(projectiles.begin() + x);
					break;
				}

				if (projectiles[x]->GetPosition().x >= width)
				{
					projectiles[x]->Destroy();
					projectiles.erase(projectiles.begin() + x);
					break;
				}
			}
		}

		if (bulletTank2 != nullptr)
		{
			for (int x = 0; x < projectiles2.size(); x++)
			{
				if (projectiles2[x]->GetPosition().y <= 0)
				{
					projectiles2[x]->Destroy();
					projectiles2.erase(projectiles2.begin() + x);
					break;
				}

				if (projectiles2[x]->GetPosition().y >= height)
				{
					projectiles2[x]->Destroy();
					projectiles2.erase(projectiles2.begin() + x);
					break;
				}

				if (projectiles2[x]->GetPosition().x <= 0)
				{
					projectiles2[x]->Destroy();
					projectiles2.erase(projectiles2.begin() + x);
					break;
				}

				if (projectiles2[x]->GetPosition().x >= width)
				{
					projectiles2[x]->Destroy();
					projectiles2.erase(projectiles2.begin() + x);
					break;
				}
			}
		}

		position1 = Tank1->GetPosition();
		position2 = Tank2->GetPosition();
		Debug::DrawCircle(position1.x + 50 * Tank1->GetDireccionH(), position1.y + 50 * Tank1->GetDireccionV(), 20, sf::Color::Blue);
		Debug::DrawCircle(position2.x + 50 * Tank2->GetDireccionH(), position2.y + 50 * Tank2->GetDireccionV(), 20, sf::Color::Green);

			if (powerUp != nullptr && Tank1->IsColliding(powerUp))
			{
				Tank1->ApplyPowerUp(powerUp, Tank2);
				powerUp->Destroy();
				powerUp = nullptr;
				dtPowerUp = 0.f;
				dtPowerUpEffect = 0;
				ActivePowerUp = true;
			}

			if (powerUp != nullptr &&  Tank2->IsColliding(powerUp))
			{
				Tank2->ApplyPowerUp(powerUp, Tank1);
				powerUp->Destroy();
				powerUp = nullptr;
				dtPowerUp = 0.f;
				dtPowerUpEffect = 0;
				ActivePowerUp = true;
			}

		for (int x = 0; x < projectiles2.size(); x++)
		{
			if (projectiles2[x] != nullptr && Tank1->IsColliding(projectiles2[x]))
			{
				Tank1->DecrementLife();
				projectiles2[x]->Destroy();
				projectiles2.erase(projectiles2.begin() + x);
				std::cout << "Tank 1 a " << Tank1->GetLife() << " vies\n";
			}
			if (Tank1->GetLife()== 0)
			{
				Tank1->Destroy();
				Tank1 = nullptr;
				SomeoneDead = true;
				break;
			}
		}

		for (int x = 0; x < projectiles.size(); x++)
		{
			if (projectiles[x] != nullptr && Tank2->IsColliding(projectiles[x]))
			{
				Tank2->DecrementLife();
				projectiles[x]->Destroy();
				projectiles.erase(projectiles.begin() + x);
				std::cout << "Tank 2 a " << Tank2->GetLife()<< " vies\n";
			}
			if (Tank2->GetLife()== 0)
			{
				Tank2->Destroy();
				Tank2 = nullptr;
				SomeoneDead = true;
				break;
			}
		}
		break;
	}
	if (dtPowerUp >= 10.f && SomeoneDead == false)
	{
		SpawnPowerUp();
		dtPowerUp = 0.f;
	}

	if (ActivePowerUp == true && dtPowerUpEffect >= 7 && SomeoneDead == false)
	{
		Tank1->SetDelay(0.5f);
		Tank1->SetSpeed(30);
		Tank2->SetDelay(0.5f);
		Tank2->SetSpeed(30);
	}
}

void SampleScene::CreateProjectile()
{
	float delay = Tank1->GetDelay();
	if (dtTank1 >= delay)
	{
		bulletTank1 = CreateEntity<Projectile>(25, sf::Color::Red);
		bulletTank1->SetPosition(position1.x + 50 * Tank1->GetDireccionH(), position1.y + 50 * Tank1->GetDireccionV());
		bulletTank1->SetDirection(10 * Tank1->GetDireccionH(), 10 * Tank1->GetDireccionV(), 40);
		projectiles.push_back(bulletTank1);
		dtTank1 = 0.f;
	}
}

void SampleScene::CreateProjectile2()
{
	float delay = Tank2->GetDelay();
	if (dtTank2 >= delay)
	{
		bulletTank2 = CreateEntity<Projectile>(25, sf::Color::Yellow);
		bulletTank2->SetPosition(position2.x + 50 * Tank2->GetDireccionH(), position2.y + 50 * Tank2->GetDireccionV());
		bulletTank2->SetDirection(10 * Tank2->GetDireccionH(), 10 * Tank2->GetDireccionV(), 40);
		projectiles2.push_back(bulletTank2);
		dtTank2 = 0.f;
	}
}

void SampleScene::SpawnPowerUp()
{
	if (powerUp != nullptr)
	{
		powerUp->Destroy();
		powerUp = nullptr;
	}
	ChoosePowerUp = PickNumber(0, 3);
	switch (ChoosePowerUp)
	{
	case 0:
		powerUp = CreateEntity<PowerUp>(20, sf::Color::Magenta);
		powerUp->SetPosition(VerticalLane * PickNumber(1, 4), HorizontalLane * PickNumber(1, 8));
		powerUp->SetState(PowerUp::State::DelayIncrease);
		break;

	case 1:
		powerUp = CreateEntity<PowerUp>(20, sf::Color::Cyan);
		powerUp->SetPosition(VerticalLane * PickNumber(1, 4), HorizontalLane * PickNumber(1, 8));
		powerUp->SetState(PowerUp::State::DelayDecrease);
		break;

	case 2:
		powerUp = CreateEntity<PowerUp>(20, sf::Color::Black);
		powerUp->SetPosition(VerticalLane * PickNumber(1, 4), HorizontalLane * PickNumber(1, 8));
		powerUp->SetState(PowerUp::State::SpeedDecrease);
		break;

	case 3:
		powerUp = CreateEntity<PowerUp>(20, sf::Color::White);
		powerUp->SetPosition(VerticalLane * PickNumber(1, 4), HorizontalLane * PickNumber(1, 8));
		powerUp->SetState(PowerUp::State::SpeedIncrease);
		break;
	}
}

void SampleScene::Restart()
{
	while(!projectiles.empty())
	{
		projectiles[0]->Destroy();
		projectiles.erase(projectiles.begin());
	}

	while(!projectiles2.empty())
	{
		projectiles2[0]->Destroy();
		projectiles2.erase(projectiles2.begin());
	}
	
	if (powerUp != nullptr)
	{
		powerUp->Destroy();
		powerUp = nullptr;
	}

	if (Tank1 != nullptr)
	{
		Tank1->Destroy();
		Tank1 = nullptr;
	}

	if (Tank2 != nullptr)
	{
		Tank2->Destroy();
		Tank2 = nullptr;
	}

	SomeoneDead = false;

	dtTank1 = 0;
	dtTank2 = 0;
	dtPowerUp = 0;
	dtPowerUpEffect = 0;

	OnInitialize();
}

int SampleScene::PickNumber(int min, int max)
{
		int number = rand() % (max - min + 1) + min;
		return number;
}