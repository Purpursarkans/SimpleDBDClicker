#include <iostream>
#include <windows.h>

static int HOST_ERROR_CLICK_X = 987;
static int HOST_ERROR_CLICK_Y = 449;

static int CONTINUE_X = 1226;
static int CONTINUE_Y = 715;

int ToSec(int sec);
int ToMin(int min);

struct RGBPixel
{
    int r;
    int g;
    int b;
};

void FindColor(int x, int y, int r, int g, int b, HDC DC,int j)
{
    COLORREF color;
    RGBPixel Pixel;
    while (!(Pixel.r > r && Pixel.g < g && Pixel.b < b))
    {
        color = GetPixel(DC, x, y);
        Pixel = {GetRValue(color), GetGValue(color), GetBValue(color)};
        std::cout << Pixel.r << " " << Pixel.g << " " << Pixel.b << std::endl;
        Sleep(ToSec(1));
        for(int i = 15; i > 0; i--)
        {
            system("cls");
            std::cout << "done: " << j << " time" << std::endl;
            std::cout << "time remaining: " << i << " sec" << std::endl;
            Sleep(ToSec(1));
        }
    }
    Beep(100, 200);
    Sleep(ToSec(3));
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
    HWND GameHWND = NULL;
    GameHWND = FindWindowA("UnrealWindow", NULL);
    HDC GameDC = GetDC(GameHWND);

    MoveWindow(GetConsoleWindow(), 0, 50, 255, 100, TRUE);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    POINT P;
    GetCursorPos(&P);
    std::cout << "Cursor pos: x:" << P.x << " y:" << P.y << std::endl;

    std::cout << "Sleep 5 sec" << std::endl;
    Sleep(ToSec(5));

    for (int i = 0;; i++)
    {
        FindColor(1290, 714, 100, 10, 10, GameDC, i);
        SwitchToThisWindow(GameHWND, false);
        Sleep(ToSec(1));
        LClickOnCoord(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y);
        Sleep(ToSec(1));
        LClickOnCoord(CONTINUE_X, CONTINUE_Y);
        Sleep(ToSec(1));
    }
    system("pause");
}