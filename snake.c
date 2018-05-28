#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <sys/select.h>
#include <stdio.h>
#include <time.h>

#define DESIRED_WIDTH  70
#define DESIRED_HEIGHT 25

int main( int argc, char *argv[] )
{
    int key = KEY_RIGHT;
    if( ( g_mainwin = initscr() ) == NULL ) {
        perror( "error initialising ncurses" );
        exit( EXIT_FAILURE );
    }
    
    // Set up
    srand( time( NULL ) );
    noecho( );
    curs_set( 2 );
    halfdelay( 1 );
    keypad( g_mainwin, TRUE );
    g_oldcur = curs_set( 0 );
    start_color( );
    init_pair( 1, COLOR_RED,     COLOR_BLACK );
    init_pair( 2, COLOR_GREEN,   COLOR_BLACK );
    init_pair( 3, COLOR_YELLOW,  COLOR_BLACK );
    init_pair( 4, COLOR_BLUE,    COLOR_BLACK );
    init_pair( 5, COLOR_CYAN,    COLOR_BLACK );
    init_pair( 6, COLOR_MAGENTA, COLOR_BLACK );
    init_pair( 7, COLOR_WHITE,   COLOR_BLACK );
    getmaxyx( g_mainwin, g_height, g_width );
    
    g_width  = g_width  < DESIRED_WIDTH  ? g_width  : DESIRED_WIDTH;
    g_height = g_height < DESIRED_HEIGHT ? g_height : DESIRED_HEIGHT; 
    
    // Set up the 2D array of all spaces
    spaces = (bool*) malloc( sizeof( bool ) * g_height * g_width );

    snake_draw_board( );
    snake_draw_fruit( );
    pos head = { 5,5 };
    enqueue( head );
    
    // Event loop
    while( 1 )
    {
        int in = getch( );
        if( in != ERR )
            key = in;
        switch( key )
        {
            case KEY_DOWN:
            case 'k':
            case 'K':
                head.y++;
                break;
            case KEY_RIGHT:
            case 'l':
            case 'L':
                head.x++;
                break;
            case KEY_UP:
            case 'j':
            case 'J':
                head.y--;
                break;
            case KEY_LEFT:
            case 'h':
            case 'H':
                head.x--;
                break;

        }
        if( !snake_in_bounds( head ) )    
            snake_game_over( );
        else
            snake_move_player( head );
    }
    snake_game_over( );
}
