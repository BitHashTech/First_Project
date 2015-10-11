/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "GHOST.h"

void Ghosts::get_color(int i ) /// each enemy has a color
{
    switch ( i )
    {
    case 0:
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
        break;
    case 1:
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x3 );
        break;
    case 2:
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x5 );
        break;
    case 3:
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x7 );
        break;
    }
}

void Ghosts::clear_temp () /// temp map for the smart enemy
{
    for ( int i = 0 ; i < MapDx ; i++ )
    {
        for ( int j = 0 ; j < MapDy ; j++ )
            temp_map[i][j] = -1 ;
    }
}

void Ghosts::is_possible(int x , int y , Map &map_ ,curser &Curser_) /// check if possible for a move
{

    if ( map_.map[x][y] != SYMBOL_WALL && map_.map[x][y] != SYMBOL_DOOR && ((map_.map[x][y] != SYMBOL_ENEMY_AFRAID  && map_.map[x][y] != SYMBOL_ENEMY_NORMAL) || Curser_.STAR_WARS ))
    {
        queue< pair < int ,int > > way;
        if ( y == -1 )
            y = map_.map[0].size()-1 ;
        else if ( y == map_.map[0].size() )
            y = 0 ;
        way.push({x,y});
        move_sequenses.push_back(way);
    }

}

void Ghosts::update_shape(int i , curser &Curser_) /// if afraid change shape
{
    switch (Curser_.enemy_shapes[i])
    {
    case 0 :
        shape = SYMBOL_ENEMY_NORMAL ;
        break;
    default:
        shape = SYMBOL_ENEMY_AFRAID;
        break;
    }
}

void Ghosts::move_random( pair < int ,int > Position , PacMan &PacMan_ , Map &map_ ,curser &Curser_) /// random enemy move
{

    if ( position == PacMan_.position )
    {
        map_.map[position.first][position.second] = shape ;
        return ;
    }
    is_possible(Position.first+1,Position.second , map_ ,Curser_);
    is_possible(Position.first-1,Position.second , map_ ,Curser_);
    is_possible(Position.first,Position.second+1 , map_ ,Curser_);
    is_possible(Position.first,Position.second-1 , map_ ,Curser_);

}

void Ghosts::attack (int ctr_moves , queue < pair < int , int > > temp , pair < int , int > position , Map &map_ ,curser &Curser_, PacMan &PacMan_) /// smart enemy
{
    if ( ctr_moves == 1 )
    {
        temp.pop();
    }

    if ( position.second == -1 )
        position.second = map_.map[0].size()-1 ;
    else if ( position.second == map_.map[0].size() )
        position.second = 0 ;
    if ( !Curser_.STAR_WARS && ctr_moves>1&&(map_.map[position.first][position.second] == SYMBOL_ENEMY_AFRAID || map_.map[position.first][position.second] == SYMBOL_ENEMY_NORMAL))
        return ;
    if ( map_.map[position.first][position.second] == SYMBOL_WALL  || map_.map[position.first][position.second] == SYMBOL_DOOR )
        return ;

    if ( temp_map[position.first][position.second] < ctr_moves && temp_map[position.first][position.second] != -1 )
        return ;

    temp.push(position);
    temp_map[position.first][position.second] = ctr_moves ;
    if ( position == PacMan_.position)
    {
        if ( move_sequenses.size() && move_sequenses.back().size() > temp.size()   )
        {
            move_sequenses.clear();
            move_sequenses.push_back(temp);
        }
        else
            move_sequenses.push_back(temp);
        return ;
    }
    attack(ctr_moves+1 , temp , {position.first-1,position.second} , map_ ,Curser_, PacMan_ );
    attack(ctr_moves+1 , temp , {position.first+1,position.second} , map_ ,Curser_, PacMan_ );
    attack(ctr_moves+1 , temp , {position.first,position.second-1} , map_ ,Curser_, PacMan_ );
    attack(ctr_moves+1 , temp , {position.first,position.second+1} , map_ ,Curser_, PacMan_ );


}

void Ghosts::select_way (int i , Map &map_ , curser &Curser_ , vector < GUN > &SHOTS) /// if more than one way choose randomly
{
    if ( !move_sequenses.size() )
    {
        Curser_.gotoxy(position.second,position.first);
        get_color(i);
        update_shape(i , Curser_);
        cout << shape ;
        return ;
    }
    int temp = rand()%move_sequenses.size() ;
    Curser_.gotoxy(position.second,position.first);
    if ( Curser_.STAR_WARS && map_.foods[position.first][position.second].shape != HEART_NUM)
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    else
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
    if ( move_sequenses[temp].front().first > position.first )
        direction = "down" ;
    else if ( move_sequenses[temp].front().first < position.first )
        direction = "up" ;
    else if ( move_sequenses[temp].front().second > position.second )
        direction = "right" ;
    else
        direction = "left" ;
    cout <<  map_.foods[position.first][position.second].shape;
    map_.map[position.first][position.second] =  map_.foods[position.first][position.second].shape;
    position = move_sequenses[temp].front();
    map_.map[position.first][position.second] = SYMBOL_ENEMY_NORMAL;
    Curser_.gotoxy(position.second,position.first);
    get_color(color);
    update_shape(i , Curser_);
    cout << shape    ;
    if ( Curser_.STAR_WARS ) {
        if ( !Delay_shot ) {
            if ( !((rand()%100 )%7)  ) {
                GUN shot ;
                shot.color = color ;
                if ( direction == "up" || direction == "down" )
                    shot.shape = SHOT_UP ;
                else
                    shot.shape = SHOT_RIGHT ;
                shot.direction = direction ;
                shot.position = position ;
                shot.owner = "GHOST" ;
                Delay_shot = 3 ;
                SHOTS.push_back(shot) ;
            }
        }
        else {
            Delay_shot-- ;
        }
    }
    move_sequenses.clear();
}
