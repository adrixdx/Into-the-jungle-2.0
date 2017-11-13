#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");

	save_file.load_file("save_game.xml");
	renderernode = save_file.child("game_state").child("renderer");
	camera_x = renderernode.attribute("x");
	camera_y = renderernode.attribute("y");

	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("jungle_1.tmx");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	

	/*if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		LOG("%f", App->player->playerpos.x);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		LOG("%d", App->render->camera.x);*/

	

	if (App->player->playerpos.x > 500 && App->player->playerpos.x < 1075) {
		App->render->camera.x = -(App->player->playerpos.x-500);
		
	}
	if (App->player->player_died) {
	
		reset = P_DIE;
		resetCamera(reset);
	}

	if (App->player->player_load) {
		reset = P_LOAD;
		resetCamera(reset);
	}

	App->map->Draw();

	
	iPoint mousexy;
	App->input->GetMousePosition(mousexy.x, mousexy.y);
	mousexy = App->map->MapToWorld(mousexy.x, mousexy.y);
	p2SString title("Into the Jungle");

	App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


bool j1Scene::resetCamera(CamReset reset) {
	bool ret = true;
	
	if (reset == P_DIE) {
		App->render->camera.x = -(App->player->playerpos.x - 30);
		App->player->player_died = false;
		reset = NOTHING;
	}
	else if (reset == P_LOAD) {
		if (App->player->playerpos.x > 500 && App->player->playerpos.x < 1075) {

			App->render->camera.x = -(App->player->position_attr_x.as_int() - 500);
		}
		else if (App->player->playerpos.x <= 500) {
			App->render->camera.x = 0;
		}
		else if (App->player->playerpos.x >= 1075) {
			App->render->camera.x = -574;
		}
		App->player->player_load = false;
		reset = NOTHING;
	}

	return ret;
}