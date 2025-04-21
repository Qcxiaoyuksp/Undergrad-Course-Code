#include <windows.h>
#include <cmath>
#include <stdio.h>

#pragma comment(lib, "user32.lib") // 添加此行
#pragma comment(lib, "gdi32.lib") // 添加此行
// 定义控件ID
#define IDC_INPUT1 1001
#define IDC_RESULT 1002
#define IDC_NUM0   1003
#define IDC_NUM1   1004
#define IDC_NUM2   1005
#define IDC_NUM3   1006
#define IDC_NUM4   1007
#define IDC_NUM5   1008
#define IDC_NUM6   1009
#define IDC_NUM7   1010
#define IDC_NUM8   1011
#define IDC_NUM9   1012
#define IDC_ADD    1013
#define IDC_SUB    1014
#define IDC_MUL    1015
#define IDC_DIV    1016
#define IDC_SQRT   1017
#define IDC_CLEAR  1018
#define IDC_EQUAL  1019

// 全局变量
HWND hwndInput1, hwndResult;
HWND hwndNum0, hwndNum1, hwndNum2, hwndNum3, hwndNum4, hwndNum5, hwndNum6, hwndNum7, hwndNum8, hwndNum9;
HWND hwndAdd, hwndSub, hwndMul, hwndDiv, hwndSqrt, hwndClear, hwndEqual;

// 消息处理函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // 创建输入框
            hwndInput1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                                      10, 10, 200, 20, hwnd, (HMENU)IDC_INPUT1, NULL, NULL);
            hwndResult = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                      10, 40, 200, 20, hwnd, (HMENU)IDC_RESULT, NULL, NULL);
                                      
            // 创建数字按钮
            hwndNum0 = CreateWindow("BUTTON", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    10, 70, 40, 40, hwnd, (HMENU)IDC_NUM0, NULL, NULL);
            hwndNum1 = CreateWindow("BUTTON", "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    60, 70, 40, 40, hwnd, (HMENU)IDC_NUM1, NULL, NULL);
            hwndNum2 = CreateWindow("BUTTON", "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    110, 70, 40, 40, hwnd, (HMENU)IDC_NUM2, NULL, NULL);
            hwndNum3 = CreateWindow("BUTTON", "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    160, 70, 40, 40, hwnd, (HMENU)IDC_NUM3, NULL, NULL);
            hwndNum4 = CreateWindow("BUTTON", "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    10, 120, 40, 40, hwnd, (HMENU)IDC_NUM4, NULL, NULL);
            hwndNum5 = CreateWindow("BUTTON", "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    60, 120, 40, 40, hwnd, (HMENU)IDC_NUM5, NULL, NULL);
            hwndNum6 = CreateWindow("BUTTON", "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    110, 120, 40, 40, hwnd, (HMENU)IDC_NUM6, NULL, NULL);
            hwndNum7 = CreateWindow("BUTTON", "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    160, 120, 40, 40, hwnd, (HMENU)IDC_NUM7, NULL, NULL);
            hwndNum8 = CreateWindow("BUTTON", "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    10, 170, 40, 40, hwnd, (HMENU)IDC_NUM8, NULL, NULL);
            hwndNum9 = CreateWindow("BUTTON", "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    60, 170, 40, 40, hwnd, (HMENU)IDC_NUM9, NULL, NULL);

            // 创建运算符按钮
            hwndAdd = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   110, 170, 40, 40, hwnd, (HMENU)IDC_ADD, NULL, NULL);
            hwndSub = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   160, 170, 40, 40, hwnd, (HMENU)IDC_SUB, NULL, NULL);
            hwndMul = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   10, 220, 40, 40, hwnd, (HMENU)IDC_MUL, NULL, NULL);
            hwndDiv = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   60, 220, 40, 40, hwnd, (HMENU)IDC_DIV, NULL, NULL);
            hwndSqrt = CreateWindow("BUTTON", "√", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    110, 220, 40, 40, hwnd, (HMENU)IDC_SQRT, NULL, NULL);
            hwndClear = CreateWindow("BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     160, 220, 40, 40, hwnd, (HMENU)IDC_CLEAR, NULL, NULL);
            hwndEqual = CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     10, 270, 190, 40, hwnd, (HMENU)IDC_EQUAL, NULL, NULL);
            
            break;
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                double operand1, result;
                char buffer[256];

                switch (LOWORD(wParam)) {
                    case IDC_NUM0:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"0");
                        break;
                    case IDC_NUM1:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"1");
                        break;
                    case IDC_NUM2:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"2");
                        break;
                    case IDC_NUM3:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"3");
                        break;
                    case IDC_NUM4:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"4");
                        break;
                    case IDC_NUM5:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"5");
                        break;
                    case IDC_NUM6:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"6");
                        break;
                    case IDC_NUM7:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"7");
                        break;
                    case IDC_NUM8:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"8");
                        break;
                    case IDC_NUM9:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)"9");
                        break;
                    case IDC_ADD:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)" + ");
                        break;
                    case IDC_SUB:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)" - ");
                        break;
                    case IDC_MUL:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)" * ");
                        break;
                    case IDC_DIV:
                        SendMessage(hwndInput1, EM_REPLACESEL, TRUE, (LPARAM)" / ");
                        break;
                    case IDC_SQRT:
                        GetWindowText(hwndInput1, buffer, sizeof(buffer));
                        operand1 = atof(buffer);
                        result = sqrt(operand1);
                        sprintf(buffer, "%f", result);
                        SetWindowText(hwndResult, buffer);
                        break;
                    case IDC_CLEAR:
                        SetWindowText(hwndInput1, "");
                        SetWindowText(hwndResult, "");
                        break;
                    case IDC_EQUAL:
                        GetWindowText(hwndInput1, buffer, sizeof(buffer));
                        // 进行计算
                        break;
                }
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 创建窗口
    const char* className = "Calculator";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndClass;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = className;
    if (!RegisterClass(&wndClass)) {
        MessageBox(NULL, "窗口注册失败！", "错误", MB_ICONERROR);
        return 0;
    }
    hwnd = CreateWindow(className, "计算器", WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, 250, 370,
                        NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) {
        MessageBox(NULL, "窗口创建失败！", "错误", MB_ICONERROR);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

