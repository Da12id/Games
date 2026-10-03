#include "SampleScene.h"

#include "Snake.h"
#include "Apple.h"

#include "Debug.h"
#include <iostream>

void SampleScene::OnInitialize()
{
	srand(time(nullptr));
	
	height = GetWindowHeight();
	width = GetWindowWidth();

	HorizontalLane = height / 8;
	VerticalLane = width / 8;

	sizeSnake = CreateEntity<Snake>(30, sf::Color::Blue);
	sizeSnake->SetPosition(500, 500);
	snake.push_back(sizeSnake);

	SpawnApple();
}

void SampleScene::OnEvent(const sf::Event& event)
{
	for(int x = 0; x<snake.size(); x++)
	{
		if (loose == false)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::D)
				{
					snake[x]->SetState(Snake::State::Right);
				}

				else if (event.key.code == sf::Keyboard::S)
				{
					snake[x]->SetState(Snake::State::Down);
				}

				else if (event.key.code == sf::Keyboard::Q)
				{
					snake[x]->SetState(Snake::State::Left);
				}

				else if (event.key.code == sf::Keyboard::Z)
				{
					snake[x]->SetState(Snake::State::Up);
				}
			}
		}
	}
}

void SampleScene::OnUpdate()
{
	//DrawLines();

	if(sizeSnake != nullptr)
	{
		for (int x = 0; x < snake.size(); x++)
		{
			snake[x]->OldPos = snake[x]->GetPosition();
			if(x == 0)
				MoveSnake(x);
			else
				ChangeDirection(x);
		}

		if (snake[0]->IsColliding(apple))
		{
			score++;
			std::cout << "tu a manger " << score << " pommes\n";
			apple->Destroy();
			IncrementSize();
			SpawnApple();
		}

		if (snake[0]->GetPosition().y <= 0)
		{
			sizeSnake->Destroy();
			sizeSnake = nullptr;
			loose = true;
		}

		if (snake[0]->GetPosition().y >= height)
		{
			sizeSnake->Destroy();
			sizeSnake = nullptr;
			loose = true;
		}

		if (snake[0]->GetPosition().x <= 0)
		{
			sizeSnake->Destroy();
			sizeSnake = nullptr;
			loose = true;
		}

		if (snake[0]->GetPosition().x >= width)
		{
			sizeSnake->Destroy();
			sizeSnake = nullptr;
			loose = true;
		}

		for(int x = 13; x<snake.size(); x++)
		{
			if(snake[0]->IsInside(snake[x]->GetPosition().x, snake[x]->GetPosition().y))
			{
				snake[x]->ToDestroy();
				sizeSnake->Destroy();
				sizeSnake = nullptr;
				loose = true;
				std::cout << "tu a perdue";
				break;
			}
		}

		if (loose == true)
		{
			for (int x = snake.size() - 1; x >= 0; x--)
			{
				snake[x]->Destroy();
				snake.erase(snake.begin());
			}
		}
	}
}

void SampleScene::IncrementSize()
{
	if(score == 13)
		sizeSnake = CreateEntity<Snake>(30, sf::Color::White);
	else
		sizeSnake = CreateEntity<Snake>(30, sf::Color::Blue);

	switch (snake[0]->GetState())
	{
	case Snake::State::Up:
		sizeSnake->SetPosition(snake[0]->GetPosition().x, snake[0]->GetPosition().y + sizeSnake->GetRadius() );
		break;

	case Snake::State::Right:
		sizeSnake->SetPosition(snake[0]->GetPosition().x - sizeSnake->GetRadius() , snake[0]->GetPosition().y);
		break;

	case Snake::State::Down:
		sizeSnake->SetPosition(snake[0]->GetPosition().x, snake[0]->GetPosition().y - sizeSnake->GetRadius() );
		break;

	case Snake::Snake::State::Left:
		sizeSnake->SetPosition(snake[0]->GetPosition().x + sizeSnake->GetRadius() , snake[0]->GetPosition().y);
		break;
	}
	snake.push_back(sizeSnake);
}

void SampleScene::SpawnApple()
{
	apple = CreateEntity<Apple>(20, sf::Color::Red);
	apple->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 7));
}

void SampleScene::MoveSnake(int x)
{
	switch (snake[x]->GetState())
	{
	case Snake::State::Up:
		snake[x]->SetDirection(0, -10, 60);
		break;

	case Snake::State::Right:
		snake[x]->SetDirection(10, 0, 60);
		break;

	case Snake::State::Down:
		snake[x]->SetDirection(0, 10, 60);
		break;

	case Snake::State::Left:
		snake[x]->SetDirection(-10, 0, 60);
		break;
	}
}

void SampleScene::ChangeDirection(int x)
{
	snake[x]->SetPosition(snake[x-1]->OldPos.x, snake[x - 1]->OldPos.y);
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
	Debug::DrawLine(0, HorizontalLane * 3, width, HorizontalLane * 3, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 4, width, HorizontalLane * 4, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 5, width, HorizontalLane * 5, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 6, width, HorizontalLane * 6, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 7, width, HorizontalLane * 7, sf::Color::Red);
	//Draw vertical lines
	Debug::DrawLine(VerticalLane, 0, VerticalLane, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 2, 0, VerticalLane * 2, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 3, 0, VerticalLane * 3, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 4, 0, VerticalLane * 4, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 5, 0, VerticalLane * 5, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 6, 0, VerticalLane * 6, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 7, 0, VerticalLane * 7, height, sf::Color::Green);
}