#pragma once

#include "Scene.h"
#include <vector>

class Circle;

class SampleScene : public Scene
{
	Circle* circle;
	std::vector<Circle*>Circles;
	Circle* pEntity;

private:
	void CreateCircle();
	bool TrytoKick(Circle* pEntity, int x, int y);
	int score = 0;
	int life = 1;
	int point = 0;
	int HowCircle = 0;
	float dtGame = 0;
	float dtSpawnCircle = 0;
	float dtkickCircle = 0;
	float dtEliminatedCircle = 0;
	float width;
	float height;
	float HorizontalLane;
	float VerticalLane;
	bool loose = false;
	int HowPoint(float dtkickCircle);
	void HowCircles(int* HowCircle);
	int PickNumber(int min, int max);
	float RoundNbr(float value, int decimal);
	void DrawLines();

	int kick = 0;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	bool CircleisGood(Circle* circle);
};


