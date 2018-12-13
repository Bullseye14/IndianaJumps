#include "j1App.h"
#include "j1Gui.h"
#include "j1Button.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Window.h"
#include "j1MainMenu.h"
#include "j1Scene.h"
#include "Animation.h"

j1Button::j1Button(BUTTON_TYPE type)
{
	buttonRect = { 0,0,199,75 };
	buttonOnHover = { 0,75,199,75 };
	buttonOnClick = { 0,150,199,75 };

	b_type = type;
}

j1Button::~j1Button()
{
}

bool j1Button::Start() 
{
	App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &buttonRect);
	
	return true;
}

bool j1Button::PostUpdate() 
{
	bool ret = true;
	
	switch (mouse_state) 
	{
	case MOUSE_NONE:
		ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &buttonRect);
		break;

	case MOUSE_HOVER:
		//App->gui->mouse_hovering = true;
		ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &buttonOnHover);
		break;

	case MOUSE_CLICK:
		ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &buttonOnClick);
		if (b_type == PLAY) 
		{
			App->mainmenu->GoToScene();
			App->mainmenu->CleanUp();
		}
		else if (b_type == CONTINUE) 
		{
			App->mainmenu->GoToScene();
			App->LoadGame("save_game.xml");
			App->mainmenu->CleanUp();
		}
		else if (b_type == CREDITS)
		{
			ShellExecuteA(NULL, "open", "https://github.com/Bullseye14/Development-Pol-Xavi", NULL, NULL, SW_SHOWNORMAL);
		}
		else if (b_type == EXIT) 
		{
			App->mainmenu->ending = true;
		}
		break;

	}

	return ret;
}

bool j1Button::OnHover()
{
	int x, y;
	App->input->GetMousePosition(x, y);
	bool ret = position.x + App->render->camera.x / (int)App->win->GetScale() < x 
		&& position.y + App->render->camera.y < y && position.x + App->render->camera.x / (int)App->win->GetScale() + buttonRect.w > x 
		&& position.y + buttonRect.h > y;

	return ret;
}

bool j1Button::OnClick()
{
	bool ret = false;

	if (OnHover())
	{
		if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)
		{
			ret = true;
		}
	}

	return ret;
}