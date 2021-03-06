#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "ModuleLevel1.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleLevel1::ModuleLevel1()
{
	// tilemap
	ground_parallax.x = 0;
	ground_parallax.y = 1;
	ground_parallax.w = 4961;
	ground_parallax.h = 587;

	// Background 
	background_parallax.x = 0;
	background_parallax.y = 0;
	background_parallax.w = 4961;
	background_parallax.h = 587;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading space scene");

	background = App->textures->Load("image/background completed.png");
	tilemap1 = App->textures->Load("image/LV1_TilemapCompleted.png");
	hud = App->textures->Load("image/xmultiply_hud.png");

	App->audio->MusicPlay("Sound/04_Into_the_Human_Body_Stage_1_.ogg", 0.5f);

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->powerup->Enable();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//HUD hitbox
	HUDhitbox = App->collision->AddCollider({ 0, 0, SCREEN_WIDTH, 3 }, COLLIDER_HUD, this);

	//--------- TOP LARGER WALL --------- 
	App->collision->AddCollider({ 495, 0, 2025, 14 }, COLLIDER_WALL); //square of all the top wall 

	//--------- BOTTOM LARGER WALL --------- 
	App->collision->AddCollider({ 0, 242, 2549, 15 }, COLLIDER_WALL);

	//--------- TOP OBSTACLES --------- 
	App->collision->AddCollider({ 640, 14, 70, 14 }, COLLIDER_WALL); //1st 

	App->collision->AddCollider({ 761, 14, 57, 16 }, COLLIDER_WALL); //2nd 1
	App->collision->AddCollider({ 770, 30, 30, 18 }, COLLIDER_WALL); //2nd 2

	App->collision->AddCollider({ 1010, 14, 75, 29 }, COLLIDER_WALL); //3rd 1
	App->collision->AddCollider({ 1085, 14, 20, 15 }, COLLIDER_WALL); //3rd 2

	App->collision->AddCollider({ 1153, 14, 70, 14 }, COLLIDER_WALL); //4th 

	App->collision->AddCollider({ 1665, 14, 70, 14 }, COLLIDER_WALL); //After first entrance top

	App->collision->AddCollider({ 2425, 14, 57, 16 }, COLLIDER_WALL); //After biggest entrance 1 top
	App->collision->AddCollider({ 2430, 30, 30, 18 }, COLLIDER_WALL); //After biggest entrance 2 top

	//--------- BOTTOM OBSTACLES --------- 
	App->collision->AddCollider({ 414, 210, 30, 16 }, COLLIDER_WALL); //1st 1
	App->collision->AddCollider({ 408, 226, 57, 16 }, COLLIDER_WALL); //1st 2

	App->collision->AddCollider({ 497, 215, 75, 27 }, COLLIDER_WALL); //2nd 1
	App->collision->AddCollider({ 572, 227, 20, 15 }, COLLIDER_WALL); //2nd 2

	App->collision->AddCollider({ 1024, 230, 70, 12 }, COLLIDER_WALL); //3rd

	App->collision->AddCollider({ 1263, 215, 104, 27 }, COLLIDER_WALL); //4th

	App->collision->AddCollider({ 1790, 210, 30, 16 }, COLLIDER_WALL); //After first entrance 1 bottom 
	App->collision->AddCollider({ 1784, 226, 57, 16 }, COLLIDER_WALL); //After first entrance 2 bottom

	App->collision->AddCollider({ 2548, 219, 318, 38 }, COLLIDER_WALL); //Just before scroll

	//-------- First Entrance TOP --------- 
	App->collision->AddCollider({ 1551, 14, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 1545, 63, 15, 15 }, COLLIDER_WALL); //small square 2
	App->collision->AddCollider({ 1423, 14, 128, 27 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 1435, 41, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1446, 56, 100, 15 }, COLLIDER_WALL); // squares are organized from top to bottom
	App->collision->AddCollider({ 1455, 71, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1460, 86, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1475, 101, 65, 8 }, COLLIDER_WALL); //bottom square 

	//--------- First Entrance BOTTOM --------- 
	App->collision->AddCollider({ 1475, 147, 65, 8 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 1460, 155, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1455, 170, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1446, 185, 100, 15 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 1435, 200, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1423, 215, 128, 27 }, COLLIDER_WALL); //bottom square
	App->collision->AddCollider({ 1551, 228, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 1545, 176, 15, 15 }, COLLIDER_WALL); //small square 2

	//--------- Second Entrance TOP (biggest one) --------- 
	App->collision->AddCollider({ 2009, 14, 190, 28 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 2025, 42, 175, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 57, 140, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 72, 115, 10 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 2015, 82, 135, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2009, 92, 87, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2129, 92, 10, 17 }, COLLIDER_WALL); //bottom square
	App->collision->AddCollider({ 2199, 14, 13, 35 }, COLLIDER_WALL); //smalles square 1
	App->collision->AddCollider({ 2212, 14, 57, 8 }, COLLIDER_WALL); //smallest square 2

	//--------- Second Entrance BOTTOM (biggest one) --------- 
	App->collision->AddCollider({ 2129, 147, 10, 17 }, COLLIDER_WALL); // top square
	App->collision->AddCollider({ 2009, 147, 87, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2015, 164, 135, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2040, 174, 115, 10 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 2040, 184, 140, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2025, 199, 175, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2009, 214, 190, 28 }, COLLIDER_WALL); //bottom square 
	App->collision->AddCollider({ 2199, 207, 13, 35 }, COLLIDER_WALL); //smallest square 1 
	App->collision->AddCollider({ 2212, 234, 57, 8 }, COLLIDER_WALL); //smallest square 2

	//--------- TOP SCROLL --------- 
	App->collision->AddCollider({ 2917, 0, 122, 43 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2997, 43, 48, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3045, 43, 200, 33 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3065, 76, 60, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3125, 76, 100, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3170, 106, 100, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3230, 119, 60, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3260, 134, 30, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3291, 130, 100, 33 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3310, 163, 60, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3322, 189, 75, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3397, 163, 90, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3450, 217, 200, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3505, 237, 140, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3600, 255, 50, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3630, 265, 50, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3650, 280, 50, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3675, 290, 50, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3705, 300, 20, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3730, 305, 235, 55 }, COLLIDER_WALL);

	//--------- BOTTOM SCROLL --------- 
	App->collision->AddCollider({ 2715, 194, 50, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2805, 209, 36, 10 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2866, 265, 20, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2886, 295, 60, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2946, 307, 18, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2964, 319, 18, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2982, 331, 100, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3082, 343, 10, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3092, 350, 50, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3142, 362, 12, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3154, 374, 55, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3209, 384, 15, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3224, 395, 50, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3258, 386, 10, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3268, 396, 10, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3278, 410, 10, 53 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3288, 434, 40, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3328, 440, 10, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3338, 450, 10, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3348, 456, 20, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3368, 462, 30, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3398, 469, 30, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3428, 480, 40, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3468, 500, 60, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3508, 494, 15, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3528, 515, 25, 50 }, COLLIDER_WALL);

	App->collision->AddCollider({ 3552, 536, 121, 20 }, COLLIDER_WALL);

	//--------- After Scroll TOP --------- 
	App->collision->AddCollider({ 3800, 293, 1200, 12 }, COLLIDER_WALL); //square of all top

	App->collision->AddCollider({ 3750, 360, 150, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3830, 380, 45, 15 }, COLLIDER_WALL);

	App->collision->AddCollider({ 3970, 305, 70, 16 }, COLLIDER_WALL); //1st obstacle

	App->collision->AddCollider({ 4340, 305, 75, 30 }, COLLIDER_WALL); //2nd obstacle 1 
	App->collision->AddCollider({ 4415, 305, 20, 15 }, COLLIDER_WALL); //2nd obstacle 2

	//--------- After Scroll BOTTOM --------- 
	App->collision->AddCollider({ 3675, 537, 1300, 13 }, COLLIDER_WALL); //square of all bottom 

	App->collision->AddCollider({ 3955, 510, 75, 27 }, COLLIDER_WALL); //1st obstacle 1 
	App->collision->AddCollider({ 4030, 522, 20, 15 }, COLLIDER_WALL); //1st obstacle 2

	App->collision->AddCollider({ 4225, 525, 70, 12 }, COLLIDER_WALL); //2nd obstacle 

	App->collision->AddCollider({ 4353, 503, 27, 16 }, COLLIDER_WALL); //3rd obstacle 1
	App->collision->AddCollider({ 4345, 519, 57, 18 }, COLLIDER_WALL); //3rd obstacle 2

	App->collision->AddCollider({ 4870, 519, 65, 18 }, COLLIDER_WALL); //Before Boss 1 
	App->collision->AddCollider({ 4800, 525, 30, 12 }, COLLIDER_WALL); //Before Boss 2

	//--------- After Scroll ENTRANCE TOP --------- 
	App->collision->AddCollider({ 4623, 305, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 4617, 357, 15, 15 }, COLLIDER_WALL); //small square 2
	App->collision->AddCollider({ 4495, 305, 128, 31 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 4507, 336, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4518, 351, 100, 15 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 4527, 366, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4532, 381, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4547, 396, 65, 8 }, COLLIDER_WALL); //bottom square 

	//--------- After Scroll ENTRANCE BOTTOM --------- 
	App->collision->AddCollider({ 4542, 440, 65, 8 }, COLLIDER_WALL); //top square 
	App->collision->AddCollider({ 4532, 448, 85, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4527, 463, 90, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4518, 478, 100, 15 }, COLLIDER_WALL); //squares are organized from top to bottom
	App->collision->AddCollider({ 4507, 493, 110, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4495, 508, 128, 29 }, COLLIDER_WALL); //bottom square
	App->collision->AddCollider({ 4623, 521, 13, 13 }, COLLIDER_WALL); //small square 1
	App->collision->AddCollider({ 4617, 469, 15, 15 }, COLLIDER_WALL); //small square 2

	// Enemies ---
	
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 450, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 465, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 480, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 495, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 510, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 525, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 540, 60, false);
	//bottom
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 450, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 465, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 480, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 495, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 510, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 525, 60, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 540, 60, true);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 600, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 615, 80, false);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 720, 80, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 720, 120, false);
	
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 770, 90, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 785, 90, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 800, 90, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 815, 90, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 830, 90, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 845, 90, false);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 860, 90, false);
	
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 770, 90, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 785, 90, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 800, 90, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 815, 90, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 830, 90, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 845, 90, true);
	App->enemies->AddEnemy(ENEMY_TYPES::BALL, 860, 90, true);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 1160, 50, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 1200, 60, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 1200, 100, false);

	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 518, 175, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 863, 205, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 1294, 175, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2265, 205, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2301, 205, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2390, 205, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONE, 2461, 205, false);

	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONEUD, 1309, 11, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONEUD, 3125, 95, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONEUD, 3509, 240, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ANEMONEUD, 3649, 280, false);

	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3240, 170, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3240, 210, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3260, 220, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3260, 250, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3300, 150, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3400, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3460, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3460, 330, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3480, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3500, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3500, 330, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3520, 330, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3540, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3540, 330, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3560, 230, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3560, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3580, 230, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3580, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3600, 230, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3600, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3600, 310, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3620, 230, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3620, 270, false);
	App->enemies->AddEnemy(ENEMY_TYPES::SHRIMP, 3620, 310, false);

	//PowerUps
	App->powerup->AddPowerUp(POWERUP_TYPES::SPEED_UP, 750, 100);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_ENEMY, 750, 87);

	//Bomb
	App->powerup->AddPowerUp(POWERUP_TYPES::BOMB, 1000, 133);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_ENEMY, 1000, 120);

	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->textures->Unload(tilemap1);
	App->textures->Unload(hud);

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->powerup->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Move camera forward -----------------------------
	if (App->render->camera.x < 9150)
	{
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->player->position.x += 1; 
	}

	if (App->render->camera.x > 5300 && App->render->camera.x < 7064)
	{
		if (App->render->camera.x % 3 == 0)
		{
			App->render->camera.y += 1 * SCREEN_SIZE;
		}
	}

	HUDhitbox->SetPos((App->render->camera.x)/2 , App->render->camera.y + 257);

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, &background_parallax, 0.75f, true); // backround
	App->render->Blit(tilemap1, 0, 0, &ground_parallax, 1.0f, true);
	App->render->Blit(hud, 0, 257, NULL, 0.0f, false);

	return UPDATE_CONTINUE;
}