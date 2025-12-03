#include <windows.h>
#include "resource1.h"
#include <time.h>



//地图
int g_arrBackgroud[20][10] = { 0 };
//俄罗斯方块
int g_arrElsfk[2][4] = { 0 };
//方块颜色
COLORREF g_blockColors[7] = {
    RGB(255, 0, 0),
    RGB(0, 255, 0),
    RGB(0, 0, 255),
    RGB(255, 255, 0),
    RGB(255, 0, 255),
    RGB(0, 255, 255),
    RGB(128, 0, 128) };
// 当前方块信息
int g_currentColor = 0;

//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//窗口绘图函数
void OnPaint(HDC hDC);
//绘制游戏界面
void DrawGame (HDC hDC);
// 绘制游戏区域边框
void DrawGameBorder(HDC hDC);
// 绘制游戏网格
void DrawGameGrid(HDC hDC);
//绘制方块
void DrawBlock(HDC hDc);
//随机生成俄罗斯方块
void Create();
// 绘制分数
void DrawScore(HDC hDC);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpreInstance, LPSTR lpCmdLine, int nCmdshow)
{//一、设计一个窗口
    TCHAR szAPPClassName[] = TEXT("elsfk");
    WNDCLASS wc = { 0 };
    wc.hbrBackground    = CreateSolidBrush(RGB(255, 255, 255));  //窗口颜色
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);           //加载光标
    wc.lpfnWndProc      = WindowProc;                            //窗口处理函数
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));  //加载图标
    wc.hInstance        = hInstance;                             //当前应用程序
    wc.style            = CS_HREDRAW | CS_VREDRAW;               //窗口类的类风格
    wc.lpszClassName = szAPPClassName;                           //窗口类型名字
    //二、注册窗口类
    RegisterClass(&wc);
    //三、创建窗口
    HWND hWnd = CreateWindow(
        szAPPClassName,                                          //窗口类型名
        TEXT("俄罗斯方块"),                                           //窗口的标题             
        WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,    //窗口的风格    
        200,
        100,                                                     //窗口的左上角坐标          
        500,
        630,                                                     //窗口的宽和高          
        NULL,                                                    //父窗口句柄            
        NULL,                                                    //菜单句柄
        hInstance,                                               //应用程序实例句柄
        NULL                                                     //附加信息                     
    );
    //四、显示窗口
    ShowWindow(hWnd, SW_SHOW);
    //五、更新窗口
    UpdateWindow(hWnd);
    //六、消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        //将消息分发给窗口处理函数
        DispatchMessage(&msg);

    }
    return 0;
}
//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hDC;
    switch (uMsg) {
    case WM_CREATE://窗口创建消息
        Create();
        break;
    case WM_PAINT:    //窗口绘图消息
        //开启绘图
        hDC =BeginPaint(hWnd, &ps);
        //绘图
        OnPaint(hDC);
        //结束绘图
        EndPaint(hWnd, &ps);
        break;
    case WM_CLOSE:                 //窗口关闭消息
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:                //窗口销毁消息
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//窗口绘图函数
void OnPaint(HDC hDC) {
    DrawGame(hDC);

}
// 绘制完整的游戏界面
void DrawGame(HDC hDC) {
    // 1. 绘制游戏区域边框
    DrawGameBorder(hDC);

    // 2. 绘制游戏网格
    DrawGameGrid(hDC);

    // 3. 绘制方块
    DrawBlock(hDC);

    // 4. 绘制分数
    DrawScore(hDC);
}

// 绘制游戏区域边框
void DrawGameBorder(HDC hDC) {
    // 绘制外边框（黑色）
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
    Rectangle(hDC, 20, 20, 320, 620);
    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);
}

// 绘制游戏网格
void DrawGameGrid(HDC hDC) {
    // 绘制网格线（浅灰色）
    HPEN hGridPen = CreatePen(PS_SOLID, 1, RGB(220, 220, 220));
    HPEN hOldPen = (HPEN)SelectObject(hDC, hGridPen);

    // 绘制垂直线（10列，所以11条线）
    for (int i = 0; i <= 10; i++) {
        MoveToEx(hDC, 20 + i * 30, 20, NULL);
        LineTo(hDC, 20 + i * 30, 620);
    }

    // 绘制水平线（20行，所以21条线）
    for (int i = 0; i <= 20; i++) {
        MoveToEx(hDC, 20, 20 + i * 30, NULL);
        LineTo(hDC, 320, 20 + i * 30);
    }

    SelectObject(hDC, hOldPen);
    DeleteObject(hGridPen);
}

//画方块
void DrawBlock(HDC hDC){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (g_arrBackgroud[i][j] == 1) {
                int x = 20 + j * 30 + 1;
                int y = 20 + i * 30 + 1;
                Rectangle(hDC, x, y, x + 28, y + 28);
            } 
        }
    }
}
// 绘制分数
void DrawScore(HDC hDC) {
    // 绘制分数标题
    TextOut(hDC, 340, 50, TEXT("分数:"), 3);

    // 绘制分数值
    TCHAR szScore[20];
    wsprintf(szScore, TEXT("%d"), 0);
    TextOut(hDC, 340, 80, szScore, lstrlen(szScore));

    // 绘制操作说明
    TextOut(hDC, 340, 150, TEXT("操作说明:"), 5);
    TextOut(hDC, 340, 180, TEXT("← → : 左右移动"), 10);
    TextOut(hDC, 340, 210, TEXT("↑ : 旋转方块"), 8);
    TextOut(hDC, 340, 240, TEXT("↓ : 加速下落"), 8);
    TextOut(hDC, 340, 270, TEXT("空格 : 直接落下"), 9);
}

//随机生成俄罗斯方块
void Create() {
    srand(time(NULL));
    int nIndex = rand() % 7;
    switch (nIndex) {
    case 0:
        g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 0, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
        g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
        break;
    case 1:
        g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 0, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 0;
        g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
        break;
    case 2:
        g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
        g_arrElsfk[1][0] = 0, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
        break;
    case 3:
        g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 0;
        g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
        break;
    case 4:
        g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
        g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
        break;
    case 5:
        g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
        g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
        break;
    case 6:
        g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 1;
        g_arrElsfk[1][0] = 0, g_arrElsfk[1][1] = 0, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
        break;
    }
    //复制到背景上
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            g_arrBackgroud[i][j+3] = g_arrElsfk[i][j];
        }
    }
}