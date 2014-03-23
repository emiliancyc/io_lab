// MusicBank.cpp: Okreœla punkt wejœcia dla aplikacji.
//

#include "stdafx.h"
#include "MusicBank.h"

#define MAX_LOADSTRING 100

// Zmienne globalne:
HINSTANCE hInst;								// bie¿¹ce wyst¹pienie
TCHAR szTitle[MAX_LOADSTRING];					// Tekst paska tytu³u
TCHAR szWindowClass[MAX_LOADSTRING];			// nazwa klasy okna g³ównego

// Przeka¿ dalej deklaracje funkcji do³¹czonych w tym module kodu:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: W tym miejscu umieœæ kod.
	MSG msg;
	HACCEL hAccelTable;

	// Zainicjuj ci¹gi globalne
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MUSICBANK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Wykonaj inicjacje aplikacji:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MUSICBANK));

	// G³ówna pêtla wiadomoœci:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasê okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MUSICBANK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW-1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MUSICBANK);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojœcie wyst¹pienia i tworzy okno g³ówne
//
//   KOMENTARZE:
//
//        W tej funkcji dojœcie wyst¹pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyœwietlane okno g³ówne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Przechowuj dojœcie wyst¹pienia w zmiennej globalnej

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomoœci dla okna g³ównego.
//
//  WM_COMMAND	- przetwarzaj menu aplikacji
//  WM_PAINT	- Rysuje okno g³ówne
//  WM_DESTROY	- wyœlij komunikat zakoñczenia i wróæ
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUTBOX_AUTOR: //o autorze
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX_AUTOR), hWnd, About);
			break;
		case IDM_ABOUTBOX_PROG: //o programie
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX_PROG), hWnd, About);
			break;
		case IDM_SZUKAJ: //wyszukiwanie
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SZUKAJ), hWnd, About);
			break;
		case IDM_IMPORT: //import z pliku
			DialogBox(hInst, MAKEINTRESOURCE(IDD_IMPORT), hWnd, About);
			break;
		case IDM_EXPORT: //export pliku
			DialogBox(hInst, MAKEINTRESOURCE(IDD_EXPORT), hWnd, About);
			break;
		case IDM_DODAJ: //dodaj do listy
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DODAJ), hWnd, About);
			break;
		case IDM_USUN: //usuwa z listy
			DialogBox(hInst, MAKEINTRESOURCE(IDD_USUN), hWnd, About);
			break;
		case IDM_EDYTUJ: //edytuje wpis
			if (DialogBox(hInst, MAKEINTRESOURCE(IDD_EDYTUJ), hWnd, About))
				DialogBox(hInst, MAKEINTRESOURCE(IDD_EDYTUJ2), hWnd, About);
			break;
		case IDM_EXIT: //wyjscie
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: W tym miejscu dodaj jakikolwiek kod rysuj¹cy...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Obs³uga wiadomoœci dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
