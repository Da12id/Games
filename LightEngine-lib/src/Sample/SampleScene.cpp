#include "SampleScene.h"

#include "Circle.h"

#include "Debug.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	srand(time(nullptr));
	width = GetWindowWidth();
	height = GetWindowHeight();
	VerticalLane = width/4;
	HorizontalLane = height/3 ;
	CreateCircle();
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (TrytoKick(circle, event.mouseButton.x, event.mouseButton.y))
		circle = nullptr;
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::M)
			DrawLines();
	}

}

void SampleScene::CreateCircle()
{
	circleSpawn = true;
	int number = PickNumber(0, 1);
	switch (number)
	{
	case 0:
		circle = CreateEntity<Circle>(50, sf::Color::Green);
		circle->SetPosition(VerticalLane * PickNumber(1,3),HorizontalLane * PickNumber(1,2));
		circle->SetState(Circle::State::Good);
		break;

	case 1:
		circle = CreateEntity<Circle>(50, sf::Color::Red);
		circle->SetPosition(VerticalLane * PickNumber(1, 3), HorizontalLane * PickNumber(1, 2));
		circle->SetState(Circle::State::Bad);
		break;
	}
}

bool SampleScene::TrytoKick(Circle* circle, int x, int y)
{
	if (circle->IsInside(x, y) == false)
		return false;

	circle->Destroy();

	if(CircleisGood(circle))
	{
		system("cls");
		point = HowPoint(dtkickCircle);
		score += point;
		std::cout << "tu a " << score << " points\n";
		point = 0;
	}
	else
	{
		system("cls");
		life--;
		std::cout << "tu perd une vie, il t'en reste " << life << std::endl;
	}
	dt = 0;
	dtkickCircle = 0;
	circleSpawn = false;
	return true;
}

void SampleScene::OnUpdate()
{
	//DrawLines();
	dt += GetDeltaTime();
	if (circle == nullptr && dt >= 1 && loose == false)
	{
		CreateCircle();
		dt = 0.f;
	}

	if (circleSpawn)
	{
		dtkickCircle += GetDeltaTime();
	}

	if (life == 0 && loose == false)
	{
		std::cout << "oh non tu a perdue\n"<<"tu a eu "<< score<<" points";
		loose = true;
	}

	if (dtkickCircle >= 4)
	{
		system("cls");
		if (CircleisGood(circle))
		{
			life--;
			std::cout << "tu perd une vie, il t'en reste " << life << std::endl;
		}
		else
			std::cout << "Bravo tu a eviter le piege\n";

		circle->Destroy();
		circle = nullptr;
		dtkickCircle = 0.f;
		CreateCircle();
	}
}

bool SampleScene::CircleisGood(Circle* circle)
{
	return  circle->IsGood(circle);
}


int SampleScene::HowPoint(float dtkickCircle)
{
	std::cout <<"tu a mit " << (int)dtkickCircle<<" seconde\n";

	if (dtkickCircle < 0.5)
	{
		point = 3;
	}
	else if (dtkickCircle <= 2)
	{
		point = 2;
	}
	else if (dtkickCircle <= 4)
	{
		point = 1;
	}
	else
	{
		std::cout << "supp a 4\n";
		point = 0;
	}
	std::cout << "tu gagne " << point << " point \n";
	return point;
}

int SampleScene::PickNumber(int min, int max)
{
	int number = rand() % (max - min + 1) + min;
	return number;
}


void SampleScene::DrawLines()
{
	//Draw horizontal lines
	Debug::DrawLine(0, HorizontalLane, width, HorizontalLane, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 2, width, HorizontalLane * 2, sf::Color::Red);
	//Draw vertical lines
	Debug::DrawLine(VerticalLane, 0, VerticalLane, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 2, 0, VerticalLane * 2, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 3, 0, VerticalLane * 3, height, sf::Color::Green);
}