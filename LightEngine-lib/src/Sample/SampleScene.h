#pragma once

#include "Scene.h"

class DummyEntity;
class Tank;

class SampleScene : public Scene
{
	Tank* Tank1;
	Tank* Tank2;


private:
	int direccionH;
	int direccionV;
	sf::Vector2f position1;
	sf::Vector2f position2;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


