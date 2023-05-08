#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "bouton.h"
#include "boutonFonction.h"

SDL_Bouton CreerSDLBouton(int *surface_informations, char *name, SDL_Rect pos, Uint32 fond, Uint32 effect_color, int *sizes, char *bouton_font_name, char *effect_font_name, int transparence)
{
    int i = 0;
    char *chemin_acces = "C:/Windows/Fonts/";
    SDL_Bouton bouton;
    SDL_Color noire = {0, 0, 0};

    //nom du bouton
    while(i < strlen(name) || i < LONGUEUR_NOM_BOUTON){
        bouton.name[i] = name[i];
        i++;
    }
    // La police du bouton
    bouton.nameFont = TTF_OpenFont(stradd(chemin_acces, bouton_font_name), sizes[0]);
    // La police appliquée pour l'effet
    bouton.effectFont = TTF_OpenFont(stradd(chemin_acces, effect_font_name), sizes[1]);
    if(bouton.nameFont == NULL || bouton.effectFont == NULL){
        bouton.nameFont = TTF_OpenFont("C:/Windows/Fonts/tahoma.ttf", sizes[0]);
        bouton.effectFont = TTF_OpenFont("C:/Windows/Fonts/tahoma.ttf", sizes[1]);
    }

    bouton.nameSurface = TTF_RenderText_Blended(bouton.nameFont, bouton.name, noire);
    bouton.surface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, surface_informations[0], surface_informations[1], surface_informations[2], 0, 0, 0, 0);
    bouton.effectSurface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, surface_informations[0], surface_informations[1], surface_informations[2], 0, 0, 0, 0);

    {//Remplir la surface du bouton avec la couleur de fondbouton.fond = SDL_MapRGB(bouton.surface->format, 0, 0, 0);}
        bouton.fond = fond;
        SDL_FillRect(bouton.surface, NULL, bouton.fond);
        SDL_Flip(bouton.surface);
    }

    {//On blite le nom du bouton dans la surface : N°5
    bouton.nameSurfacePosition.x = bouton.surface->w/2 - bouton.nameSurface->w/2;
    bouton.nameSurfacePosition.y = bouton.surface->h/2 - bouton.nameSurface->h/2;
    SDL_BlitSurface(bouton.nameSurface, NULL, bouton.surface, &bouton.nameSurfacePosition);
    }

    {//On donne une valeur aux autres sous-variables:
            //1.La surface où se trouve le bouton : c'est bon (voir ligne 19).
           //2.La surface contenant le nom du bouton : c'est ok(voir ligne 20).
          //3.La surface qui produit l'efect : voir ligne 46
        {//4.Maintenant la position de la surface:
            bouton.surfacePosition.x = pos.x;
            bouton.surfacePosition.y = pos.y;
        }
        {//7.Le fond à rendre transparent:
         bouton.effectColor = effect_color;
         SDL_FillRect(bouton.effectSurface, NULL, bouton.effectColor);
         SDL_Flip(bouton.effectSurface);
        }
        /* 10.La transparence : */ bouton.nivo_transparence = transparence;
    }
    return bouton;
}

void SDL_BlitButton(SDL_Bouton bouton, SDL_Surface *ecran)
{
    SDL_BlitSurface(bouton.surface, NULL, ecran, &bouton.surfacePosition);
}

void SDL_FreeButton(SDL_Bouton bouton)
{
    SDL_FreeSurface(bouton.surface);
    SDL_FreeSurface(bouton.effectSurface);
    SDL_FreeSurface(bouton.nameSurface);
    TTF_CloseFont(bouton.effectFont);
    TTF_CloseFont(bouton.nameFont);
}

char *stradd(char *chaine1, char *chaine2)
{
    char *chaine = malloc(strlen(chaine1)+strlen(chaine2)+1 * sizeof(char));
    strcat(chaine, chaine1);
    strcat(chaine, chaine2);
    return chaine;
}
