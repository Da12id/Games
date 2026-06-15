#pragma once
#include "Entity.h"
class Projectile : public Entity
{
	void OnInitialize() override;
	void OnUpdate() override;
};

