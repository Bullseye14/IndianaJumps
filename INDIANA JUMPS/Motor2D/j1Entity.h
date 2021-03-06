#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "j1EntityManager.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "p2Log.h"
#include "j1App.h"

struct Collider;
struct Animation;
struct SDL_Texture;
enum ENTITY_TYPES;

class j1Entity
{
public:
	j1Entity(int x, int y, ENTITY_TYPES type);
	~j1Entity();

	bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool PreUpdate();
	virtual bool CleanUp();
public:
	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };
	
	virtual void OnCollision(Collider* c1, Collider* c2) {};
	virtual void CheckCollision();

	SDL_Texture* graphics = nullptr;

	ENTITY_TYPES type;
	fPoint position;
	fPoint initialPosition;
	fPoint speed;
	Animation* animation = nullptr;
	Collider* playerHitbox = nullptr;

	p2DynArray<iPoint> path;
	
};
#endif // __ENTITY_H__ 
