#include <iostream>
#include <windows.h>

static int HOST_ERROR_CLICK_X = 1014;
static int HOST_ERROR_CLICK_Y = 450;

static int CONTINUE_X = 1290;
static int CONTINUE_Y = 714;

static int RED = 150;
static int GREEN = 10;
static int BLUE = 10;

int ToSec(int sec);
int ToMin(int min);

struct RGBPixel
{
    int r;
    int g;
    int b;
};

bool FindColor(int x, int y, int r, int g, int b, HDC DC)
{
    COLORREF color;
    RGBPixel Pixel;

    for (int i = 7; i > 0; i--)
    {
        system("cls");
        std::cout << "time remaining: " << i << " sec" << std::endl;
        Sleep(ToSec(1));
    }
    color = GetPixel(DC, x, y);
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

int main()
{
    MoveWindow(GetConsoleWindow(), 0, 50, 255, 100, TRUE);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    HWND GameHWND = NULL;
    while (GameHWND == NULL)
    {
        std::cout << "Search UnrealWindow(DBD)" << std::endl;
        GameHWND = FindWindowA("UnrealWindow", NULL);
        Sleep(ToSec(1));
    }
    std::cout << "Found successful" << std::endl;
    HDC GameDC = GetDC(GameHWND);

    std::cout << "Sleep 3 sec" << std::endl;
    Sleep(ToSec(3));

    POINT P;
    GetCursorPos(&P);
    std::cout << "Cursor pos: x:" << P.x << " y:" << P.y << std::endl;

    std::cout << "Sleep 3 sec" << std::endl;
    Sleep(ToSec(3));

    for (int i = 0;; i++)
    {
        if (FindColor(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y, RED, GREEN, BLUE, GameDC))
        {
            SwitchToThisWindow(GameHWND, true);
            Sleep(ToSec(1));
            LClickOnCoord(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y);
            Sleep(ToSec(1));
        }
        if (FindColor(CONTINUE_X, CONTINUE_Y, RED, GREEN, BLUE, GameDC))
        {
            SwitchToThisWindow(GameHWND, true);
            Sleep(ToSec(1));
            LClickOnCoord(CONTINUE_X, CONTINUE_Y);
            Sleep(ToSec(1));
        }
        
    }
    system("pause");
}