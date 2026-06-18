
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SampleScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "Snake", 60, sf::Color(55,0,55));
	
	pInstance->LaunchScene<SampleScene>();

	return 0;
}