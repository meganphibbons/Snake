#include <allegro.h>
#include <iostream>
#include <deque>

using namespace std;

void init();
void deinit();

struct snakeBody
    {
        int x;
        int y;
        snakeBody(int xPos, int yPos)
        {
            x = xPos;
            y = yPos;
        }
    };

int main()
{
    init();

    const int BACKGROUND = 0xB266FF;
    const int BORDER = 0x99FFFF;
    const int BODY = 0xB2FF66;
    const int FOOD = 0xFFCCFF;

    deque<snakeBody> snake;
    bool lost = false;
    bool won = false;
    int snakeX = SCREEN_W / 2;
    int snakeY = SCREEN_H / 2;
    int points = 0;

    enum orientations
    {
        LEFT = 0, RIGHT, UP, DOWN
    };

    int direction = UP;

    BITMAP *board = create_bitmap(SCREEN_W, SCREEN_H);

    int foodX = (rand() % ((SCREEN_W - 40) / 20)) * 20 + 20;
    int foodY = (rand() % ((SCREEN_H - 40) / 20)) * 20 + 20;

    snake.push_back(snakeBody(snakeX, snakeY));

    while(!key[KEY_UP])
    {
        rectfill(board, 0, 0, SCREEN_W, SCREEN_H, BACKGROUND);
        textprintf_centre_ex(board, font, SCREEN_W / 2, SCREEN_H / 2 - 10, makecol(0, 0, 0), -1, "Welcome to Snake! Collect the food and earn as many points as possible!");
        textprintf_centre_ex(board, font, SCREEN_W / 2, SCREEN_H / 2 + 10, makecol(0, 0, 0), -1, "Press the UP arrow key to begin. Use the arrow keys to move.");
        blit(board, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    while(!key[KEY_ESC] && !lost && !won)
    {
        if(snakeX > (SCREEN_W - 40) || snakeX < 20 || snakeY > (SCREEN_H - 40) || snakeY < 20)
            lost = true;
        for(int i = 1; i < points + 1; i++)
        {
            if(snakeX == snake[i].x && snakeY == snake[i].y)
                lost = true;
             if(foodX == snake[i].x && foodY == snake[i].y)
             {
                foodX = (rand() % ((SCREEN_W - 40) / 20)) * 20 + 20;
                foodY = (rand() % ((SCREEN_H - 40) / 20)) * 20 +  20;
             }
        }
        rectfill(board, 0, 0, SCREEN_W, SCREEN_H, BORDER);
        rectfill(board, 20, 20, SCREEN_W - 20, SCREEN_H - 20, BACKGROUND);
        if(foodX == snakeX && foodY == snakeY)
        {
            foodX = (rand() % ((SCREEN_W - 40) / 20)) * 20 + 20;
            foodY = (rand() % ((SCREEN_H - 40) / 20)) * 20 + 20;
            points++;
            snake.push_back(snakeBody(snake[points].x, snake[points].y));
        }
        textprintf_centre_ex(board, font, SCREEN_W / 2, SCREEN_H - 10, makecol(0, 0, 0), -1, "Points: %d", points);
        rectfill(board, foodX, foodY, foodX + 20, foodY + 20, FOOD);
        for(int i = 0; i < points + 1; i++)
            rectfill(board, snake[i].x, snake[i].y, snake[i].x + 20, snake[i].y + 20, BODY);
        if(key[KEY_LEFT] && direction != RIGHT)
            direction = LEFT;
        else if(key[KEY_RIGHT] && direction != LEFT)
            direction = RIGHT;
        else if(key[KEY_UP] && direction != DOWN)
            direction = UP;
        else if(key[KEY_DOWN] && direction != UP)
            direction = DOWN;
        if(direction == LEFT)
            snakeX -= 20;
        else if(direction == RIGHT)
            snakeX += 20;
        else if(direction == UP)
            snakeY -= 20;
        else
            snakeY += 20;
        snake.pop_back();
        snake.push_front(snakeBody(snakeX, snakeY));
        rest(80);
        blit(board, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    while(!key[KEY_ESC])
    {
        rectfill(board, 0, 0, SCREEN_W, SCREEN_H, BACKGROUND);
        if(lost)
            textprintf_centre_ex(board, font, SCREEN_W / 2, SCREEN_H / 2, makecol(0, 0, 0), -1, "Sorry, you lost! You had %d points!", points);
        else if(won)
            textprintf_centre_ex(board, font, SCREEN_W / 2, SCREEN_H / 2, makecol(0, 0, 0), -1, "Congrats! You won!");
        else
            textprintf_centre_ex(board, font, SCREEN_W / 2, SCREEN_H / 2, makecol(0, 0, 0), -1, "Points: %d. Press ESC to exit.", points);
        blit(board, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    deinit();
    return 0;
}
END_OF_MAIN()

void init()
{
    srand(time(0));
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if(depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    if(res != 0)
    {
        allegro_message(allegro_error);
        exit(-1);
    }
    install_timer();
    install_keyboard();
    install_mouse();
}

void deinit()
{
    clear_keybuf();
}
