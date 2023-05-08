#ifndef BTN_BUTTON_H_INCLUDED
#define BTN_BUTTON_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define BTN_BUTTON_SIMPLE 0
#define BTN_BUTTON_SCALETEXT 1
#define BTN_BUTTON_SCALEBOX 2
#define BTN_SURFACE_PTR 0
#define BTN_TEXTURE_PTR 1
#define BTN_MAX_BUTTON_LABEL_CHAR 255

typedef struct
{
    SDL_Color normalColor;
    SDL_Color hoverColor;
    SDL_Color labelColor;
    SDL_Color labelOnHoverColor;
    SDL_Color borderColor;
    SDL_Color borderOnHoverColor;
} BTN_Colors;

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
    char label[BTN_MAX_BUTTON_LABEL_CHAR];
    BTN_Colors colors;
    TTF_Font *font;
    Uint8 type;
    SDL_bool hide;
    SDL_bool selected;
    SDL_bool hovered;
} BTN_Button;


extern BTN_Button* BTN_CreateButtonWithTexture(Uint8 type, int w, int h, const char *name, const char *font);
extern int BTN_CopyButton(BTN_Button *button, SDL_Renderer *renderer, SDL_Rect *dst);
extern void BTN_FreeButton(BTN_Button *button);
extern int BTN_Update(BTN_Button *button, SDL_Renderer *renderer, SDL_Event *event, SDL_Rect relativeTo);
extern void BTN_HideButton(BTN_Button *button, SDL_bool hide);

#endif // BTN_BUTTON_H_INCLUDED
