#include <iostream>
#include <windows.h>

static int HOST_ERROR_CLICK_X = 987;
static int HOST_ERROR_CLICK_Y = 449;

static int CONTINUE_X = 1226;
static int CONTINUE_Y = 715;

void simulateMouseClickOnWnd(HWND targetWnd, int clickX, int clickY, int clickType)
{
    HWND foreWnd = GetForegroundWindow();
    DWORD windowThreadProcessId = GetCurrentThreadId();
    DWORD wakfuThreadID = GetWindowThreadProcessId(targetWnd, 0);

    AttachThreadInput(windowThreadProcessId, wakfuThreadID, true); // switch input to targetWnd and set focust on to it
    SetFocus(targetWnd);

    DWORD mousePos; // Im setting desired click position and send it throught lParam
    *(WORD *)&mousePos = clickX;
    *((WORD *)&mousePos + 1) = clickY;

    if (clickType == 0) //        LEFT CLICK
    {
        SendMessage(targetWnd, WM_MOUSEMOVE, 0, mousePos);
        SendMessage(targetWnd, WM_LBUTTONDOWN, MK_LBUTTON, mousePos);
        Sleep(50);
        SendMessage(targetWnd, WM_MOUSEMOVE, 0, mousePos);
        SendMessage(targetWnd, WM_LBUTTONUP, 0, mousePos);
    }
    else //                        RIGHT CLICK
    {
        SendMessage(targetWnd, WM_MOUSEMOVE, 0, mousePos);
        SendMessage(targetWnd, WM_RBUTTONDOWN, MK_RBUTTON, mousePos);
        Sleep(50);
        SendMessage(targetWnd, WM_MOUSEMOVE, 0, mousePos);
        SendMessage(targetWnd, WM_RBUTTONUP, 0, mousePos);
    }

    AttachThreadInput(windowThreadProcessId, wakfuThreadID, false);
    SetFocus(foreWnd);
}

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
    
    HWND GameHWND = NULL;
    GameHWND = FindWindowA("UnrealWindow", NULL);
    //SetForegroundWindow(GameHWND);

    MoveWindow(GetConsoleWindow(), 0, 50, 255, 100, TRUE);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    POINT P;
    GetCursorPos(&P);
    std::cout << "Cursor pos: x:" << P.x << " y:" << P.y << std::endl;

    std::cout << "Sleep 5 sec" << std::endl;
    Sleep(ToSec(5));

    for(int i = 1;;i++)
    {
        SwitchToThisWindow(GameHWND, false);
        Sleep(ToSec(1));
        std::cout << "done times: " << i << std::endl;
        LClickOnCoord(CONTINUE_X, CONTINUE_Y);
        Sleep(ToMin(18));
        SwitchToThisWindow(GameHWND, false);
        Sleep(ToSec(1));
        LClickOnCoord(HOST_ERROR_CLICK_X, HOST_ERROR_CLICK_Y);
        Sleep(ToSec(3));
        SwitchToThisWindow(GameHWND, false);
        Sleep(ToSec(1));
        LClickOnCoord(CONTINUE_X, CONTINUE_Y);
        Sleep(ToMin(1));
    }
    system("pause");
}