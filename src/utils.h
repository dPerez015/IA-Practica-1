#pragma once
#include <string>
#include <SDL.h>

/* Get the resource path for resources located in res/subDir */
std::string getResourcePath(const std::string &subDir = "");

/* draw utilities */
void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
//void draw_arrow(SDL_Renderer* rend, Vector2D start, float size, float orient);
void draw_arrow(SDL_Renderer* rend, int cx, int cy, float size, float orient); 