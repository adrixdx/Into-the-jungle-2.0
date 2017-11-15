#include "p2Defs.h"
#include "p2Log.h"
#include "Enemies.h"
#include "p2List.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Audio.h"
#include "j1Player.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )



Enemies::Enemies() : j1Module()
{

	/*idle_right.PushBack({ 1,39,20,35 });
	idle_right.PushBack({ 21,39,20,35 });
	idle_right.PushBack({ 42,39,20,35 });
	idle_right.PushBack({ 63,39,20,35 });
	idle_right.PushBack({ 84,39,20,35 });
	idle_right.PushBack({ 105,39,20,35 });
	idle_right.PushBack({ 126,39,20,35 });
	idle_right.PushBack({ 147,39,20,35 });
	idle_right.PushBack({ 168,39,20,35 });
	idle_right.PushBack({ 189,39,20,35 });
	idle_right.PushBack({ 210,39,20,35 });
	idle_right.PushBack({ 231,39,20,35 });
	idle_right.speed = 0.05f;

	idle_left.PushBack({ 1,157,20,35 });
	idle_left.PushBack({ 21,157,20,35 });
	idle_left.PushBack({ 42,157,20,35 });
	idle_left.PushBack({ 63,157,20,35 });
	idle_left.PushBack({ 84,157,20,35 });
	idle_left.PushBack({ 105,157,20,35 });
	idle_left.PushBack({ 126,157,20,35 });
	idle_left.PushBack({ 147,157,20,35 });
	idle_left.PushBack({ 168,157,20,35 });
	idle_left.PushBack({ 189,157,20,35 });
	idle_left.PushBack({ 210,157,20,35 });
	idle_left.PushBack({ 231,157,20,35 });
	idle_left.speed = 0.05f;

	walk_right.PushBack({ 1,1,22,33 });
	walk_right.PushBack({ 23,1,19,33 });
	walk_right.PushBack({ 43,1,16,33 });
	walk_right.PushBack({ 60,1,20,33 });
	walk_right.PushBack({ 80,1,20,33 });
	walk_right.PushBack({ 100,1,19,33 });
	walk_right.PushBack({ 119,1,20,33 });
	walk_right.PushBack({ 139,1,23,33 });
	walk_right.speed = 0.05f;

	walk_left.PushBack({ 1,118,22,33 });
	walk_left.PushBack({ 23,118,19,33 });
	walk_left.PushBack({ 43,118,16,33 });
	walk_left.PushBack({ 60,118,20,33 });
	walk_left.PushBack({ 80,118,20,33 });
	walk_left.PushBack({ 100,118,19,33 });
	walk_left.PushBack({ 119,118,20,33 });
	walk_left.PushBack({ 139,118,23,33 });
	walk_left.speed = 0.05f;

	jump_right.PushBack({ 162,1,19,37 });
	jump_right.PushBack({ 203,1,19,37 });
	jump_right.PushBack({ 223,1,21,37 });
	jump_right.PushBack({ 182,1,21,37 });
	jump_right.speed = 0.05f;
	jump_right.loop = false;

	jump_left.PushBack({ 162,118,19,37 });
	jump_left.PushBack({ 203,118,19,37 });
	jump_left.PushBack({ 223,118,21,37 });
	jump_left.PushBack({ 182,118,21,37 });
	jump_left.speed = 0.05f;
	jump_left.loop = false;

	ledge_right.PushBack({ 1,76,21,41 });
	ledge_right.PushBack({ 22,76,20,41 });
	ledge_right.PushBack({ 42,76,19,41 });
	ledge_right.PushBack({ 61,76,20,41 });
	ledge_right.PushBack({ 81,76,20,41 });
	ledge_right.PushBack({ 101,76,20,41 });
	ledge_right.speed = 0.05f;
	ledge_right.loop = false;

	ledge_left.PushBack({ 1,194,21,41 });
	ledge_left.PushBack({ 22,194,20,41 });
	ledge_left.PushBack({ 42,194,19,41 });
	ledge_left.PushBack({ 61,194,20,41 });
	ledge_left.PushBack({ 81,194,20,41 });
	ledge_left.PushBack({ 101,194,20,41 });
	ledge_left.speed = 0.05f;
	ledge_left.loop = false;*/

}




Enemies::~Enemies()
{

}


bool Enemies::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");
	bool ret = true;

	save_file.load_file("save_game.xml");
	positionnode = save_file.child("game_state").child("position");
	position_attr_x = positionnode.child("position").attribute("x");
	position_attr_y = positionnode.child("position").attribute("y");
	starting_x = positionnode.child("start").attribute("x");
	starting_y = positionnode.child("start").attribute("y");





	return ret;
}

bool Enemies::Start()
{


	LOG("starting player");
	bool ret = true;
	graphics = App->tex->Load("maps/Enemy_Sprites.png");
	jumpfx = App->audio->LoadFx("audio/fx/jump.wav");

	state_Enemy = IDLE_RIGHT;

	enemie_position.x = starting_x.as_float();
	enemie_position.y = starting_y.as_float();
	speed.x = 0;

	speed.y = 0;
	enemie_collider = App->collision->AddCollider({ (int)enemie_position.x,(int)enemie_position.y,20,35 }, COLLIDER_ENEMIES, this);

	return ret;
}

bool Enemies::Update()
{


	return true;
}

bool Enemies::PostUpdate()
{
	

	return true;
}

bool Enemies::Jumping() {
	bool ret = true;

	if (onGround)
	{
		jump_right.Reset();
		jump_left.Reset();
		jumping = true;
		speed.y = -2.0f;
		onGround = false;
		enemie_position.y -= 5;
		touching_floor = false;
		App->audio->PlayFx(jumpfx);
	}

	if (speed.y < -1.5f) {
		speed.y = -1.5f;
	}

	return ret;
}


bool Enemies::CleanUp()
{
	LOG("Destroying enemies");
	bool ret = true;
	return ret;
}


bool Enemies::Load(pugi::xml_node& node)
{
	bool ret = true;



	return ret;
}




void Enemies::Draw()
{
	/*switch (state)
	{
	case IDLE_RIGHT:
		current_animation = &idle_right;
		break;

	case IDLE_LEFT:
		current_animation = &idle_left;
		break;

	case WALK_RIGHT:
		current_animation = &walk_right;
		break;

	case WALK_LEFT:
		current_animation = &walk_left;
		break;

	case JUMP_RIGHT:
		current_animation = &jump_right;
		break;

	case JUMP_LEFT:
		current_animation = &jump_left;
		break;
	case LEDGE_RIGHT:
		current_animation = &ledge_right;
		break;
	case LEDGE_LEFT:
		current_animation = &ledge_left;
		break;

	}


	//so jump animation doesnt get stuck if we just jump and not press anything else after
	if (current_animation->Finished() && current_animation == &jump_right && touching_floor) {
		current_animation = &idle_right;
	}
	else if (current_animation->Finished() && current_animation == &jump_left && touching_floor) {
		current_animation = &idle_left;
	}


	SDL_Rect render = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, playerpos.x, playerpos.y, &render);

	if (last_state != last_state_2)
		last_state_2 = last_state;

	if (last_state != state)
		last_state = state;
	//LOG("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");*/


}




void Enemies::LoadPosition() {


	enemie_position.x = position_attr_x.as_int();
	enemie_position.y = position_attr_y.as_int();

}


void Enemies::SavePosition() {
	position_attr_x.set_value(enemie_position.x);
	position_attr_y.set_value(enemie_position.y);
}


void Enemies::OnCollision(Collider* c1, Collider* c2) {

	
}