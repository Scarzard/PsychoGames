#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleAudio.h"



ModuleLevel1::ModuleLevel1()
{
	// tilemap
	ground.x = 0;
	ground.y = 1;
	ground.w = 4961;
	ground.h = 513;

	// Background 
	background.x = 0;
	background.y = 0;
	background.w = 4961;
	background.h = 512;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading level 1 scene");
	
	backround = App->textures->Load("image/background completed.png");
	tilemap1 = App->textures->Load("image/LV1_TilemapCompleted.png");

	App->audio->MusicPlay("Sound/04_Into_the_Human_Body_Stage_1_.ogg", 0.5f);
	
	App->player->Enable();
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1 scene");
	App->player->Disable();
	App->textures->Unload(backround);
	App->textures->Unload(tilemap1);
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	/*int speed_backround = 4;
	int speed_tilemap = 5;

	if (background_w < 4961) {
		background_w -= speed_backround;
	}
	if (tilemap_w < 4961) {
		tilemap_w -= speed_tilemap;
	}*/

	// Move camera forward -----------------------------
	int scroll_speed = 1;

	App->player->position.x += 1;
	App->render->camera.x -= 3;

	// Draw everything --------------------------------------
	App->render->Blit(backround, (background_w) / 3.5, 0, &background, 0.75f); // backround
	App->render->Blit(tilemap1, (tilemap_w) / 3.5, 0, &ground, 0.75f); //tilemap
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{
		App->fade->FadeToBlack(this, App->lvl2, 1);
		App->player->position.x = 100;
		App->player->position.y = 30;
	}
	return UPDATE_CONTINUE;
}