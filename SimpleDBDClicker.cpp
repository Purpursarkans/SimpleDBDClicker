//!!!ONLY FOR 1920x1080p SCREEN!!!


#include <iostream>
#include <windows.h>

const int CENTER_X = 1080/2;
const int CENTER_Y = 1920/2;


const int HOST_ERROR_CLICK_X = 1436;
const int HOST_ERROR_CLICK_Y = 665;

const int START_GAME_X = 1822;
const int START_GAME_Y = 918;

const int CONTINUE_X = 1822;
const int CONTINUE_Y = 1012;

const int RED = 100;
const int GREEN = 10;
const int BLUE = 10;

const int MOVE_CONSOLE_X = 0;
const int MOVE_CONSOLE_Y = 50;
const int CONSOLE_WIDTH = 255;
const int CONSOLE_HEIGHT = 100;

int ToSec(int sec);
int ToMin(int min);

struct RGBPixel
{
    int r;
    int g;
    int b;
};

bool FindColor(int x, int y, int r, int g, int b, HDC hDC)
{
    COLORREF color;
    RGBPixel Pixel;

    for (int i = 7; i > 0; i--)
    {
        system("cls");
        std::cout << "time remaining: " << i << " sec" << std::endl;
        Sleep(ToSec(1));
    }
    color = GetPixel(hDC, x, y);
    Pixel = {GetRValue(color), GetGValue(color), GetBValue(color)};
    std::cout << Pixel.r << " " << Pixel.g << " " << Pixel.b << std::endl;
    Sleep(ToSec(1));

    if(Pixel.r > r && Pixel.g < g && Pixel.b < b)
    {
        Beep(100, 200);
        Sleep(ToSec(3));
        return true;
    }
    else
    {
        return false;
    }
}

void LClickOnCoord(int X, int Y)
{
    SetCursorPos(X, Y);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, X, Y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, X, Y, 0, 0);
}

int ToSec(int sec)
{
    return sec * 1000;
}

int ToMin(int min)
{
    return min * 60000;
}

void ClickColorCoord(int x, int y, int r, int g, int b, HWND hwnd, HDC hDC)
{
    if (FindColor(x, y, r, g, b, hDC))
    {
        SwitchToThisWindow(hwnd, true);
        Sleep(ToSec(1));
        LClickOnCoord(x, y);
        //SetCursorPos(CENTER_X, CENTER_X);
        Sleep(ToSec(1));
    }
}

int main()
{
    MoveWindow(GetConsoleWindow(), MOVE_CONSOLE_X, MOVE_CONSOLE_Y, CONSOLE_WIDTH, CONSOLE_HEIGHT, TRUE);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    HWND GameHWND = NULL;
    while (GameHWND == NULL)
    {
        std::cout << "Search UnrealWindow(DBD)" << std::endl;
        GameHWND = FindWindowA("UnrealWindow", NULL);
        if (GameHWND == NULL)
        {
            Sleep(ToSec(1));
        }
    }
    std::cout << "Found successful" << std::endl;
    HDC GameDC = GetDC(GameHWND);

    std::cout << "Sleep 3 sec" << std::endl;
    Sleep(ToSec(3));    

    for (;;)
    {
        ClickColorCoord(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y, RED, GREEN, BLUE, GameHWND, GameDC);
        ClickColorCoord(START_GAME_X, START_GAME_Y, RED, GREEN, BLUE, GameHWND, GameDC);
        ClickColorCoord(CONTINUE_X, CONTINUE_Y, RED, GREEN, BLUE, GameHWND, GameDC);

        /*
        if (FindColor(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y, RED, GREEN, BLUE, GameDC))
        {
            SwitchToThisWindow(GameHWND, true);
            Sleep(ToSec(1));
            LClickOnCoord(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y);
            Sleep(ToSec(1));
        }
        
        if (FindColor(START_GAME_X, START_GAME_Y, RED, GREEN, BLUE, GameDC))
        {
            SwitchToThisWindow(GameHWND, true);
            Sleep(ToSec(1));
            LClickOnCoord(START_GAME_X, START_GAME_Y);
            Sleep(ToSec(1));
        }

        if (FindColor(CONTINUE_X, CONTINUE_Y, RED, GREEN, BLUE, GameDC))
        {
            SwitchToThisWindow(GameHWND, true);
            Sleep(ToSec(1));
            LClickOnCoord(CONTINUE_X, CONTINUE_Y);
            Sleep(ToSec(1));
        }
        */
        
    }
    system("pause");
}


