#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include	"PugiXml/src/pugixml.hpp"
#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"Animation.h"
#include	"j1Player.h"

#define GRAVITY 0.02f 
#define SPEED_X 1.0f
#define SPEED_Y 0.5f


enum STATEENEMY {
	IDLE_RIGHT_ENEMY,
	IDLE_LEFT_ENEMY,
	WALK_RIGHT_ENEMY,
	WALK_LEFT_ENEMY,
	NO_STATE_ENEMY,
};

class Enemies :public j1Module
{
public:
	Enemies();
	~Enemies();

	bool Start();
	bool CleanUp();
	bool Awake(pugi::xml_node& config);
	bool Update();
	bool PostUpdate();
	bool Load(pugi::xml_node&);
	void LoadPosition();
	void SavePosition();

	void Draw();
	void OnCollision(Collider* c1, Collider* c2);
private:

	uint width = 0;
	uint height = 0;
	SDL_Texture* graphics = nullptr;
	fPoint speed;
	STATEENEMY state_Enemy = NO_STATE_ENEMY;
	Animation* current_animation = nullptr;

	STATEENEMY last_state_Enemy = NO_STATE_ENEMY;
	STATEENEMY last_state_2_Enemy = NO_STATE_ENEMY;
	Animation idle_right_enemy;
	Animation walk_right_enemy;
	Animation idle_left_enemy;
	Animation walk_left_enemy;

	

	uint lastTime = 0;
	bool onGround = true;



	pugi::xml_attribute starting_x;
	pugi::xml_attribute starting_y;
	pugi::xml_node positionnode;
	pugi::xml_document save_file;

	uint jumpfx;
public:


	fPoint enemie_position;
	Collider* enemie_collider;
	bool touching_floor = false;
	uint currentTime = 0;
	bool enemy_load = false;

	pugi::xml_attribute position_attr_x;
	pugi::xml_attribute position_attr_y;

};



#endif
