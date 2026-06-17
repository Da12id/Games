#include "SampleScene.h"

#include "Circle.h"

#include "Debug.h"

#include <iostream>

#include <cmath>

#include <algorithm>

#include <vector>

void SampleScene::OnInitialize()
{
	srand(time(nullptr));
	width = GetWindowWidth();
	height = GetWindowHeight();
	VerticalLane = width/8;
	HorizontalLane = height/5;
	CreateCircle();
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left && circle != nullptr)
	{
		for(int x = Circles.size() - 1; x >= 0; x--)
		{
			if(Circles[x] != nullptr)
			{
				if (TrytoKick(Circles[x], event.mouseButton.x, event.mouseButton.y))
				{
					Circles.erase(Circles.begin() + x);
					kick ++;
				}
			}
		}
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::M)
			DrawLines();
	}

}

void SampleScene::CreateCircle()
{
	HowCircles(&HowCircle);
	for(int x = 0; x<HowCircle; x++)
	{
		int number = PickNumber(0, 2);
		switch (number)
		{
		case 0:
			circle = CreateEntity<Circle>(50, sf::Color::Green);
			circle->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 4));
			circle->SetState(Circle::State::Good);
			circle->pos = sf::Vector2(circle->GetPosition().x, circle->GetPosition().y);
			if (x != 0)
			{
				while (std::any_of(Circles.begin(), Circles.end(), [&](Circle* Tcircle) {return Tcircle->GetPosition() == circle->pos; }))
				{
					circle->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 4));
				}
			}
			Circles.push_back(circle);
			break;

		case 1:
			circle = CreateEntity<Circle>(50, sf::Color::Green);
			circle->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 4));
			circle->SetState(Circle::State::Good);
			circle->pos = sf::Vector2(circle->GetPosition().x, circle->GetPosition().y);
			if( x != 0)
			{
				while (std::any_of(Circles.begin(), Circles.end(), [&](Circle* Tcircle) {return Tcircle->GetPosition() == circle->pos; }))
				{
					circle->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 4));
				}
			}
			Circles.push_back(circle);
			break;

		case 2:
			circle = CreateEntity<Circle>(50, sf::Color::Red);
			circle->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 4));
			circle->SetState(Circle::State::Bad);
			circle->pos = sf::Vector2(circle->GetPosition().x, circle->GetPosition().y);
			if (x != 0)
			{
				while (std::any_of(Circles.begin(), Circles.end(), [&](Circle* Tcircle) {return Tcircle->GetPosition() == circle->pos; }))
				{
					circle->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 4));
				}
			}
			Circles.push_back(circle);
			break;
		}
	}
}

bool SampleScene::TrytoKick(Circle* circle, int x, int y)
{
	if (circle->IsInside(x, y) == false)
		return false;


	if(CircleisGood(circle))
	{
		system("cls");
		point = HowPoint(dtkickCircle);
		score += point;
		if(score <= 1)
			std::cout << "tu a " << score << " point\n";
		else
			std::cout << "tu a " << score << " points\n";
	}
	else
	{
		system("cls");
		life--;
	}
	dtSpawnCircle = 0;
	dtkickCircle = 0;
	circle->Destroy();
	return true;
}

void SampleScene::OnUpdate()
{
	//DrawLines();
	dtGame += GetDeltaTime();
	dtSpawnCircle += GetDeltaTime();

	if (!Circles.empty())
	{
		dtkickCircle += GetDeltaTime();
		for (int x = 0; x < Circles.size(); x++)
		{
			Circles[x]->dt += GetDeltaTime();
		}
	}

	if (life == 0 && loose == false)
	{
		if(score <=1)
			std::cout << "oh non tu a perdue\n" << "tu a eu " << score << " point\n";
		else
			std::cout << "oh non tu a perdue\n" << "tu a eu " << score << " points\n";
		loose = true;
	}

	for(int x = Circles.size() - 1; x>= 0; x--)
	{
		if (Circles[x] != nullptr)
		{
			if (Circles[x]->dt >= 2 && Circles[x]->IsGood(Circles[x]) == false)
			{
				system("cls");
				Circles[x]->dt = 0.F;
				Circles[x]->Destroy();
				Circles.erase(Circles.begin() + x);
				std::cout << "Bravo tu a eviter le piege\n";
			}
		}
	}

	for (int x = Circles.size() - 1; x >= 0; x--)
	{
		if (Circles[x] != nullptr)
		{
			if (Circles[x]->dt >= 3)
			{
				system("cls");
				life--;
				if (score <= 1)
					std::cout << "oh non tu a perdue\n" << "tu a eu " << score << " point";
				else
					std::cout << "oh non tu a perdue\n" << "tu a eu " << score << " points";
				loose = true;
				Circles[x]->dt = 0.f;
				Circles[x]->Destroy();
				Circles.erase(Circles.begin() + x);
			}
		}
	}
	if (Circles.empty() && loose == false)
	{
		CreateCircle();
	}
}

bool SampleScene::CircleisGood(Circle* circle)
{
	return  circle->IsGood(circle);
}

int SampleScene::HowPoint(float dtkickCircle)
{
	std::cout <<"tu a mit " <<RoundNbr(dtkickCircle, 1) << " seconde\n";

	if (dtkickCircle < 0.5f)
	{
		point = 3;
	}
	else if (dtkickCircle <= 1.0f)
	{
		point = 2;
	}
	else if (dtkickCircle <= 2.5f)
	{
		point = 1;
	}
	std::cout << "tu gagne " << point << " point \n";
	return point;
}

void SampleScene::HowCircles(int* HowCircle)
{
	if (dtGame <= 10)
		*HowCircle = 1;
	else if (dtGame <= 20)
		*HowCircle = 2;
	else if (dtGame <= 30)
		*HowCircle = 4;
}

int SampleScene::PickNumber(int min, int max)
{
	int number = rand() % (max - min + 1) + min;
	return number;
}

float SampleScene::RoundNbr(float value, int decimal)
{
	float factor = std::pow(10, decimal);
	return std::round(value * factor) / factor;
}

void SampleScene::DrawLines()
{
	//Draw horizontal lines
	Debug::DrawLine(0, HorizontalLane, width, HorizontalLane, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 2, width, HorizontalLane * 2, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 3, width, HorizontalLane * 3, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 4, width, HorizontalLane * 4, sf::Color::Red);
	//Draw vertical lines
	Debug::DrawLine(VerticalLane, 0, VerticalLane, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 2, 0, VerticalLane * 2, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 3, 0, VerticalLane * 3, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 4, 0, VerticalLane * 4, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 5, 0, VerticalLane * 5, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 6, 0, VerticalLane * 6, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 7, 0, VerticalLane * 7, height, sf::Color::Green);
}