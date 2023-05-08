#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../inc/BTN_.h"

SDL_Texture* SDL_CreateTextureFromPixel(SDL_Renderer *renderer, void *pixels, int w, int h, int depth, int pitch, Uint32 format)
{
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, depth, pitch, format);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


extern BTN_Button* BTN_CreateButton(Uint8 type, int w, int h, const char *label, TTF_Font *font)
{
    //Creation of an instance of the button//
    BTN_Button *button = malloc(sizeof(*button));
    if(button == NULL)
    {
        SDL_SetError("Can't create an instance of a button :: BTN_CreateButton().\n");
        return NULL;
    }

    //The font use to draw the label in the button//
    button->font = font;
    if(button->font == NULL)
    {
        SDL_SetError("La police n'a pas pu etre creer :: BTN_CreateButton().\n");
        button->font = TTF_OpenFont("C/Windows/Fonts/arial.ttf", 12);
    }

    //Set the label of the button//
    if(label == NULL)
    {
        fprintf(stdout, "The label of the button is empty :: BTN_CreateButton().\n");
        SDL_SetError("The label of the button is empty :: BTN_CreateButton().\n");
        label = " ";
    }
    if(strlen(label) > BTN_MAX_BUTTON_LABEL_CHAR - 1)
    {
        fprintf(stdout, "The label of the button is to long :: BTN_CreateButton().\n");
        SDL_SetError("The label of the button is to long :: BTN_CreateButton().\n");
    }
    strcpy(button->label, label);

    /*
    * The colors of the buttons
    */

    //The color of the label in the button
    button->colors.labelColor.r = 0;
    button->colors.labelColor.g = 0;
    button->colors.labelColor.b = 0;
    button->colors.labelColor.a = 255;

    //The background color of the button
    button->colors.normalColor.r = 255;
    button->colors.normalColor.g = 255;
    button->colors.normalColor.b = 255;
    button->colors.normalColor.a = 255;

    //The background color of the button on hover
    button->colors.hoverColor.r = 0;
    button->colors.hoverColor.g = 0;
    button->colors.hoverColor.b = 255;
    button->colors.hoverColor.a = 128;

    //The background color of the button on hover
    button->colors.borderColor.r = 0;
    button->colors.borderColor.g = 0;
    button->colors.borderColor.b = 255;
    button->colors.borderColor.a = 128;

    return button;
}

extern int BTN_CopyButton(BTN_Button *button, SDL_Renderer *renderer, SDL_Rect *dst)
{
    button->rect = *dst;

    //Creation of the texture of the button
    button->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button->rect.w * 2, button->rect.h);
    if(button->texture == NULL)
    {
        SDL_SetError("Can't textured the button :: BTN_CopyButton()\n");
        return -1;
    }
    SDL_SetTextureBlendMode(button->texture, SDL_BLENDMODE_BLEND);

    //It is with this texture that we will draw the different state of the button(hover, normal)
    SDL_Texture *temp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button->rect.w, button->rect.h);
    if(temp == NULL)
    {
        SDL_SetError("Can't textured the button :: BTN_CopyButton()\n");
        return -1;
    }
    SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);


    SDL_Texture *renderTarget = SDL_GetRenderTarget(renderer);//save the default renderer target

    /*
    * First of all, let's draw the button at his normal state
    */

    //Creation of the label's texture on normal state
    SDL_Surface *s = TTF_RenderText_Blended(button->font, button->label, button->colors.labelColor);
    SDL_Texture *labelTexture = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);
    if(labelTexture == NULL)
    {
        SDL_SetError("Cannot create the texture of the label :: BTN_CopyButton().\n");
        return -1;
    }
    SDL_Rect labelRect;
    SDL_QueryTexture(labelTexture, NULL, NULL, &labelRect.w, &labelRect.h);
    labelRect.x = (button->rect.w/2) - (labelRect.w/2);
    labelRect.y = (button->rect.h/2) - (labelRect.h/2);

    //set the render target to a temp texture
    SDL_SetRenderTarget(renderer, temp);

    //fill the button texture with normal background color
    SDL_SetRenderDrawColor(renderer, button->colors.normalColor.r, button->colors.normalColor.g, button->colors.normalColor.b, button->colors.normalColor.a);
    SDL_RenderClear(renderer);

    //set the outline color
    SDL_SetRenderDrawColor(renderer, button->colors.borderColor.r, button->colors.borderColor.g, button->colors.borderColor.b, button->colors.borderColor.a);
    SDL_RenderDrawRect(renderer, NULL);

    //draw the label
    SDL_RenderCopy(renderer, labelTexture, NULL, &labelRect);
    SDL_RenderPresent(renderer);

    //set the renderer target to the button texture
    SDL_SetRenderTarget(renderer, button->texture);
    SDL_RenderCopy(renderer, temp, NULL, &(SDL_Rect){0, 0, button->rect.w, button->rect.h});
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(labelTexture);

    /*
    * Now, let's draw the button at his hovered state
    */

    //Creation of the label's texture on normal state
    s = TTF_RenderText_Blended(button->font, button->label, button->colors.labelOnHoverColor);
    labelTexture = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);
    if(labelTexture == NULL)
    {
        SDL_SetError("Cannot create the texture of the label :: BTN_CopyButton().\n");
        return -1;
    }
    SDL_QueryTexture(labelTexture, NULL, NULL, &labelRect.w, &labelRect.h);
    if(button->type == BTN_BUTTON_SCALETEXT)
    {
        labelRect.w += 2;
        labelRect.h += 2;
    }
    labelRect.x = (button->rect.w/2) - (labelRect.w/2);
    labelRect.y = (button->rect.h/2) - (labelRect.h/2);

    //set the render target to a temp texture
    SDL_SetRenderTarget(renderer, temp);

    //fill the button texture with hover background color
    SDL_SetRenderDrawColor(renderer, button->colors.hoverColor.r, button->colors.hoverColor.g, button->colors.hoverColor.b, button->colors.hoverColor.a);
    SDL_RenderClear(renderer);

    //set the outline color
    SDL_SetRenderDrawColor(renderer, button->colors.borderOnHoverColor.r, button->colors.borderOnHoverColor.g, button->colors.borderOnHoverColor.b, button->colors.borderOnHoverColor.a);
    SDL_RenderDrawRect(renderer, NULL);

    //draw the label
    SDL_RenderCopy(renderer, labelTexture, NULL, &labelRect);
    SDL_RenderPresent(renderer);

    //set the renderer target to the button texture
    SDL_SetRenderTarget(renderer, button->texture);
    SDL_RenderCopy(renderer, temp, NULL, &(SDL_Rect){button->rect.w-1, 0, button->rect.w, button->rect.h});
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(labelTexture);

    //reset the default renderer target
    SDL_SetRenderTarget(renderer, renderTarget);
    SDL_RenderCopy(renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h}, &button->rect);
    SDL_RenderPresent(renderer);

    return 0;
}

extern void BTN_FreeButton(BTN_Button *button)
{
    if(button != NULL)
    {
        if(button->texture != NULL)
            SDL_DestroyTexture(button->texture);
        free(button);
    }
}

extern char *BTN_Setlabel(BTN_Button *button, char *label)
{
}

extern TTF_Font *BTN_SetFont(BTN_Button *button, char *file, int fontSize, SDL_Window *window)
{
}

extern int BTN_setFontColor(BTN_Button *button, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

}

extern int BTN_SetBackgroundColor(BTN_Button *button, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Window *window)
{

}

extern void BTN_SetHoveredColor(BTN_Button *button, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
}

extern int BTN_Update(BTN_Button *button, SDL_Renderer *renderer, SDL_Event *event, SDL_Rect relativeTo)
{
    if(button == NULL || button->hide == SDL_TRUE)
        return -1;

    SDL_Point cursor = {event->button.x - relativeTo.x, event->button.y - relativeTo.y};
    if(event->type == SDL_MOUSEMOTION && SDL_PointInRect(&cursor, &button->rect))
    {
        button->hovered = SDL_TRUE;

        if(button->type == BTN_BUTTON_SCALEBOX)
            SDL_RenderCopy(renderer, button->texture, &(SDL_Rect){button->rect.w-1, 0, button->rect.w, button->rect.h},
                           &(SDL_Rect){button->rect.x - 1, button->rect.y - 1, button->rect.w + 2, button->rect.h + 2});
        else
            SDL_RenderCopy(renderer, button->texture, &(SDL_Rect){button->rect.w-1, 0, button->rect.w, button->rect.h},
                           &button->rect);
    }
    else if(event->type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&cursor, &button->rect))
    {
        button->hovered = SDL_FALSE;
        button->selected = SDL_TRUE;
        SDL_RenderCopy(renderer, button->texture, &(SDL_Rect){0, 0, button->rect.w, button->rect.h}, &button->rect);
    }
    return 0;
}

void BTN_HideButton(BTN_Button *button, SDL_bool hide)
{
    button->hide = hide;
}
