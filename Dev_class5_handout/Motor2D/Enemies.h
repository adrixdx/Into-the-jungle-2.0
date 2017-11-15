#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"Animation.h"
#include	"j1Player.h"

#define GRAVITY 0.02f 
#define SPEED_X 1.0f
#define SPEED_Y 0.5f


enum STATE {
	IDLE_RIGHT,
	IDLE_LEFT,
	WALK_RIGHT,
	WALK_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT,
	NO_STATE,
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
	bool Jumping();
	void OnCollision(Collider* c1, Collider* c2);
private:

	uint width = 0;
	uint height = 0;
	SDL_Texture* graphics = nullptr;
	fPoint speed;
	STATE state_Enemy = NO_STATE;
	Animation* current_animation = nullptr;

	STATE last_state_Enemy = NO_STATE;
	STATE last_state_2_Enemy = NO_STATE;
	Animation idle_right;
	Animation walk_right;
	Animation jump_right;
	Animation idle_left;
	Animation walk_left;
	Animation jump_left;
	

	uint lastTime = 0;
	bool jumping = false;
	bool onGround = true;



	pugi::xml_attribute starting_x;
	pugi::xml_attribute starting_y;
	pugi::xml_node positionnode;
	pugi::xml_document save_file;

	bool on_ledge_right = false;
	bool on_ledge_left = false;
	uint jumpfx;
public:


	fPoint enemie_position;
	Collider* enemie_collider;
	bool touching_floor = false;
	uint currentTime = 0;

	pugi::xml_attribute position_attr_x;
	pugi::xml_attribute position_attr_y;

};



#endif
