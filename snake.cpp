#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
bool gameOver;
const int sirina = 50;
const int visina = 20;
int x, y, fX, fY, score;
int tailX[100], tailY[100];
int nTail;
enum z { STOP = 0, LEFT, RIGHT, UP, DOWN};
z dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = sirina / 2;
    y = visina / 2; fX = rand() % sirina;
    fY = rand() % visina;
    score = 0;
}

void Tabla()
{
    system("cls"); //system("clear");
    for (int i = 0; i < sirina+2; i++)
    cout << "#";
    cout << endl;
    for (int i = 0;i < visina; i++)
    {
        for (int j = 0; j < sirina; j++)
        {
            if (j == 0)
            cout << "#";
            if (i == y && j == x)
            cout << "O";
            else if (i == fY && j == fX)
            cout << "X";
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
            cout << " ";
            }
        if (j == sirina - 1)
        cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < sirina+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
    cout << "Za mog brata COKOVLADU";
    cout << endl;
    cout << "W,A,S,D za kontrolu\nX za izlaz";
}
void Kontrole()
{
    if (_kbhit())
    {
    switch (_getch())
        {
        case 'a':dir = LEFT;
        break;
        case 'd':dir = RIGHT;
        break;
        case 'w':dir = UP;
        break;
        case 's':dir = DOWN;
        break;
        case 'x':gameOver = true;
        break;
        }
    }
}

void Kretanje()
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
    case LEFT:x--;
    break;
    case RIGHT:x++;
    break;
    case UP:y--;
    break;
    case DOWN:y++;
    break;
    default:
    break;
    }
    if (x >= sirina) x = 0; else if (x < 0) x = sirina - 1;
    if (y >= visina) y = 0; else if (y < 0) y = visina - 1;
    for (int i = 0; i < nTail; i++)
    if (tailX[i] == x && tailY[i] == y)
    gameOver = true;
    if (x == fX && y == fY)
    {
        score += 10;
        fX = rand() % sirina;
        fY = rand() % visina;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Tabla();
        Kontrole();
        Kretanje();
        Sleep(60);//brzina moze da se menja (preporicujem od 10 do 100)
    }
    return 0;
}

