/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "MAP.h"


void Map::clean_map() /// initialize the map with nothing
{
    for ( int i = 0 ; i < MapDx ; i++ )
        map[i].clear();
}

void Map::read_map(curser &Curser_) /// get the map from a file
{
    ifstream fin;
    switch ( Curser_.level )
    {
    case 1:
    case 3:
        fin.open("Data\\map_classic.txt");
        break;
    default:
        fin.open("Data\\map2.txt");
        break;
    }
    for ( int i = 0 ; i <  MapDx ; i++ )
    {
        fin >> map[i] ;
    }
    fin.close() ;
}

void Map::Generate() /// put food in food map
{
    ///srand(time(0));
    for(int i=0; i<MapDx; i++)
    {
        for(int j=0; j<MapDy; j++)
        {
            foods[i][j].shape = SYMBOL_NORMAL_FOOD ;
        }
    }
}

void Map::get_life(curser &Curser_) /// randomly put a life in the level
{
    if ( !((rand() % 10000) % 269 ) )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
        switch ( Curser_.level )
        {
        case 3:
        case 1:
            foods[life_pos1.second][life_pos1.first].shape = char(3) ;
            map[life_pos1.second][life_pos1.first] = char(3) ;
            Curser_.gotoxy(life_pos1.first,life_pos1.second);
            break;
        default:
            foods[life_pos2.second][life_pos2.first].shape = char(3) ;
            map[life_pos2.second][life_pos2.first] = char(3) ;
            Curser_.gotoxy(life_pos2.first,life_pos2.second);
            break;
        }
        cout << char(3);
    }
}
void Map::showMap(curser &Curser_) /// show the map
{
    cout << endl;
    for (int x = 0; x < MapDx; x++)
    {
        for ( int i = 0 ; i < 3 ; i++ )
            cout << '\t' ;
        for ( int y = 0 ; y < map[x].size() ; y++ )
        {
            switch ( map[x][y] )
            {
            case SYMBOL_FOOD:
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
                cout << foods[x][y].shape ;
                break;
            case SYMBOL_WALL:
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xB );
                cout << SYMBOL_SUPER_WALL ;
                break;
            case SYMBOL_SPACE:
                cout << SYMBOL_EMPTY ;
                foods[x][y].shape = SYMBOL_EMPTY ;
                break;
            case SYMBOL_SUPER:
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
                cout << SYMBOL_SUPER_FOOD ;
                foods[x][y].shape = SYMBOL_SUPER_FOOD;
                break;
            default :
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xB );
                cout << map[x][y];
                break;
            }
        }
        cout << endl;
    }
    Curser_.gotoxy(0,30);
    cout << "Press p to pause || any key to resume \n" ;
    Curser_.gotoxy(0,31);
    cout << "But e to EXIT" ;
    if ( Curser_.STAR_WARS )
        cout << " , SPACE to fire 500 score to win";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    Curser_.gotoxy(-20,10);
    cout << "PLAYER NAME:";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    Curser_.gotoxy(30,10);
    cout << "FOOD  SCORE: ";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x9 );
    Curser_.gotoxy(30,12);
    cout << "GHOST SCORE: ";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x2 );
    Curser_.gotoxy(30,14);
    cout << "BONUS SCORE: ";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xF );
    Curser_.gotoxy(30,16);
    cout << "TOTAL SCORE: ";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
    for ( int i = 0 ; i < 6 ; i += 2 )
    {
        int col_pos ;
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
        Curser_.gotoxy(i,col_pos);
        cout << char(HEART_NUM);
    }

}
