#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*) override;

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation upward;
	Animation downward;
	iPoint position;
	uint shot;

	struct Collider* playerHitBox;
};

#endif