#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <time.h>

#include <iostream>

using namespace sf;
using namespace std;
const int M = 20;
const int N = 10;

int field[M][N] = {-1};//-1 = пустая клетка

int w = 34, score=0;

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

bool check()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return 0;
        else if (field[a[i].y][a[i].x]>-1)
            return 0;
    return 1;
}
int main()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            field[j][i] = -1; //-1 = пустая клетка
        }
    }
    srand(time(0));
    RenderWindow window(VideoMode(N * w, M * w), "Tetris");
    Texture t;
    t.loadFromFile("Paint/tiles.png" );
    Sprite tiles(t);
    int dx = 0, colorNum=0;
    colorNum = rand() % 7;
    int n = rand() % 7;
    bool rotate = false;
    float timer = 0, delay = 0.4;
    Clock clock;
    Font font;
    if (!font.loadFromFile("Paint/Arial.ttf"), 50)
    {
        cout << "error font loading";
    }
    else
    {
        cout << "font loaded";
    }
    
    while (window.isOpen())
    {
        string sc = "Score: " + to_string(score);
        Text text(sc, font, 50);
        text.setFillColor(Color::Black);
        
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
        if (Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.05;
        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!check())
        {
            for (int i = 0; i < 4; i++)
            {
                a[i] = b[i];
            }
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
            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    a[i] = b[i];
                }
            }
        }
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;//падение фигуры
            }
            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    field[b[i].y][b[i].x] = colorNum;//фигура упала, остается в field
                }
                colorNum = rand() % 7; //рандом цвета новой фигуры
                cout << colorNum << endl;
                n = rand() % 7; //рандом формы фигуры
                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }
            timer = 0;
        }

        int k = M - 1;//удаление полных строк
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j]!=-1)//если там не -1, то есть квадрат закрашен
                    count++;
                field[k][j] = field[i][j];
            }
            if (count < N)
                k--;
            else 
                score += 1;
            cout << score;
        }
        dx = 0;
        rotate = false;
        delay = 0.3;
        window.clear(Color::White);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == -1)
                    continue;
                tiles.setTextureRect(IntRect(field[i][j]*w, 0, w, w));
                tiles.setPosition(j * w, i * w);
                window.draw(tiles);
            }

        }
        for (int i = 0; i < 4; i++)
        {
            tiles.setTextureRect(IntRect(colorNum*w, 0, w, w));
            tiles.setPosition(a[i].x * w, a[i].y * w);
            window.draw(tiles);
        }
        window.draw(text);
        if (field[3][1] != -1)
        {
            cout << "Game over!";
            string gameend = "Game over!";
            Text text(gameend, font, 50);
            window.draw(text);

            string sc = to_string(score);
            Text text2(sc, font, 50);
            window.draw(text2);
            window.waitEvent(event) {

            }
        }
        window.display();
    }
    return 0;
}