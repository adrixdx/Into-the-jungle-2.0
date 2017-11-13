#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include <math.h>
#include "j1Collision.h"
#include "j1Audio.h"

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

bool j1Map::Start() {
	bool ret = true;

	App->audio->PlayMusic("audio/music/TheJungleFloor.ogg");

	Collider* mapcollider3 = App->collision->AddCollider({ 192,292,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider4 = App->collision->AddCollider({ 256,240,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider6 = App->collision->AddCollider({ 288,208,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider8 = App->collision->AddCollider({ 352,208,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider9 = App->collision->AddCollider({ 400,224,32,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider11 = App->collision->AddCollider({ 464,224,32,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider13 = App->collision->AddCollider({ 432,272,32,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider15 = App->collision->AddCollider({ 528,224,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider17 = App->collision->AddCollider({ 592,192,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider19 = App->collision->AddCollider({ 624,160,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider21 = App->collision->AddCollider({ 704,160,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider22 = App->collision->AddCollider({ 736,384,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider24 = App->collision->AddCollider({ 784,384,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider25 = App->collision->AddCollider({ 784,416,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider26 = App->collision->AddCollider({ 880,416,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider29 = App->collision->AddCollider({ 880,384,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider34 = App->collision->AddCollider({ 928,384,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider31 = App->collision->AddCollider({ 928,416,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider32 = App->collision->AddCollider({ 1024,416,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider33 = App->collision->AddCollider({ 1024,384,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider39 = App->collision->AddCollider({ 1520,208,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider40 = App->collision->AddCollider({ 1456,224,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider41 = App->collision->AddCollider({ 1392,240,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider42 = App->collision->AddCollider({ 1328,256,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider43 = App->collision->AddCollider({ 1264,272,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider44 = App->collision->AddCollider({ 1184,272,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider45 = App->collision->AddCollider({ 1136,320,16,16 }, COLLIDER_LEDGE, this);
	Collider* mapcollider46 = App->collision->AddCollider({ 1088,368,16,16 }, COLLIDER_LEDGE, this);

	Collider* mapcollider = App->collision->AddCollider({ 0,0,1600,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider1 = App->collision->AddCollider({ 0,292,192,192 }, COLLIDER_FLOOR, this);
	Collider* mapcollider2 = App->collision->AddCollider({ 192,292,16,192 }, COLLIDER_FLOOR, this);
	Collider* mapcollider5 = App->collision->AddCollider({ 256,240,112,240 }, COLLIDER_FLOOR, this);
	Collider* mapcollider7 = App->collision->AddCollider({ 288,208,80,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider10 = App->collision->AddCollider({ 400,224,32,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider12 = App->collision->AddCollider({ 464,224,32,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider14 = App->collision->AddCollider({ 432,272,32,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider16 = App->collision->AddCollider({ 528,224,192,256 }, COLLIDER_FLOOR, this);
	Collider* mapcollider18 = App->collision->AddCollider({ 592,192,128,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider20 = App->collision->AddCollider({ 624,160,96,32 }, COLLIDER_FLOOR, this);
	Collider* mapcollider23 = App->collision->AddCollider({ 720,384,32,96 }, COLLIDER_FLOOR, this);
	Collider* mapcollider27 = App->collision->AddCollider({ 784,384,112,16 }, COLLIDER_FLOOR, this);
	Collider* mapcollider28 = App->collision->AddCollider({ 784,416,112,16 }, COLLIDER_FLOOR, this);
	Collider* mapcollider30 = App->collision->AddCollider({ 816,400,48,16 }, COLLIDER_FLOOR, this);
	Collider* mapcollider35 = App->collision->AddCollider({ 928,384,112,16 }, COLLIDER_FLOOR, this);
	Collider* mapcollider36 = App->collision->AddCollider({ 928,416,112,16 }, COLLIDER_FLOOR, this);
	Collider* mapcollider37 = App->collision->AddCollider({ 960,400,48,16 }, COLLIDER_FLOOR, this);
	Collider* mapcollider38 = App->collision->AddCollider({ 1520,208,80,272 }, COLLIDER_FLOOR, this);
	Collider* mapcollider47 = App->collision->AddCollider({ 1184,272,96,208 }, COLLIDER_FLOOR, this);
	Collider* mapcollider48 = App->collision->AddCollider({ 1136,320,48,160 }, COLLIDER_FLOOR, this);
	Collider* mapcollider49 = App->collision->AddCollider({ 1088,368,48,112 }, COLLIDER_FLOOR, this);
	Collider* mapcollider50 = App->collision->AddCollider({ 0,500,3000,300 }, COLLIDER_DIE, this);
	Collider* mapcollider51 = App->collision->AddCollider({ -20,0,23,1000 }, COLLIDER_FLOOR, this);
	Collider* mapcollider52 = App->collision->AddCollider({ 1600,0,23,1000 }, COLLIDER_FLOOR, this);
	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	
	p2List_item<TileSet*>* draw_tilesets = data.tilesets.start;
	p2List_item<MapLayer*>* draw_layers = data.layers.start;

	while (draw_tilesets != NULL)
	{
		while (draw_layers != NULL) {

			for (int i = 0; i < draw_layers->data->width; i++) {
				for (int j = 0; j < draw_layers->data->height; j++) {

					iPoint pos = MapToWorld(i, j);

					if (draw_layers->data->GetGid(i, j) != 0) {

						SDL_Rect rect = draw_tilesets->data->GetTileRect(draw_layers->data->GetGid(i, j));
						SDL_Rect* section = &rect;

						

						App->render->Blit(draw_tilesets->data->texture, pos.x, pos.y, &rect);
					}
				}
			}
			draw_layers = draw_layers->next;
		}
		draw_tilesets = draw_tilesets->next;
	}
		

}


iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * data.tile_width;
	ret.y = y * data.tile_height;

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret;

	ret.x = x / data.tile_width;
	ret.y = y / data.tile_height;

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	
	// Remove all layers
	p2List_item<MapLayer*>* item1;
	item1 = data.layers.start;

	while (item1 != NULL) {
		RELEASE(item1->data);
		item1 = item1->next;
	}
	data.layers.clear();


	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	
	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* yer = new MapLayer();

		if (ret == true)
		{
			ret = LoadLayer(layer, yer);
		}

		data.layers.add(yer);
	}

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		
		
		p2List_item<MapLayer*>* item_layer = data.layers.start;
		while(item_layer != NULL)
		{
			MapLayer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_uint();
	layer->height = node.attribute("height").as_uint();

	layer->gid = new uint[layer->width * layer->height];
	memset(layer->gid, 0, layer->width * layer->height);

	int i = 0;

	for (pugi::xml_node Iterator = node.child("data").child("tile"); Iterator; Iterator = Iterator.next_sibling("tile"))
	{
		layer->gid[i] = Iterator.attribute("gid").as_uint();
		i++;
	}

	return ret;
}



