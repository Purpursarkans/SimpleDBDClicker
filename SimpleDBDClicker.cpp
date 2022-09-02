#include <iostream>
#include <windows.h>

static int HOST_ERROR_CLICK_X = 987;
static int HOST_ERROR_CLICK_Y = 449;

static int CONTINUE_X = 1226;
static int CONTINUE_Y = 715;

void LClickOnCoord(int X, int Y)
{
    SetCursorPos(X, Y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, X, Y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, X, Y, 0, 0);
}

int ToSec(int sec)
{
    return sec*1000;
}

int ToMin(int min)
{
    return min*60000;
}

int main()
{
    MoveWindow(GetConsoleWindow(), 0, 50, 255, 100, TRUE);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    std::cout << "Sleep 10 sec on start" << std::endl;

    Sleep(ToSec(10));

    POINT P;
    GetCursorPos(&P);
    std::cout << "Cursor pos: x:" << P.x << " y:" << P.y << std::endl;

    Sleep(ToSec(5));

    for(int i = 1;;i++)
    {
        std::cout << "done times: " << i << std::endl;
        LClickOnCoord(CONTINUE_X, CONTINUE_Y);
        Sleep(ToMin(18));
        LClickOnCoord(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y);
        Sleep(ToSec(3));
        LClickOnCoord(CONTINUE_X, CONTINUE_Y);
        Sleep(ToMin(1));
    }
    system("pause");
}