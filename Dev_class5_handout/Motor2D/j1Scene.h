#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
enum CamReset {
	P_DIE,
	P_LOAD,
	NOTHING,
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool resetCamera(CamReset);

private:
	CamReset reset = NOTHING;
	pugi::xml_document save_file;
	pugi::xml_node renderernode;
	pugi::xml_attribute camera_x;
	pugi::xml_attribute camera_y;

};

#endif // __j1SCENE_H__