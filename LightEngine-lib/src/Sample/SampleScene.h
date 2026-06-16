#pragma once

#include "Scene.h"

class Circle;

class SampleScene : public Scene
{
	Circle* circle;
	Circle* pEntity;

private:
	void CreateCircle();
	bool TrytoKick(Circle* pEntity, int x, int y);
	int score = 0;
	int life = 3;
	int point = 0;
	float dt = 0;
	float dtkickCircle = 0;
	float dtEliminatedCircle = 0;
	float width;
	float height;
	float HorizontalLane;
	float VerticalLane;
	bool circleSpawn = false;
	bool loose = false;
	int HowPoint(float dtkickCircle);
	int PickNumber(int min, int max);
	void DrawLines();

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	bool CircleisGood(Circle* circle);
};


