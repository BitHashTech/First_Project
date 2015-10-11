/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "PLAYER.h"


void player::getname(curser &Curser_) /// the name of the player
{
    for ( int i = 0 ; i < 18 ; i++ )
        cout << '\n';
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE ); /// text color
    cout << "\t\t    Enter your name please to enter the game .. \n\n\t\t\t";

    bool is_spaces = 1;
    name.clear() ;

    while ( name.empty() )
    {

        Curser_.gotoxy(-5,20) ;
        getline(cin,name);
        is_spaces = 1 ;
        for ( int i = 0 ; i < min((int)name.size(),15) ; i++ ) {
            if ( name[i] != SYMBOL_EMPTY && name[i] != '\t' )
                is_spaces = 0 ;
        }
        if ( is_spaces )
            name.clear() ;
    }
    name = name.substr(0,min(15,(int)name.size()));
}



