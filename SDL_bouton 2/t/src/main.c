#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <BTN_.h>

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS) != 0){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    TTF_Init();
    SDL_Event event;
    int quitter = 0;
    SDL_Window *wind = SDL_CreateWindow("new", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN);
    SDL_Renderer *rende = SDL_CreateRenderer(wind, 0, SDL_RENDERER_TARGETTEXTURE);
    BTN_Button *b = BTN_CreateButtonWithTexture(BTN_DYNAMIC_BUTTON_FORM_A, 120, 120, 1, 1, "DACF", "taile.ttf");
    BTN_CopyButton(b, rende);
    BTN_SetBackgroudImg(b, "fondIMG.jpg", wind);
    SDL_RenderPresent(rende);
    while(!quitter){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quitter = 1;
                break;
            case SDL_MOUSEMOTION:
                if(BTN_RenderMouseMotion(b, event, rende));
                break;
        }
        if(SDL_GetTicks() >= 10000)
            BTN_ChangeBackgroundColor(b, 200, 128, 100, 128, wind);
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
