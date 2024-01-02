#include "view.h"
#include "sdlView.h"

View sdlView_init(unsigned w, unsigned h)
{
	View view;
	view.typeView = SDL_VIEW;
	view.instanciation = createSdlView(w, h);
	Functions_View *f = (Functions_View *)malloc(sizeof(Functions_View));
	if (!f)
	{
		perror("malloc()\n");
		exit(EXIT_FAILURE);
	}
	view.functions = f;
	view.functions->updateView = sdlUpdateView;
	view.functions->destroyView = destroySdlView;
	view.functions->play_sound = play_sound;
	return view;
}
View ncursesView_init() {}