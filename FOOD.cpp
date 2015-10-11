/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "FOOD.h"


void Food::get_power(player &player1_ , curser &Curser_) /// apply foods power
{
    if ( shape == HEART_NUM )
    {
        PlaySound(TEXT("Data\\pacman_eatfruit.wav"),NULL,SND_FILENAME);
        player1_.total_score += score_per_heart ;
        player1_.bonus_score += score_per_heart ;
        int col_pos  ;
        if ( Curser_.life_ctr < 10 ) {
            Curser_.life_ctr++;
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
            switch(Curser_.level)
            {
            case 1:
            case 3:
                col_pos = MapDx + 1 ;
                break;
            default:
                col_pos = MapDx - 1  ;
                break;
            }
            Curser_.last_life_pos += 2;
            Curser_.gotoxy(Curser_.last_life_pos,col_pos);
            cout << char(HEART_NUM) ;
        }
        return ;
    }
    player1_.score_food += score_per_food , player1_.total_score += score_per_food;
    if ( shape == SYMBOL_SUPER_FOOD )
    {
        PlaySound(TEXT("Data\\aklha.wav"),NULL,SND_FILENAME); /// sound
        for ( int i = 0 ; i < 4 ; i++ )
            Curser_.enemy_shapes[i] = 1 ;
        Curser_.time_afraid = time_Afraid ;
    }
}
