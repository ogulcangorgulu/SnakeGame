#include <iostream>
#include <conio.h>  //_kbhit() and _getch
#include <ctime>// rand location
#include <windows.h> // for sleep function and colors
using namespace std;

//global varaibles
bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    //random fruit location based on width and height
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;


}
void gameDraw()
{

    system("cls");  //clear the screen
    cout << "\n\t~ Snake Game ~" << endl;
    for (int i = 0; i < width + 2; i++) {
        cout << char(254);
    }
    cout << endl;

    // i height, j width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) //print first element with '|'
            {
                cout << char(219);
            }
            if (i == y && j == x)   //print the head of snake on the middle
            {
                cout << char(223); // head
            }
            else if (i == fruitY && j == fruitX)    //print the food on random location
            {
                cout << char(5);
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++) { // going through every element of our tail
                    if (tailX[k] == j && tailY[k] == i) //j is current x coordinate that we are printing
                    {
                        cout << char(223); // body
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1) {
                cout << char(219);
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
    {
        cout << char(254);
    }
    cout << endl;
    cout << "Score " << score << endl;

}
void gameInput()
{
    if (_kbhit())   //if a character on the keyboard is pressed
    {
        switch (_getch())   //return ASCII value that was pressed
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;

        }
    }
}
void gameLogic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    // set first element 'o' to follow the head
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
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if we want to end the game when we hit the wall
    /* if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;*/

    // to go through the wall and continue the game
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
   

    for (int i = 0; i < nTail; i++)   // if we hit ourselves on the wall
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    
    if (x == fruitX && y == fruitY)
    {
       
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;   // if we eat the fruit
    }
}

int main()
{
    //setting console to blue
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);

    Setup();
    while (!gameOver)
    {
        gameDraw();
        gameInput();
        gameLogic();
        Sleep(30);  //andy, personally the game is really fast so I had to slow it down to 30 for my cpu.
    }
    cout << endl;
    cout << "Ahh! You did great!!" << endl;
    cout << "Your score was: " << score;
    cout << endl;
    return 0;
}
