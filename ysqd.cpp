#include <bits/stdc++.h>
#include <windows.h>
#define CSGO "Counter-Strike: Global Offensive - Direct3D 9"
using namespace std;
int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE); // 隐藏控制台窗口
    HWND hWnd = FindWindow(NULL, CSGO);
    if (hWnd != NULL)
    {
        RECT csgo;
        GetClientRect(hWnd, &csgo);
        bool Genshin = false;      // 控制是否显示图片
        bool LastTime = false;     // 上一次的检测状态
        bool FullWhite = false;    // 是否全白
        const int numSamples = 50; // 要抽取的像素点数量
        POINT point;
        while (true)
        {
            FullWhite = true;
            HDC hdc = GetDC(hWnd);
            for (int i = 1; i <= numSamples; i++)
            {
                point.x = csgo.left + rand() % (csgo.right - csgo.left);
                point.y = csgo.top + rand() % (csgo.bottom - csgo.top);
                COLORREF pixelColor = GetPixel(hdc, point.x, point.y);
                if (pixelColor != RGB(255, 255, 255))
                {
                    FullWhite = false;
                    break;
                }
            }
            ReleaseDC(hWnd, hdc);
            if (!LastTime && FullWhite)
            {
                Genshin = true;                    // 设置显示图片标志
                keybd_event(VK_INSERT, 0, 0, 0);   // 按下 Insert 键
                Sleep(100);                        // 等待100ms
                keybd_event(VK_INSERT, 0, 2, 0);   // 松开 Insert 键
                Sleep(2000);                       // 等待2s
            }
            else if (LastTime && !FullWhite)
            {
                Genshin = false;
                keybd_event(VK_INSERT, 0, 0, 0);
                Sleep(100);
                keybd_event(VK_INSERT, 0, 2, 0);
                Sleep(2000);
            }
            LastTime = FullWhite;
        }
    }
    else
        printf("Not Found.\n");
    return 0;
}
