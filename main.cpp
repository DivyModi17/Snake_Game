#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

bool GameOver;
const int width = 50;
const int height = 20;
int x, y, fruitX, fruitY, obstacleX, obstacleY, score, highestScore;
int tailX[1000], tailY[1000];
int nTail;
char dir;

void Setup()
{
    GameOver = false;
    dir = 'L';
    x = width / 2;
    y = height / 2;
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;
    obstacleX = rand() % (width - 2) + 1;
    obstacleY = rand() % (height - 2) + 1;
    score = 0;

    nTail = 2;
    tailX[0] = x + 1;
    tailY[0] = y;
    tailX[1] = x + 2;
    tailY[1] = y;
}

void Draw()
{
    system("cls");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                cout << "#";
            }
            else if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "F";
            }
            else if (i == obstacleY && j == obstacleX)
            {
                cout << "X";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    cout << "Score: " << score << endl;
    cout << "Highest Score: " << highestScore << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != 'R')
                dir = 'L';
            break;
        case 'd':
            if (dir != 'L')
                dir = 'R';
            break;
        case 'w':
            if (dir != 'D')
                dir = 'U';
            break;
        case 's':
            if (dir != 'U')
                dir = 'D';
            break;
        case 'x':
            GameOver = true;
            break;
        }
    }
}

void Logic()
{

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case 'L':
        x--;
        break;
    case 'R':
        x++;
        break;
    case 'U':
        y--;
        break;
    case 'D':
        y++;
        break;
    }

    if (x > width - 1 || x < 0 || y > height - 1 || y < 0)
    {
        GameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            GameOver = true;
        }
    }

    if (x == obstacleX && y == obstacleY)
    {
        GameOver = true;
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
        obstacleX = rand() % (width - 2) + 1;
        obstacleY = rand() % (height - 2) + 1;
        nTail++; // Increase snake length
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    char playAgain;

    do
    {
        Setup();
        while (!GameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(70);
        }

        if (score > highestScore)
        {
            highestScore = score;
        }

        cout << "Game Over!" << endl;
        cout << "Your Score: " << score << endl;
        cout << "Highest Score: " << highestScore << endl;
        cout << "Do you want to play again? (y/n)";
        playAgain = '+';
        while (playAgain != 'Y' && playAgain != 'y' && playAgain != 'n' && playAgain != 'N')
        {
            playAgain = _getch();
            if (playAgain == 'n' || playAgain == 'N')
            {
                return 0;
            }
        }

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
