#pragma once

#include "Scene.h"

#include <vector>

class Snake;

class Apple;

class SampleScene : public Scene
{
	std::vector<Snake* >snake;
	Snake* sizeSnake;
	Apple* apple;

private:
	float height;
	float width;
	float HorizontalLane;
	float VerticalLane;
	bool loose = false;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void IncrementSize();
	void SpawnApple();
	void ChangeDirection(int x);
	int PickNumber(int min, int max);

private:
	void DrawLines();
};


