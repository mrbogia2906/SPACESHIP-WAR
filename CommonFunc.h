#ifndef CommonFunc_H
#define CommonFunc_H

#include<Windows.h>
#include<string>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;


const int BKGROUND_WIDTH = 4000;
const int BKGROUND_HEIGHT = 500;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

const int START_XPOS_MAIN  = 100;
const int START_YPOS_MAIN  = 200;
const int SPEED_MAIN_OBJECT = 5 ;
const int SPEED_BULLET_MAIN = 10 ;
const int ENEMY_SPEED = 5 ;
const int SPEED_BULLET_THREATS = 8 ;
const int NUM_LIVES = 3;
const int NUM_THREAT = 3;
const int BOSS_HEALTH = 5;

static SDL_Window* g_Window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Texture *g_bkground = NULL;
static SDL_Texture *g_win = NULL;
static SDL_Texture *g_lose = NULL;
static SDL_Event g_even;

static TTF_Font *g_Font = NULL;

static Mix_Music* g_music_bkg = NULL;
static Mix_Chunk* g_player_fire = NULL;
static Mix_Chunk* g_enemy_death = NULL;
static Mix_Chunk* g_player_death = NULL;
static Mix_Chunk* g_exp = NULL;

namespace SDL_General
{
	SDL_Texture * LoadImage (string path, SDL_Renderer *ren);
	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y);
	void ApplySurfaceClip(SDL_Renderer* ren, SDL_Texture* src, SDL_Rect* clip, int x, int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void CleanUp();

}

#endif



