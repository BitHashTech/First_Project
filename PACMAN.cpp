/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "PACMAN.h"


void PacMan::get_shape() /// direction shape
{
    if ( last_direction == "up" )
        shape = SYMBOL_PLAYER_UP ;
    else if ( last_direction == "down"  )
        shape = SYMBOL_PLAYER_DOWN ;
    else if ( last_direction == "left" )
        shape = SYMBOL_PLAYER_LEFT;
    else
        shape = SYMBOL_PLAYER_RIGHT;
}

bool PacMan::isValidPos(int y) /// in  2D array
{
    return (y == -1|| y == MapDy) ;
}

void PacMan::teleport(curser &Curser_ , Map &map_)
{
    vector < pair < int , int > > temp ;
    for ( int i = 0 ; i < 4 ; i++ ) {
        if ( SUPER_FOOD[i] == position )
            continue;
        temp.push_back(SUPER_FOOD[i]);
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    Curser_.gotoxy(position.second,position.first);
    cout << SYMBOL_SUPER_FOOD;
    position = temp[rand()%temp.size()];
    map_.map[position.first][position.second] = shape ;
    Curser_.gotoxy(position.second ,position.first);
    cout << shape ;
}

void PacMan::movePlayer( string &temp_direction, Map &map_ , player &player1_ ,curser &Curser_ ) /// if valid move
{
    last_direction = temp_direction ;
    int x = position.first , y = position.second ;
    if ( temp_direction == "up" )
        x--;
    else if ( temp_direction == "down" )
        x++;
    else if ( temp_direction == "left" )
        y-- ;
    else
        y++;

    if (isValidPos(y))
    {
        switch ( y )
        {
        case -1 :
            y = MapDy-1;
            break;
        case MapDy :
            y = 0 ;
            break;
        }
    }
    if ( map_.foods[position.first][position.second].shape == SYMBOL_SUPER_FOOD && Curser_.STAR_WARS ) {
        map_.map[position.first][position.second] = SYMBOL_SUPER_FOOD;
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
        Curser_.gotoxy(position.second,position.first);
        cout << SYMBOL_SUPER_FOOD ;
    }
    else {
        map_.map[position.first][position.second] = SYMBOL_EMPTY;
        Curser_.gotoxy(position.second,position.first);
        cout << " " ;
    }
    position.first = x;
    position.second = y;
    ///
    get_shape();
    Curser_.gotoxy(position.second,position.first);
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    cout << shape ;
    if (Curser_.STAR_WARS &&  map_.foods[position.first][position.second].shape == SYMBOL_SUPER_FOOD )
    {
        teleport(Curser_,map_);
        return ;
    }
    if ( map_.foods[position.first][position.second].shape != SYMBOL_SPACE && map_.map[position.first][position.second] != SYMBOL_SPACE
        &&map_.map[position.first][position.second] != SYMBOL_EMPTY )
    {
        map_.foods[position.first][position.second].get_power( player1_ , Curser_);
        map_.foods[position.first][position.second].shape = SYMBOL_EMPTY ;
        PlaySoundA(TEXT("Data\\waka3.wav"),NULL ,SND_FILENAME) ;
    }
    map_.map[position.first][position.second] = shape;
    return ;
}

