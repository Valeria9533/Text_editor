#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Commdlg.h"
#include "commctrl.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100
#define SetConsoleTitle SetConsoleTitleA

// Глобальные переменные:
HINSTANCE hInst;  
HINSTANCE g_hInst;
HIMAGELIST g_hImageList = NULL;
// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hWndMain;
HWND hWndB;
HWND hWndB1;
HWND hWndB2;
HWND hWndB3;
HWND hWndE;
HWND hWndWay;
HWND hWndToolBar;
HANDLE my_hIcon = LoadImage(0, _T("imagepath/starman1600.jpg"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

TCHAR szFile[MAX_PATH]; // буфер для имени файла

WNDCLASSEX wcex;

void coordinates(void); //прототип ф-ции
void ConfirmExit(void);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	InitCommonControls();

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringA(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringA(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  //  WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(my_hIcon));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW - 2);
	//wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(my_hIcon));

    return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   //РЕЕСТР

   //Адреса переменных, куда будет возвращен дескриптор, открываемого или создаваемого ключа.
   HKEY hkey; 
   HKEY x1;
   HKEY y1;
   HKEY w;
   HKEY h;

   DWORD  dwDisposition;  //Адрес переменной, куда будет возвращен один из следующих значений:
                          //Ключ не существует и был создан или ключ существует и был открыт без изменений.

   DWORD dwx1 = 0; //гориз. позиция окна
   DWORD dwy1 = 0; //верт. позиция окна
   DWORD dw_w; //ширина окна
   DWORD dw_h; //высота окна

   DWORD dwType1, dwSize1;
   DWORD dwType, dwSize;
   
   //Файл

   //чтение информации
   if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\My Company\\My Application"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hkey, &dwDisposition)
	   == ERROR_SUCCESS)
   {
	   dwType = REG_SZ;
	   dwSize = sizeof(szFile);
	   RegQueryValueEx(hkey, TEXT("LastFileName"), NULL, &dwType, (PBYTE)&szFile, &dwSize);
	   RegCloseKey(hkey);
   }  

   //Положение и размеры окна

   dwx1 = -1;  // Set the default values

   //чтение информации
   if (RegCreateKeyExA(HKEY_CURRENT_USER, TEXT("Software\\My Company\\My Application"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &x1, &dwDisposition)
	   == ERROR_SUCCESS)
   {
	   dwType1 = REG_DWORD;
	   dwSize1 = sizeof(DWORD);
	   RegQueryValueExA(x1, TEXT("X1"), NULL, &dwType1, (PBYTE)&dwx1, &dwSize1);
	   RegQueryValueExA(x1, TEXT("Y1"), NULL, &dwType1, (PBYTE)&dwy1, &dwSize1);
	   RegQueryValueExA(x1, TEXT("X2"), NULL, &dwType1, (PBYTE)&dw_w, &dwSize1);
	   RegQueryValueExA(x1, TEXT("Y2"), NULL, &dwType1, (PBYTE)&dw_h, &dwSize1);
	   RegCloseKey(x1);
   }

   if (dwx1 == -1) //если 1-й раз запускается
   {
	   dwx1 = 100;
	   dwy1 = 50;
	   dw_w = 800;
	   dw_h = 500;
   }
   hWndMain = CreateWindowA(szWindowClass, _T("Notebook"), WS_OVERLAPPEDWINDOW, //создаем главное окно (и название)
	   dwx1, dwy1, dw_w, dw_h, nullptr, nullptr, hInstance, nullptr);
  
if (!hWndMain)
   {
      return FALSE;
   }

//создание кнопок и окна для ввода текста
hWndB = CreateWindowEx(0, _T("BUTTON"), _T("Exit"), WS_CHILD | WS_VISIBLE, 100, 50, 100, 50, hWndMain, (HMENU)ID_EXIT, hInstance, 0);
hWndB1 = CreateWindowEx(0, _T("BUTTON"), _T("Save"), WS_CHILD | WS_VISIBLE, 100, 50, 100, 50, hWndMain, (HMENU)ID_SAVE, hInstance, 0);
hWndB2 = CreateWindowEx(0, _T("BUTTON"), _T("Save as"), WS_CHILD | WS_VISIBLE, 100, 50, 100, 50, hWndMain, (HMENU)ID_SAVEAS, hInstance, 0);
hWndB3 = CreateWindowEx(0, _T("BUTTON"), _T("Open"), WS_CHILD | WS_VISIBLE, 100, 50, 100, 50, hWndMain, (HMENU)ID_OPEN, hInstance, 0);
hWndE = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOHSCROLL, 0, 0, 100, 100, hWndMain, (HMENU)200, hInstance, 0);
hWndWay = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_AUTOHSCROLL, 90, 780, 100, 10, hWndMain, (HMENU)200, hInstance, 0);

show_file(szFile);

// Declare and initialize local constants.
const int ImageListID = 0;
const int numButtons = 13;
const int bitmapSize = 20;

const DWORD buttonStyles = BTNS_AUTOSIZE;

// Create the toolbar.
hWndToolBar = CreateWindowExA(0, TOOLBARCLASSNAME, NULL, WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
	hWndMain, NULL, g_hInst, NULL);

if (hWndToolBar == NULL)
return NULL;

 //Create the image list.
g_hImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
	ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
	numButtons, 0);

// Set the image list.
SendMessage(hWndToolBar, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)g_hImageList);

// Load the button images.
SendMessage(hWndToolBar, TB_LOADIMAGES, (WPARAM)IDB_STD_LARGE_COLOR, (LPARAM)HINST_COMMCTRL);

// Initialize button info.
TBBUTTON tbButtons[numButtons] =
{
	{ MAKELONG(STD_FILEOPEN,  ImageListID), ID_OPEN, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" Open "},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ MAKELONG(STD_FILESAVE, ImageListID), ID_SAVE, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" Save "},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ MAKELONG(STD_COPY, ImageListID), IDM_COPY, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" Copy "},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ MAKELONG(STD_PASTE, ImageListID), IDM_PASTE, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" Paste "},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ MAKELONG(STD_UNDO, ImageListID), IDM_REVERSE, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" Undo "},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ MAKELONG(STD_CUT, ImageListID), IDM_CUT, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" Cut "},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ MAKELONG(STD_HELP, ImageListID), IDM_ABOUT, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)" About "}
};

// Add buttons.
SendMessage(hWndToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
SendMessage(hWndToolBar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

// Resize the toolbar, and then show it.
SendMessageA(hWndToolBar, TB_AUTOSIZE, 0, 0);
ShowWindow(hWndToolBar, TRUE);

//return hWndToolbar;
   ShowWindow(hWndMain, nCmdShow);
   UpdateWindow(hWndMain);
   return TRUE;
}

BOOL Exit() //выход из программы
{
	if (MessageBox(hWndB, _T("Действительно выйти?"), _T("Exit"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		return TRUE; // Выход.
	}
	return FALSE;   // Отмена.
}

void ConfirmExit(void)
{
	TCHAR szFile[MAX_PATH];
	const int result = MessageBox(hWndB, _T("Вы хотите выйти без сохранения?"), _T("Exit"), MB_YESNO | MB_ICONQUESTION);
	switch (result)
	{
	case IDYES:
		coordinates();
		DestroyWindow(hWndMain);
		break;
	case IDNO:
		save_file(hWndMain);
		if (Exit() == TRUE)
			coordinates();
		else break;
			DestroyWindow(hWndMain);
		break;
	}
}

void show_file(TCHAR* way) //чтение файла и запись в окно
{
	FILE *f;
	f = fopen(way, "rb");
	if (!f)
	{
		SetWindowText(hWndE, "");
	}
	else
	{
		fseek(f, 0, SEEK_END); // переместить внутренний указатель в конец файла
		ftell(f); // вернуть текущее положение внутреннего указателя
		int _size = ftell(f);
		rewind(f); // установить внутренний указатель файла в начало
		TCHAR* data = new TCHAR[_size + 1];
		fread(data, _size, 1, f);
		data[_size] = 0; //завершить строку
		SetWindowText(hWndE, data);
		SetWindowText(hWndWay, szFile); //вывести путь к файлу
		fclose(f);
	}
}

OPENFILENAME ofn;			// структура стандартного диалогового окна
		
void open_file(HWND hWnd) //открытие файла
{
	// Инициализация OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; //идентифицирует окно, которое является владельцем
	ofn.lpstrFile = szFile; //указатель на буфер, для инициализации имени файла
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile); //определяет размер буфера, на который указывает параметр lpstrFile
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0CPP\0*.cpp\0H\0*.h\0"); //фильтр расширения файлов
	ofn.nFilterIndex = 1; //определяет выбранный в настоящий момент фильтр для типов файлов
	int ret = GetOpenFileName(&ofn);
	if (ret == 0) return;
	show_file(ofn.lpstrFile);
	//MessageBox(0, ofn.lpstrFile, _T("Путь к файлу"), MB_OKCANCEL);
}

void write_file(TCHAR* way) //запись в файл
{
	FILE *f;
	f = fopen(way, "w");
	int _size = GetWindowTextLengthA(hWndE);
	TCHAR *data = new TCHAR[_size + 1];
	GetWindowTextA(hWndE, data, _size);
	int ret = GetOpenFileName(&ofn);
	if (ret == 0) return;
	fwrite(data, _size, 1, f);
	fclose(f);
}

void save_file(HWND hWnd) //сохранение файла
{
	OPENFILENAME ofn;			// структура стандартного диалогового окна
	TCHAR szFile[100];			// буфер для имени файла

	// Инициализация OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; 
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0"); 
	ofn.nFilterIndex = 1;  
	GetSaveFileName(&ofn);
	write_file(ofn.lpstrFile);
}



//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, User!");

    switch (message)
    {
	case WM_CREATE:
	{
		HMENU hmenu = CreateMenu();
		HMENU hfile = CreateMenu();
		HMENU hinfo = CreateMenu();

		AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hfile, _T("File"));
		AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hinfo, _T("Info"));
		AppendMenu(hfile, MF_STRING, IDM_REVERSE, _T("Отмена Ctrl+Z"));
		AppendMenu(hfile, MF_STRING, IDM_LOAD, _T("Открыть Ctrl+O"));
		AppendMenu(hfile, MF_STRING, IDM_SAVE, _T("Сохранить Ctrl+S"));
		AppendMenu(hfile, MF_STRING, IDM_SAVEAS, _T("Сохранить как Ctrl+W"));
		AppendMenu(hfile, MF_STRING, IDM_COPY, _T("Копировать Ctrl+С"));
		AppendMenu(hfile, MF_STRING, IDM_PASTE, _T("Вставить Ctrl+V"));
		AppendMenu(hfile, MF_STRING, IDM_CUT, _T("Вырезать Ctrl+X"));
		AppendMenu(hfile, MF_STRING, IDM_OUT, _T("Выйти Alt+F4"));
		AppendMenu(hinfo, MF_STRING, IDM_ABOUT, _T("О программе"));

		SetMenu(hWnd, hmenu);
		break;
	}
	case WM_SIZE: //расположение кнопок и окна для текста
	{
		int dx = LOWORD(lParam);
		int dy = HIWORD(lParam);
		SetWindowPos(hWndB, 0, dx - 170, dy - 70, 90, 50, 0);
		SetWindowPos(hWndB1, 0, dx - 270, dy - 70, 90, 50, 0);
		SetWindowPos(hWndB2, 0, dx - 370, dy - 70, 90, 50, 0);
		SetWindowPos(hWndB3, 0, dx - 470, dy - 70, 90, 50, 0);
		SetWindowPos(hWndE, 0, 90, 60, dx - 170, dy - 150, 0);
		SetWindowPos(hWndWay, 0, 90, dy - 70, dx - 600, 20, 0);
		SendMessageA(hWndToolBar, TB_AUTOSIZE, 0, 0);
		break;
	}
	case WM_GETMINMAXINFO: //мин, макс размеры окна
	{
		MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
		POINT ptMin = { 746, 400 }, ptMax = { 1000, 750 };
		pInfo->ptMinTrackSize = ptMin;
		pInfo->ptMaxTrackSize = ptMax;
		return 0;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
              //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				MessageBox(hWnd, _T("Привет!\nЭта программа была создана 20.02.2020\nАвтор - Окромелидзе В.Г."), _T("О программе"), MB_OK);
				return TRUE;
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_EXIT:
				/*if (ConfirmExit() == TRUE)
				{
					coordinates();
					DestroyWindow(hWnd);
				}*/
				ConfirmExit();
				
			case ID_OPEN:
				open_file(hWnd);
				break;
			case ID_SAVE:
				save_file(hWnd);
				break;
			case ID_SAVEAS:
				save_file(hWnd);
				break;
			case IDM_REVERSE: //отмена
				keybd_event(VK_CONTROL, 0, 0, 0); //нажимаем
				keybd_event(0x5A, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); //отпускаем
				keybd_event(0x5A, 0, KEYEVENTF_KEYUP, 0);
				break;
			case IDM_LOAD: //открыть
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event(0x4F, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(0x4F, 0, KEYEVENTF_KEYUP, 0);
				open_file(hWnd);
				break;
			case IDM_SAVE: //сохранить
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event(0x53, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
				save_file(hWnd);
				break;
			case IDM_SAVEAS: //сохранить как
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event(0x57, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0);
				break;
			case IDM_COPY: //копировать
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event(0x43, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
				break;
			case IDM_PASTE: //вставить
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event(0x56, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
				break;
			case IDM_CUT: //вырезать
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event(0x58, 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(0x58, 0, KEYEVENTF_KEYUP, 0);
				break;
			case IDM_OUT: //выйти
				keybd_event(VK_MENU, 0, 0, 0);
				keybd_event(VK_F4, 0, 0, 0);
				keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW - 2);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
			TextOutA(hdc, 5, 61, greeting, _tcslen(greeting));
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CTLCOLOREDIT:
		if (IDC_CLREDIT == GetDlgCtrlID((HWND)lParam))
		{
			// Зеленый текст на черном фоне
			HDC dc = (HDC)wParam;
			SetBkMode(dc, TRANSPARENT);
			SetTextColor(dc, RGB(0, 255, 0));
			return (BOOL)GetStockObject(BLACK_BRUSH);
		}
		return FALSE;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_CLOSE:
		/*if (ConfirmExit() == TRUE)
		{
			coordinates();
			DestroyWindow(hWnd);
		}*/
		ConfirmExit();
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void coordinates(void)
{
	//Адреса переменных, куда будет возвращен дескриптор, открываемого или создаваемого ключа
	HKEY x1;
	HKEY hkey;

	DWORD  dwDisposition;  //Адрес переменной, куда будет возвращен один из следующих значений:
						   //Ключ не существует и был создан или ключ существует и был открыт без изменений.
	DWORD dwx1; 
	DWORD dwy1; 
	DWORD dwx2;
	DWORD dwy2; 
	DWORD dwType1, dwSize1;

	DWORD dwType, dwSize;

	RECT rt;

	//запись информации о файле
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\My Company\\My Application"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, &dwDisposition) ==
		ERROR_SUCCESS)
	{
		dwType = REG_SZ;
		dwSize = (_tcslen(szFile) + 1) * sizeof(TCHAR);
		RegSetValueEx(hkey, TEXT("LastFileName"), 0, dwType, (PBYTE)szFile, dwSize);
		RegCloseKey(hkey);
	}

	GetWindowRect(hWndMain, &rt);
	dwx1 = rt.left;
	dwy1 = rt.top;
	dwx2 = rt.right - rt.left;
	dwy2 = rt.bottom - rt.top;

	//запись информации о параметрах окна
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\My Company\\My Application"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &x1, &dwDisposition) ==
		ERROR_SUCCESS)
	{
		dwType1 = REG_DWORD;
		dwSize1 = sizeof(DWORD);
		RegSetValueExA(x1, TEXT("X1"), NULL, dwType1, (PBYTE)&dwx1, dwSize1);
		RegSetValueExA(x1, TEXT("Y1"), NULL, dwType1, (PBYTE)&dwy1, dwSize1);
		RegSetValueExA(x1, TEXT("X2"), NULL, dwType1, (PBYTE)&dwx2, dwSize1);
		RegSetValueExA(x1, TEXT("Y2"), NULL, dwType1, (PBYTE)&dwy2, dwSize1);
		RegCloseKey(x1);
	}
}

// Обработчик сообщений для окна "О программе".
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
