#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "bouton.h"
#include "boutonEvenement.h"

void buttonMotion(SDL_Bouton bouton, SDL_Surface *ecran, SDL_Event event)
{
    SDL_Color noire = {0, 0, 0};

    if(event.motion.x >= bouton.surfacePosition.x && event.motion.y >= bouton.surfacePosition.y && event.motion.x <= bouton.surfacePosition.x + bouton.surface->w && event.motion.y <= bouton.surfacePosition.y + bouton.surface->h){
        SDL_FillRect(bouton.surface, NULL, bouton.fond);
        bouton.nameSurface = TTF_RenderText_Blended(bouton.effectFont, bouton.name, noire);
        {//On recentre le texte agrandi
            bouton.nameSurfacePosition.x = bouton.surface->w/2 - bouton.nameSurface->w/2;
            bouton.nameSurfacePosition.y = bouton.surface->h/2 - bouton.nameSurface->h/2;
        }
        SDL_BlitSurface(bouton.nameSurface, NULL, bouton.surface, &bouton.nameSurfacePosition);
        SDL_SetAlpha(bouton.effectSurface, SDL_SRCALPHA, bouton.nivo_transparence);
        SDL_BlitSurface(bouton.surface, NULL, ecran, &bouton.surfacePosition);
        SDL_BlitSurface(bouton.effectSurface, NULL, ecran, &bouton.surfacePosition);
        SDL_Flip(ecran);
    }
    else{
        SDL_FillRect(bouton.surface, NULL, bouton.fond);
        bouton.nameSurface = TTF_RenderText_Blended(bouton.nameFont, bouton.name, noire);
        SDL_BlitSurface(bouton.nameSurface, NULL, bouton.surface, &bouton.nameSurfacePosition);
        SDL_BlitSurface(bouton.surface, NULL, ecran, &bouton.surfacePosition);
        SDL_Flip(ecran);
    }
}

void bouton_Appui(SDL_Bouton bouton, SDL_Surface *ecran, SDL_Event event)
{
    SDL_Color noire = {0, 0, 0};

    if(event.button.x >= bouton.surfacePosition.x && event.button.y >= bouton.surfacePosition.y && event.button.x <= bouton.surfacePosition.x + bouton.surface->w && event.button.y <= bouton.surfacePosition.y + bouton.surface->h && event.motion.x >= bouton.surfacePosition.x && event.motion.y >= bouton.surfacePosition.y && event.motion.x <= bouton.surfacePosition.x + bouton.surface->w && event.motion.y <= bouton.surfacePosition.y + bouton.surface->h){
        SDL_FillRect(bouton.surface, NULL, bouton.fond);
        bouton.nameSurface = TTF_RenderText_Blended(bouton.nameFont, bouton.name, noire);
        {//On recentrer le texte agrandi
            bouton.nameSurfacePosition.x = bouton.surface->w/2 - bouton.nameSurface->w/2;
            bouton.nameSurfacePosition.y = bouton.surface->h/2 - bouton.nameSurface->h/2;
        }
        SDL_BlitSurface(bouton.nameSurface, NULL, bouton.surface, &bouton.nameSurfacePosition);
        SDL_BlitSurface(bouton.surface, NULL, ecran, &bouton.surfacePosition);
        SDL_BlitSurface(bouton.effectSurface, NULL, ecran, &bouton.surfacePosition);
        SDL_Flip(ecran);
    }
}

int bouton_Relache(SDL_Bouton bouton, SDL_Surface *ecran, SDL_Event event)
{
    if(event.button.x >= bouton.surfacePosition.x && event.button.y >= bouton.surfacePosition.y && event.button.x <= bouton.surfacePosition.x + bouton.surface->w && event.button.y <= bouton.surfacePosition.y + bouton.surface->h){
        buttonMotion(bouton, ecran, event);
        return 1;
    }
    else{
        return 0;
    }
}
