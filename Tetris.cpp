#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

using namespace sf;
using namespace std;
const int M = 20;
const int N = 10;

int field[M][N] = {0};
int w = 34;

struct Point
{
    int x, y;
}a[4], b[4];
int figures[7][4] = {
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};
int main()
{
    RenderWindow window(VideoMode(N * w, M * w), "Tetris");
    Texture t;
    t.loadFromFile("Paint/tiles.png" );
    Sprite tiles(t);
    tiles.setTextureRect(IntRect(0, 0, w, w));
    int dx = 0;
    bool rotate = false;
    float timer = 0, delay = 0.7;
    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
               window.close();
            }
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Up)
                    rotate = true;
                else if (event.key.code == Keyboard::Right)
                    dx=1;
                else if (event.key.code == Keyboard::Left)
                    dx = -1;
        }
        for (int i = 0; i < 4; i++)
        {
            a[i].x += dx;
        }
        if (rotate){
            Point p = a[1];
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
        }
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                a[i].y += 1;
                timer = 0;
            }
        }

        int n = 0;
        if(a[0].x==0)
        for (int i = 0; i < 4; i++)
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }
        dx = 0;
        rotate = false;
        window.clear(Color::White);
        for (int i = 0; i < 4; i++)
        {
            tiles.setPosition(a[i].x * w, a[i].y * w);
            window.draw(tiles);
        }
        window.display();
    }
    return 0;
}
