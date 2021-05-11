#include "CommonFunc.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "HealthObject.h"
#include "Text.h"

string change_NumberToString(int number){
    number = max(number, 0);
    string res;
    while(number > 0){
        res = char(number % 10 + 48) + res;
        number /= 10;
    }
    if(res.empty()) res = "0";
    return res;
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		g_Window = SDL_CreateWindow(" SPACESHIP WAR ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		g_renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED );

		if (g_renderer!= NULL)
		{
			SDL_SetRenderDrawColor(g_renderer, 255 , 255, 255, 255);

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				cout<<"SDL_image could not initialize! SDL_image Error: "<< IMG_GetError()<<endl;
				return 0;
			}

			if ( Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1 ){
                cout<< " Mix_OpenAudio didn't work !! " <<endl;
                return 0;
			}

            g_music_bkg = Mix_LoadMUS("music/Mercury.wav");
            g_player_fire = Mix_LoadWAV("sound/player_fire.wav");
            g_player_death = Mix_LoadWAV("sound/player_died.wav");
            g_enemy_death = Mix_LoadWAV("sound/alien_died.wav");

            if ( g_music_bkg == NULL || g_player_fire == NULL || g_player_death == NULL ||
                 g_enemy_death == NULL ) {
                if ( g_music_bkg == NULL  ) cout << " g_music_bkg = null " << endl;
                if ( g_player_fire == NULL  ) cout << " g_player_fire = null " << endl;
                if ( g_player_death == NULL ) cout << " g_player_death = null " <<endl;
                if ( g_enemy_death == NULL ) cout << " g_enemy_death = null " <<endl;
                cout << Mix_GetError() << endl;
                return 0;
            }

            // Init TTF and load TTF (gFont)

            if( TTF_Init() == -1 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }

            g_Font = TTF_OpenFont( "font/VeraMoBd.ttf", 28 );
            if( g_Font == NULL )
            {
                printf( "Failed to load VeraMoBd font (TTF)! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }

			return 1;
		}
		else
			return 0;
	}
	else
        return 0;
}

int Game();

int main(int argc, char* argv[])
{
    srand (time(NULL));
    Game();
    return 0;
}

int Game()
{

    bool is_run_screen = true;
    int bground_x = 0;

    //Make background
    bool is_quit = false;
    if (init() == false)
        return 0;
    g_bkground = SDL_General::LoadImage("gfx/bkg.png", g_renderer);

    //Make img win and lose
    g_win = SDL_General::LoadImage("gfx/Youwin.png", g_renderer);
    g_lose = SDL_General::LoadImage("gfx/Youlose.png", g_renderer);

    if (g_bkground == NULL)
    {
        return 0;
    }
    SDL_General::ApplySurface(g_renderer, g_bkground, 0, 0);

    // Make health player
    HealthObject health_Player;
    health_Player.Init(g_renderer);

    // Make game mark
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);

    // Make player
    MainObject human_object;
    human_object.SetRect(START_XPOS_MAIN, START_YPOS_MAIN);
    bool ret = human_object.LoadImg("gfx/player2.png", g_renderer);
    if (!ret)
    {
        return 0;
    }

    // Make explosion
    ExplosionObject exp_main;
    ret = exp_main.LoadImg("gfx/exp.png", g_renderer);
    exp_main.set_clip();
    if (ret == false)
        return 0;

    //Make enemies
    ThreatObject* p_threats = new ThreatObject[NUM_THREAT];
    for (int i = 0; i < NUM_THREAT; i++)
    {
        ThreatObject* p_threat = (p_threats + i);
        if (p_threat)
        {
            ret = p_threat->LoadImg("gfx/enemy2.png", g_renderer);
            if (ret == false)
            {
                return 0;
            }
            int rand_y = rand()%(SCREEN_HEIGHT-50);
            if (rand_y > SCREEN_HEIGHT)
            {
                rand_y = SCREEN_HEIGHT * 0.3;
            }
            p_threat->SetRect(SCREEN_WIDTH + i*400, rand_y);
            p_threat->set_x_val(ENEMY_SPEED);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_renderer);
        }
    }

    // Make boss
    ThreatObject* p_boss = new ThreatObject();

    ret = p_boss->LoadImg("gfx/boss.png", g_renderer);
    if (ret == false)
    {
        return 0;
    }
    p_boss->SetRect(SCREEN_WIDTH - 180, rand() % (SCREEN_HEIGHT-100));
    p_boss->set_y_val(2);

    BulletObject* p_bullet_boss = new BulletObject();
    p_boss->InitBullet(p_bullet_boss, g_renderer);


    unsigned int die_number = 0; // So lan dinh dan
    unsigned int mark_value = 0; // Score
    unsigned int num_hit_boss = 0;

    while (!is_quit)
    {
        while (SDL_PollEvent(&g_even))
        {
            if (g_even.type == SDL_QUIT)
            {
                is_quit = true;
                break;
            }
            human_object.HandleInputAction(g_even, g_renderer, g_player_fire);
        }

        // Apply Background
        if (is_run_screen == true)
        {
            bground_x -= 4;
            if (bground_x <= -(BKGROUND_WIDTH - SCREEN_WIDTH))
            {
                is_run_screen = false;
            }
            else
            {
                SDL_General::ApplySurface(g_renderer, g_bkground, bground_x, 0);
            }
        }
        else
        {
            SDL_General::ApplySurface(g_renderer, g_bkground, bground_x, 0);

            p_boss->HandleMoveBoss(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_boss->Show(g_renderer);
            p_boss->MakeBullet(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            std::vector<BulletObject*> bullet_list = human_object.GetBulletList();
            for (unsigned int b = 0; b < bullet_list.size(); b++)
            {
                BulletObject* p_bullet = bullet_list.at(b);
                if (p_bullet != NULL)
                {
                    // CheckCollision player bullet and boss
                    bool ret_collis = SDL_General::CheckCollision(p_bullet->GetRect(), p_boss->GetRect());
                    if (ret_collis)
                    {
                        num_hit_boss++;
                        Mix_PlayChannel(-1, g_enemy_death, 0);
                        for (int ex = 0; ex < 2; ex++)
                        {
                            int x_pos = (p_boss->GetRect().x + p_boss->GetRect().w*0.5) - EXP_WIDTH*0.5;
                            int y_pos = (p_boss->GetRect().y + p_boss->GetRect().h*0.5) - EXP_HEIGHT*0.5;

                            exp_main.SetFrame(ex);
                            exp_main.SetRect(x_pos, y_pos);
                            exp_main.ShowEx(g_renderer);
                        }
                        human_object.RemoveBullet(b);
                        if (num_hit_boss > BOSS_HEALTH)
                        {
                            SDL_General::ApplySurface(g_renderer,g_win,300,100);
                            SDL_RenderPresent(g_renderer);
                            SDL_Delay(5000);

                            delete[] p_threats;
                            SDL_General::CleanUp();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
            }
        }

        // Show health player
        health_Player.Render(g_renderer);

        // Apply player
        human_object.HandleMove();
        human_object.Show(g_renderer);

        //Make player bullet
        human_object.MakeBullet(g_renderer);

        // Run enemy
        for (int i = 0; i < NUM_THREAT; i++) //
        {
            ThreatObject* p_threat = (p_threats + i);
            if (p_threat)
            {
                p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_renderer);
                p_threat->MakeBullet(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

                // CheckCollision player and enemy
                bool is_collis = SDL_General::CheckCollision(human_object.GetRect(), p_threat->GetRect());
                if (is_collis == true)
                {
                    die_number++;
                    Mix_PlayChannel(-1, g_player_death, 0);
                    for (int ex = 0; ex < 4; ex++)
                    {
                        int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
                        int y_pos = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT*0.5+20;

                        exp_main.SetFrame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.ShowEx(g_renderer);
                        SDL_Delay(100);
                        // Update screen
                        SDL_RenderPresent(g_renderer);
                    }
                    SDL_Delay(1000);
                    if (die_number <= NUM_LIVES - 1)
                    {
                        human_object.SetRect(START_XPOS_MAIN, START_YPOS_MAIN);
                        health_Player.Decrease();
                        health_Player.Render(g_renderer);
                    }
                    else
                    {
                        SDL_General::ApplySurface(g_renderer,g_lose,300,100);
                        SDL_RenderPresent(g_renderer);
                        SDL_Delay(5000);

                        delete[] p_threats;
                        SDL_General::CleanUp();
                        SDL_Quit();
                        return 0;
                    }
                }

                // CheckCollision player and enemy bullet
                std::vector<BulletObject*> bullet_list_threat = p_threat->GetBulletList();
                for (unsigned int tm = 0; tm < bullet_list_threat.size(); tm++)
                {
                    BulletObject* p_bullet = bullet_list_threat.at(tm);
                    if (p_bullet)
                    {
                        bool ret_collis = SDL_General::CheckCollision(p_bullet->GetRect(), human_object.GetRect());
                        if (ret_collis == true)
                        {
                            die_number++;
                            Mix_PlayChannel(-1, g_player_death, 0);
                            for (int ex = 0; ex < 4; ex++)
                            {
                                int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
                                int y_pos = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT*0.5+20;

                                exp_main.SetFrame(ex);
                                exp_main.SetRect(x_pos, y_pos);
                                exp_main.ShowEx(g_renderer);
                                SDL_Delay(100);
                                // Update screen
                                SDL_RenderPresent(g_renderer);
                            }
                            SDL_Delay(1000);
                            if (die_number <= NUM_LIVES - 1)
                            {
                                human_object.SetRect(START_XPOS_MAIN, START_YPOS_MAIN);
                                health_Player.Decrease();
                                health_Player.Render(g_renderer);
                            }
                            else
                            {
                                SDL_General::ApplySurface(g_renderer,g_lose,300,100);
                                SDL_RenderPresent(g_renderer);
                                SDL_Delay(5000);

                                delete[] p_threats;
                                SDL_General::CleanUp();
                                SDL_Quit();
                                return 0;
                            }
                        }
                    }
                }

                // CheckCollision player bullet and enemy
                std::vector<BulletObject*> bullet_list = human_object.GetBulletList();
                for (unsigned int am = 0; am < bullet_list.size(); am++)
                {
                    BulletObject* p_bullet = bullet_list.at(am);
                    if (p_bullet != NULL)
                    {
                        bool ret_collis = SDL_General::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
                        if (ret_collis)
                        {
                            mark_value += 100;
                            Mix_PlayChannel(-1, g_enemy_death, 0);
                            for (int ex = 0; ex < 4; ex++)
                            {
                                int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w*0.5) - EXP_WIDTH*0.5;
                                int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h*0.5) - EXP_HEIGHT*0.5;

                                exp_main.SetFrame(ex);
                                exp_main.SetRect(x_pos, y_pos);
                                exp_main.ShowEx(g_renderer);
                                // Update screen
                                SDL_RenderPresent(g_renderer);
                            }
                            p_threat->Reset(0 - i*400);
                            human_object.RemoveBullet(am);
                        }
                    }
                }
            }
        }

        // Show mark in screen
        std::string val_str_mark = change_NumberToString(mark_value);
        std::string strMark("Score: ");
        strMark += val_str_mark;
        mark_game.SetText(strMark);
        mark_game.CreateGameText(g_Font, g_renderer);

        // Update screen
        SDL_RenderPresent(g_renderer);
        SDL_Delay(16);
    }

    delete[] p_threats;
    SDL_General::CleanUp();
    SDL_Quit();
    return 0;
}
