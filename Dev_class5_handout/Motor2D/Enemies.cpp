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
#include "j1Input.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )



Enemies::Enemies() : j1Module()
{

	idle_right_enemy.PushBack({ 1,1,100,100 });
	idle_right_enemy.PushBack({ 21,39,20,35 });
	idle_right_enemy.PushBack({ 42,39,20,35 });
	idle_right_enemy.speed = 0.05f;

	idle_left_enemy.PushBack({ 1,157,20,35 });
	idle_left_enemy.PushBack({ 21,157,20,35 });
	idle_left_enemy.PushBack({ 42,157,20,35 });
	idle_left_enemy.speed = 0.05f;

	walk_right_enemy.PushBack({ 1,1,22,33 });
	walk_right_enemy.PushBack({ 23,1,19,33 });
	walk_right_enemy.PushBack({ 43,1,16,33 });
	walk_right_enemy.speed = 0.05f;

	walk_left_enemy.PushBack({ 1,118,22,33 });
	walk_left_enemy.PushBack({ 23,118,19,33 });
	walk_left_enemy.PushBack({ 43,118,16,33 });
	walk_left_enemy.speed = 0.05f;


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

	STATEENEMY state_Enemy = IDLE_RIGHT_ENEMY;

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
	currentTime = SDL_GetTicks();

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		SavePosition();
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		LoadPosition();
		enemy_load = true;
		STATEENEMY state_Enemy = IDLE_RIGHT_ENEMY;
		touching_floor = false;
		speed.y = 0;
		speed.x = 0;

	}


	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		enemie_position.x = starting_x.as_float();
		enemie_position.y = starting_y.as_float();
		enemy_load = true;
		STATEENEMY state_Enemy = IDLE_RIGHT_ENEMY;
		touching_floor = false;
		speed.y = 0;
		speed.x = 0;
	}

	if (touching_floor == false) {
		speed.y += GRAVITY;
	}

	else// if (playerpos.y >= 400) 
	{
		speed.y = 0;
		onGround = true;
	}

	enemie_position.x += speed.x;
	enemie_position.y += speed.y;
	speed.x = 0;
	enemie_collider->SetPos(enemie_position.x, enemie_position.y);
	Draw();

	return true;
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
	switch (state_Enemy)
	{
	case IDLE_RIGHT:
		current_animation = &idle_right_enemy;
		break;

	case IDLE_LEFT:
		current_animation = &idle_left_enemy;
		break;

	case WALK_RIGHT:
		current_animation = &walk_right_enemy;
		break;

	case WALK_LEFT:
		current_animation = &walk_left_enemy;
		break;



	}




	SDL_Rect render = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, enemie_position.x, enemie_position.y, &render);

	if (last_state_Enemy != last_state_2_Enemy)
		last_state_2_Enemy = last_state_Enemy;

	if (last_state_Enemy != state_Enemy)
		last_state_Enemy = state_Enemy;
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


void Enemies::OnCollision(Collider* e1, Collider* e2) {

	if (e2->type == COLLIDER_FLOOR)
	{


		if (e1->rect.y < e2->rect.y + e2->rect.h && e1->rect.y + 3 > e2->rect.y + e2->rect.h)

		{
			enemie_position.y = enemie_position.y + 1;
			speed.y = GRAVITY;



		}
		else if (e1->rect.y + e1->rect.h > e2->rect.y && e1->rect.y + e1->rect.h - 3 < e2->rect.y)

		{

			touching_floor = true;
			if ((e1->rect.x + 5 >= e2->rect.x + e2->rect.w && e1->rect.x - 5 <= e2->rect.x + e2->rect.w)
				|| (e1->rect.x + e1->rect.w - 5 <= e2->rect.x && e1->rect.x + e1->rect.w + 5 >= e2->rect.x)) {
				touching_floor = false;

			}

		}


		else if (e1->rect.x + e1->rect.w > e2->rect.x && e1->rect.x + e1->rect.w - 3 < e2->rect.x)
		{
			enemie_position.x = enemie_position.x - 1;

		}
		else if (e1->rect.x < e2->rect.x + e2->rect.w && e1->rect.x + 3 > e2->rect.x + e2->rect.w)
		{
			enemie_position.x = enemie_position.x + 1;

		}
	}
}