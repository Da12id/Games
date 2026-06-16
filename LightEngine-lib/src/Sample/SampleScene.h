#pragma once

#include "Scene.h"
#include <vector>

class DummyEntity;
class Tank;
class Projectile;

class SampleScene : public Scene
{
	Tank* Tank1;
	Tank* Tank2;
	std::vector<Projectile*> projectiles;
	Projectile* bulletTank1;
	std::vector<Projectile*> projectiles2;
	Projectile* bulletTank2;

private:
	float dt;
	int direccionH;
	int direccionV;
	sf::Vector2f position1;
	sf::Vector2f position2;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void CreateProjectile();
	void CreateProjectile2();
	void Restart();
};


