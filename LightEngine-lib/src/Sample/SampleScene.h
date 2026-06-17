#pragma once

#include "Scene.h"
#include <vector>

class Tank;
class Projectile;
class PowerUp;

class SampleScene : public Scene
{
	Tank* Tank1;
	Tank* Tank2;
	std::vector<Projectile*> projectiles;
	Projectile* bulletTank1;
	std::vector<Projectile*> projectiles2;
	Projectile* bulletTank2;
	PowerUp* powerUp;

private:
	float dtTank1 = 0;
	float dtTank2 = 0;
	float dtPowerUp = 0;
	float dtPowerUpEffect = 0;
	float width;
	float height;
	float HorizontalLane;
	float VerticalLane;
	int direccionH;
	int direccionV;
	int ChoosePowerUp;
	bool ActivePowerUp = false;
	bool SomeoneDead = false;
	bool activeZ = false;
	bool activeA = false;
	bool activeS = false;
	bool activeSpace = false;
	bool activeUp = false;
	bool activeDown = false;
	sf::Vector2f position1;
	sf::Vector2f position2;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void WhatCommand(const sf::Keyboard::Key touch);
	void OnUpdate() override;
	void CreateProjectile();
	void CreateProjectile2();
	void SpawnPowerUp();
	void Restart();
	int PickNumber(int min, int max);
};


