#include "p2Defs.h"
#include "p2Log.h"
#include "j1Player.h"
#include "p2List.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Map.h"
//#include "SDL\include\SDL_timer.h"
#include "j1Collision.h"
#include "j1Audio.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )



j1Player::j1Player() : j1Module()
{

	idle_right.PushBack({ 1,39,20,35 });	
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
	ledge_left.loop = false;	

}




j1Player::~j1Player()
{
	
}


bool j1Player::Awake(pugi::xml_node& config)
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

bool j1Player::Start()
{

	
	LOG("starting player");
	bool ret = true;
	graphics = App->tex->Load("maps/PlayerSprites.png");
	jumpfx = App->audio->LoadFx("audio/fx/jump.wav");
	
	state = IDLE_RIGHT;
	
	playerpos.x = starting_x.as_float();
	playerpos.y = starting_y.as_float();
	speed.x = 0;
	
	speed.y = 0;
	playerCollider = App->collision->AddCollider({ (int)playerpos.x,(int)playerpos.y,20,35 }, COLLIDER_PLAYER, this);

	return ret;
}

bool j1Player::Update()
{

	
	return true;
}

bool j1Player::PostUpdate()
{
	currentTime = SDL_GetTicks();

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		SavePosition();
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		LoadPosition();
		player_load = true;
		state = IDLE_RIGHT;
		touching_floor = false;
		speed.y = 0;
		speed.x = 0;
		
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		playerpos.x = starting_x.as_float();
		playerpos.y = starting_y.as_float();
		player_load = true;
		state = IDLE_RIGHT;
		touching_floor = false;
		speed.y = 0;
		speed.x = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && in_ledge == false && ledge_jump_x_disabled == false)
	{

		speed.x = SPEED_X;
		if (jumping == false) {
			state = WALK_RIGHT;
		}
		else {
			state = JUMP_RIGHT;
		}
		playerdir = RIGHT;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP && in_ledge == false && ledge_jump_x_disabled == false)
	{
		if (jumping == false) {
			state = IDLE_RIGHT;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && in_ledge == false && ledge_jump_x_disabled == false)
	{
		speed.x = -SPEED_X;
		if (jumping == false) {
			state = WALK_LEFT;
		}
		else {
			state = JUMP_LEFT;
		}
		playerdir = LEFT;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP && in_ledge == false && ledge_jump_x_disabled == false)
	{
		if (jumping == false) {
			state = IDLE_LEFT;
		}

	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (playerdir == RIGHT)
			state = JUMP_RIGHT;
		else if (playerdir == LEFT)
			state = JUMP_LEFT;
		Jumping();
		speed.x = SPEED_X;
		if (in_ledge) {
			disable_ledge = SDL_GetTicks();
			ledge_disabled = true;
			ledge_jump_x_disabled = true;
			in_ledge = false;
			on_ledge_left = false;
			on_ledge_right = false;
		}
	}



	if (touching_floor == false && in_ledge == false) {
		speed.y += GRAVITY;

	}
	else// if (playerpos.y >= 400) 
	{

		speed.y = 0;
		onGround = true;
		
		//jump_right.Reset();
		//jump_left.Reset();
		jumping = false;
	}



	if (on_ledge_right) {
		
		state = LEDGE_RIGHT;
	}

	if (on_ledge_left){
		
		state = LEDGE_LEFT;
}
	
	if (currentTime > disable_ledge + 50 && disable_ledge != 0) {
		ledge_jump_x_disabled = false;
		ledge_disabled = false;
		LOG("jump x enabled & ledge ON");
		disable_ledge = 0;
		
	}
	playerpos.x += speed.x;
	playerpos.y += speed.y;
	speed.x = 0;
	playerCollider->SetPos(playerpos.x, playerpos.y);
	Draw();
	
	return true;
}

bool j1Player::Jumping() {
	bool ret = true;
	
	if (onGround)
	{
		jump_right.Reset();
		jump_left.Reset();
		jumping = true;
		speed.y = -2.0f;
		onGround = false;
		playerpos.y-=5;
		touching_floor = false;
		App->audio->PlayFx(jumpfx);
	}

	if (speed.y < -1.5f) {
		speed.y = -1.5f;
	}

	return ret;
}


bool j1Player::CleanUp()
{
	LOG("Destroying player");
	bool ret = true;
	return ret;
}


bool j1Player::Load(pugi::xml_node& node)
{
	bool ret = true;



	return ret;
}




void j1Player::Draw()
{
	switch (state)
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
	}else if (current_animation->Finished() && current_animation == &jump_left && touching_floor) {
		current_animation = &idle_left;
	}


	SDL_Rect render = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, playerpos.x, playerpos.y, &render);

	if(last_state!=last_state_2)
		last_state_2 = last_state;

	if(last_state!=state)
		last_state = state;
	//LOG("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");

	
}




void j1Player::LoadPosition() {


	playerpos.x = position_attr_x.as_int();
	playerpos.y = position_attr_y.as_int();

}


void j1Player::SavePosition() {
	position_attr_x.set_value(playerpos.x);
	position_attr_y.set_value(playerpos.y);
}


void j1Player::OnCollision(Collider* c1, Collider* c2) {

	if (c2->type == COLLIDER_FLOOR)
	{
		
		
		if (c1->rect.y < c2->rect.y + c2->rect.h && c1->rect.y + 3 > c2->rect.y + c2->rect.h)

		{
			playerpos.y = playerpos.y + 1;
			speed.y = GRAVITY;
			
			
			
		}
		else if (c1->rect.y + c1->rect.h > c2->rect.y && c1->rect.y + c1->rect.h - 3< c2->rect.y)

		{
			
			touching_floor = true;
			if ((c1->rect.x + 5 >= c2->rect.x + c2->rect.w && c1->rect.x - 5 <= c2->rect.x + c2->rect.w)
				|| (c1->rect.x + c1->rect.w - 5 <= c2->rect.x && c1->rect.x + c1->rect.w + 5 >= c2->rect.x)) {
				touching_floor = false;
				
			}
			
		}


		else if (c1->rect.x + c1->rect.w > c2->rect.x && c1->rect.x + c1->rect.w - 3 < c2->rect.x)
		{
			playerpos.x = playerpos.x - 1;

		}
		else if (c1->rect.x < c2->rect.x + c2->rect.w && c1->rect.x + 3 > c2->rect.x + c2->rect.w)
		{
			playerpos.x = playerpos.x + 1;

		}

	

	}
	if (c2->type == COLLIDER_DIE) 
	{
		playerpos.x = starting_x.as_float();
		playerpos.y = starting_y.as_float();
		speed.x = 0;
		speed.y = 0;
		player_died = true;

	}

	if (c2->type == COLLIDER_LEDGE && in_ledge==false && ledge_disabled == false)
	{


		//same as FLOOR until...
		if (c1->rect.y < c2->rect.y + c2->rect.h && c1->rect.y + 3 > c2->rect.y + c2->rect.h)

		{
			playerpos.y = playerpos.y + 1;
			speed.y = GRAVITY;

			

		}
		else if (c1->rect.y + c1->rect.h > c2->rect.y && c1->rect.y + c1->rect.h - 3< c2->rect.y)

		{
			

			touching_floor = true;
			if ((c1->rect.x + 5 >= c2->rect.x + c2->rect.w && c1->rect.x - 5 <= c2->rect.x + c2->rect.w)
				|| (c1->rect.x + c1->rect.w - 5 <= c2->rect.x && c1->rect.x + c1->rect.w + 5 >= c2->rect.x)) {
				touching_floor = false;
				
			}
		
		}


		else if (c1->rect.x + c1->rect.w > c2->rect.x && c1->rect.x + c1->rect.w - 3 < c2->rect.x)
		{
			playerpos.x = playerpos.x - 1;

		}
		else if (c1->rect.x < c2->rect.x + c2->rect.w && c1->rect.x + 3 > c2->rect.x + c2->rect.w)
		{
			playerpos.x = playerpos.x + 1;

		}

		
		// here.
		//if player y is between ledge y and half of its height, then he will grab


		if (c2->rect.y < c1->rect.y && c1->rect.y - (c2->rect.h / 2) < c2->rect.y) {
			speed.x = 0;
			ledge_right.Reset();
			ledge_left.Reset();
		
			if (c1->rect.x < c2->rect.x) {
				state = LEDGE_RIGHT;
				on_ledge_right = true;
			}
			else {
				state = LEDGE_LEFT;
				on_ledge_left = true;
			}
			in_ledge = true;
		}
	

	}
}