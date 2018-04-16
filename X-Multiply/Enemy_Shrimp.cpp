#include "Application.h"
#include "Enemy_Shrimp.h"
#include "ModuleCollision.h"


Enemy_Shrimp::Enemy_Shrimp(int x, int y) : Enemy(x, y)
{
	Width = 45;
	Height = 34;

	fly.PushBack({ 22, 20, Width, Height });
	//fly.PushBack({ 65, 17, Width, Height });
	//fly.PushBack({ 16, 71, Width, Height });
	fly.PushBack({ 72, 72, Width, Height });


	fly.speed = 0.03f;

	animation = &fly;

	collider = App->collision->AddCollider({ 22, 20, Width, Height }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Shrimp::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
}