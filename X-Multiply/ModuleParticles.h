#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 300

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	iPoint position;

public:
	//player particles
	Particle shot;
	Particle shot_impact;
	Particle player_death;
	Particle bomb;
	Particle bomb_explosion;

	//enemy particles
	Particle enemy_shot;
	Particle explosion_enemy;
	Particle anemona_shot1; 
	Particle anemona_shot2;
	Particle anemona_shot3;
	Particle anemona_shot4;
	Particle anemona_shot5;
	Particle anemona_shotud1;
	Particle anemona_shotud2;
	Particle anemona_shotud3;
	Particle anemona_shotud4;
	Particle anemona_shotud5;

};

#endif // __MODULEPARTICLES_H__