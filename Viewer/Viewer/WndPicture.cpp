
#include "framework.h"
#include "WndPicture.h"

LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void RegisterPictureWnd( HINSTANCE hInst )
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProcChild;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInst;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = L"PictureWnd";
    wcex.hIconSm        = NULL;
    RegisterClassExW(&wcex);
}


void OnPaint( HWND hWnd, HDC hdc )
{
    HBITMAP hBmp = (HBITMAP)LoadImage( NULL, L"sample.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
    if ( hBmp ) {

        BITMAP bmp;
        GetObject( hBmp, sizeof( BITMAP ), &bmp );

        HDC hdc2 = CreateCompatibleDC( hdc );
        HBITMAP hOldBmp = (HBITMAP)SelectObject( hdc2, hBmp );
        BitBlt( hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdc2, 0, 0, SRCCOPY );
 
        SelectObject( hdc2, hOldBmp );
        DeleteDC( hdc2 );
        DeleteObject( hBmp );
    }
}


LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...

            OnPaint( hWnd, hdc );

            EndPaint(hWnd, &ps);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
