#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#define WIDTH 40
#define HEIGHT 15
#define PADDLE_SIZE 3
#define ENDSCORE 3

typedef struct _point_t
{
    int x;
    int y;
} point_t;

typedef struct _game_data_t
{
    point_t paddle_left;
    point_t paddle_right;
    point_t ball;
    point_t ball_direction;
    unsigned char score_left;
    unsigned char score_right;
    char paused;
    char ended;
} game_data_t;

void place_paddels(game_data_t* game_data)
{
    // left
    mvprintw(game_data->paddle_left.y - 1, 2, "#");
    mvprintw(game_data->paddle_left.y, 2, "#");
    mvprintw(game_data->paddle_left.y + 1, 2, "#");

    // right
    mvprintw(game_data->paddle_right.y - 1, WIDTH - 2, "#");
    mvprintw(game_data->paddle_right.y, WIDTH - 2, "#");
    mvprintw(game_data->paddle_right.y + 1, WIDTH - 2, "#");
}

void place_ball(game_data_t* game_data)
{
    mvprintw(game_data->ball.y, game_data->ball.x, "o");
}

void print_field(game_data_t* game_data)
{
    clear();
    for (size_t x = 1; x < WIDTH; x++)
    {
        mvprintw(1, x, "x");
        mvprintw(HEIGHT, x, "x");
    }
    
    for (size_t y = 1; y <= HEIGHT; y++)
    {
        mvprintw(y, 1, "x");
        mvprintw(y, WIDTH, "x");
    }
    
    place_ball(game_data);
    place_paddels(game_data);

    if (game_data->paused && !game_data->ended)
    {
        mvprintw(7,18,"Paused");
        mvprintw(8,18,"======");
        mvprintw(9,6,"(move paddle to continue...)");
    }

    if (game_data->ended)
    {
        mvprintw(7,13,"%s Player Won!", game_data->score_left > game_data->score_right ? "Left" : "Right");
        mvprintw(8,11,"====================");
        mvprintw(9,13,"Press q to quit");
    }
    

    mvprintw(0, 16, "%d   --   %d", game_data->score_left, game_data->score_right);
}

void key_proc(game_data_t* game_data)
{
    int ch = getch();

    switch (ch)
    {       
    case KEY_UP:
        game_data->paused = 0;
        if(game_data->paddle_right.y>3)
            game_data->paddle_right.y -= 1;
        break;
    case KEY_DOWN:
        game_data->paused = 0;
        if(game_data->paddle_right.y<HEIGHT-2)
            game_data->paddle_right.y += 1;
        break;
    case 'w':
        game_data->paused = 0;  
        if(game_data->paddle_left.y>3)
            game_data->paddle_left.y -= 1;
        break;
    case 's':
        game_data->paused = 0;
        if(game_data->paddle_left.y<HEIGHT-2)
            game_data->paddle_left.y += 1;
        break;
    case 'r':
        game_data->ball.x = WIDTH/2;
        game_data->ball.y = HEIGHT/2;
        break;
    case 'p':
        game_data->paused = 1;
        break;
    case 'q': exit(EXIT_SUCCESS);
    default:
        break;
    }
}

void move_ball(game_data_t* game_data)
{
    game_data->ball.x += game_data->ball_direction.x;
    game_data->ball.y += game_data->ball_direction.y;
}

void detect_collision(game_data_t* game_data)
{
    // hit top
    if (game_data->ball.y <= 2)
    {
        game_data->ball_direction.y = 1;
    }

    // hit bottom
    if (game_data->ball.y >= HEIGHT-1)
    {
        game_data->ball_direction.y = -1;
    }
    
    // hit left paddle
    if (game_data->ball.x == 3 && (game_data->ball.y == game_data->paddle_left.y || game_data->ball.y+1 == game_data->paddle_left.y || game_data->ball.y-1 == game_data->paddle_left.y))
    {
        game_data->ball_direction.x = 1;
    }
    
    // hit right paddle
    if (game_data->ball.x == WIDTH-3 && (game_data->ball.y == game_data->paddle_right.y || game_data->ball.y+1 == game_data->paddle_right.y || game_data->ball.y-1 == game_data->paddle_right.y))
    {
        game_data->ball_direction.x = -1;
    }

    // hit left wall
    if (game_data->ball.x < 3)
    {
        game_data->ball.x = WIDTH/2;
        game_data->ball.y = HEIGHT/2;
        game_data->score_right++;
        game_data->paused = 1;
        game_data->ball_direction.x *= -1;
    }
    
    // hit right wall
    if (game_data->ball.x > WIDTH-3)
    {
        game_data->ball.x = WIDTH/2;
        game_data->ball.y = HEIGHT/2;
        game_data->score_left++;
        game_data->paused = 1;
        game_data->ball_direction.x *= -1;
    }

    // game end condition
    if (game_data->score_left == ENDSCORE || game_data->score_right == ENDSCORE)
    {
        game_data->ended = 1;
    }
}

int main(void)
{
    game_data_t game_data = {
        .paddle_left = {2, HEIGHT / 2},
        .paddle_right = {WIDTH-2,  HEIGHT / 2},
        .ball = {WIDTH / 2, HEIGHT / 2},
        .ball_direction = {1,1},
        .score_left = 0,
        .score_right = 0,
        .paused = 0,
        .ended = 0
    };
    
    int x, y;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    curs_set(0);

    print_field(&game_data);

    refresh();

    int frame = 0;
    while(1)
    {
        key_proc(&game_data);
        detect_collision(&game_data);
        if(frame%3==0 && !game_data.paused && !game_data.ended) move_ball(&game_data);
        print_field(&game_data);
        usleep(50000);
        frame++;
    }

    endwin();

    return 0;
}