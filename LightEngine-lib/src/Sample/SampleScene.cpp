#include "SampleScene.h"

#include "Snake.h"
#include "Apple.h"

#include "Debug.h"

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
			snake[x]->OldPosition = snake[x]->GetPosition();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::D)
				{
					snake[x]->SetState(Snake::State::Right);
					//ChangeDirection();
				}

				else if (event.key.code == sf::Keyboard::S)
				{
					snake[x]->SetState(Snake::State::Down);
					//ChangeDirection();
				}

				else if (event.key.code == sf::Keyboard::Q)
				{
					snake[x]->SetState(Snake::State::Left);
					//ChangeDirection();
				}

				else if (event.key.code == sf::Keyboard::Z)
				{
					snake[x]->SetState(Snake::State::Up);
					//ChangeDirection();
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
		if (snake[0]->IsColliding(apple))
		{
			apple->Destroy();
			IncrementSize();
			SpawnApple();
			snake[0]->SetState(Snake::State::Idle);
			snake[0]->SetDirection(0, 0, 0);
		}

		for(int x = 1; x<snake.size(); x++)
		{
			if (snake[x-1]->OldPosition != snake[x-1]->GetPosition())
				ChangeDirection(x);
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
	}

}

void SampleScene::IncrementSize()
{
	sizeSnake = CreateEntity<Snake>(30, sf::Color::Blue);
	switch (snake[0]->GetState())
	{
	case Snake::State::Up:
		sizeSnake->SetPosition(snake[0]->GetPosition().x, snake[0]->GetPosition().y + sizeSnake->GetRadius() / 2);
		break;

	case Snake::State::Right:
		sizeSnake->SetPosition(snake[0]->GetPosition().x - sizeSnake->GetRadius() / 2, snake[0]->GetPosition().y);
		break;

	case Snake::State::Down:
		sizeSnake->SetPosition(snake[0]->GetPosition().x, snake[0]->GetPosition().y - sizeSnake->GetRadius() / 2);
		break;

	case Snake::Snake::State::Left:
		sizeSnake->SetPosition(snake[0]->GetPosition().x + sizeSnake->GetRadius() / 2, snake[0]->GetPosition().y);
		break;
	}
	snake.push_back(sizeSnake);
}

void SampleScene::SpawnApple()
{
	apple = CreateEntity<Apple>(20, sf::Color::Red);
	apple->SetPosition(VerticalLane * PickNumber(1, 7), HorizontalLane * PickNumber(1, 7));
}

void SampleScene::ChangeDirection(int x)
{
	snake[x]->SetPosition(snake[x-1]->OldPosition.x, snake[x - 1]->OldPosition.y);
	/*switch (snake[x - 1]->GetState())
	{
	case Snake::State::Up:
		snake[x]->SetPosition(snake[x - 1]->GetPosition().x, snake[x - 1]->GetPosition().y + sizeSnake->GetRadius() / 2);
		break;

	case Snake::State::Right:
		snake[x]->SetPosition(snake[x - 1]->GetPosition().x - sizeSnake->GetRadius() / 2, snake[x - 1]->GetPosition().y);
		break;

	case Snake::State::Down:
		snake[x]->SetPosition(snake[x - 1]->GetPosition().x, snake[x - 1]->GetPosition().y - sizeSnake->GetRadius() / 2);
		break;

	case Snake::Snake::State::Left:
		snake[x]->SetPosition(snake[x - 1]->GetPosition().x + sizeSnake->GetRadius() / 2, snake[x - 1]->GetPosition().y);
		break;
	}*/
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