// Nightmare Creatures Save Editor.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Nightmare Creatures Save Editor.h"
#include <iostream>
#include <ostream>
#include <windowsx.h>
#include <commdlg.h>
#include <ShlObj.h>

//Compare first 256 bytes data with the loaded file to check if it is a NC save file or not.
const unsigned char _identifier[256] = {
    0x53, 0x43, 0x11, 0x01, 0x82, 0x6D, 0x82, 0x89, 0x82, 0x87, 0x82, 0x88,
    0x82, 0x94, 0x82, 0x8D, 0x82, 0x81, 0x82, 0x92, 0x82, 0x85, 0x81, 0x40,
    0x82, 0x62, 0x82, 0x92, 0x82, 0x85, 0x82, 0x81, 0x82, 0x94, 0x82, 0x95,
    0x82, 0x92, 0x82, 0x85, 0x82, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};


#define MAX_LOADSTRING 100

#define NC_SAVE_FILE_SIZE 0x180

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



const char* const LevelNames[]
{
    "Chelsea",
    "SpitalField",
    "Sewer Snake",
    "Thames Tunnel",
    "India Docks",
    "Highgate Cemetery",
    "Hampstead Heath",
    "Queenhite Docks",
    "City",
    "Smithfield",
    "Snowman",
    "Regents Canal",
    "London Zoo",
    "Marylebone",
    "Bloomsbury",
    "Pimlico",
    "Jose Manuel",
    "Westminster",
    "Westminster II",
    "The Roofs",
    "Map Select"
};

const char* const WeaponUpgrade_Names[]
{
    "Level 1",
    "Level 2",
    "Level 3",
    "Level 4"
};

const char* const CharacterNames[]
{
    "Ignatius",
    "Nadia"
};

const char* const ItemNames[]
{
    "Unused Item",
    "Proximity Mine",
    "Replusive Smoke",
    "Freeze",
    "Dynamite",
    "Flash",
    "Torch",
    "Multi Gun",
    "Berzerker",
    "Large Healing Ball",
    "Healing Ball",
    "Chaos",
    "Gun"
};

const char* const CheatNames[]
{
    "Level Select",
    "CD Track Select",
    "Unlimited",
    "Cut Body",
    "Reduce",
    "Play Monster",
    "Disable Combos",
    "Team Greetings",
    "Blur",
    "Debug"
};

const char* const DifficultyNames[]
{
    "Easy",
    "Hard"
};

const char* const SaveNumberNames[]
{
    "Save Number 1",
    "Save Number 2",
    "Save Number 3",
    "Save Number 4",
    "Save Number 5",
    "Save Number 6"
};


HWND LoadSaveButton;
HWND CloseSaveButton;
HWND CreateSaveButton, SaveNumberInput;
HWND ExitButton;
HWND SetDataButton;

HWND LivesInput, LevelInput, CharacterInput, HealthInput, WeaponLevelInput, DifficultyInput;

HWND ItemsInput[13] = {};

HWND CheatsInput[10] = {};

FILE* savefile = nullptr;

RECT rect;

NC_SaveFile savefile_data = {};
const NC_SaveFile c_savefile_data = {};

int Get_Savefile_DataSum(NC_SaveFile* _savefile)
{
    if (_savefile == nullptr)
        return 0xFFFFFFFF;

    int result = 0;

    unsigned char* tempbuf = new unsigned char[NC_SAVE_FILE_SIZE];
    memcpy(tempbuf, _savefile, NC_SAVE_FILE_SIZE);
    
    for (int i = 0; i < NC_SAVE_FILE_SIZE-5; ++i)
    {
        result += tempbuf[i];
    }

    delete[] tempbuf;
    return result;
}

void Fix_Savefile_DataSumValue(NC_SaveFile* _savefile)
{
    if (_savefile == nullptr)
        return;

    int result = Get_Savefile_DataSum(_savefile);
    _savefile->DataSumValue = result;
}

void Set_CanInput_RichText(bool caninput)
{
    if (caninput)
    {
        LONG style = GetWindowLongPtr(LivesInput, GWL_STYLE);
        SetWindowLongPtr(LivesInput, GWL_STYLE, style & ~WS_DISABLED);

        style = GetWindowLongPtr(SetDataButton, GWL_STYLE);
        SetWindowLongPtr(SetDataButton, GWL_STYLE, style & ~WS_DISABLED);

        style = GetWindowLongPtr(HealthInput, GWL_STYLE);
        SetWindowLongPtr(HealthInput, GWL_STYLE, style & ~WS_DISABLED);

        style = GetWindowLongPtr(LevelInput, GWL_STYLE);
        SetWindowLongPtr(LevelInput, GWL_STYLE, style & ~WS_DISABLED);

        style = GetWindowLongPtr(CharacterInput, GWL_STYLE);
        SetWindowLongPtr(CharacterInput, GWL_STYLE, style & ~WS_DISABLED);

        style = GetWindowLongPtr(WeaponLevelInput, GWL_STYLE);
        SetWindowLongPtr(WeaponLevelInput, GWL_STYLE, style & ~WS_DISABLED);

        style = GetWindowLongPtr(DifficultyInput, GWL_STYLE);
        SetWindowLongPtr(DifficultyInput, GWL_STYLE, style & ~WS_DISABLED);

        for (int i = 0; i < _ARRAYSIZE(ItemNames); ++i)
        {
            style = GetWindowLongPtr(ItemsInput[i], GWL_STYLE);
            SetWindowLongPtr(ItemsInput[i], GWL_STYLE, style & ~WS_DISABLED);
        }

        for (int i = 0; i < _ARRAYSIZE(CheatNames); ++i)
        {
            style = GetWindowLongPtr(CheatsInput[i], GWL_STYLE);
            SetWindowLongPtr(CheatsInput[i], GWL_STYLE, style & ~WS_DISABLED);
        }
    }
    else
    {
        LONG style = GetWindowLongPtr(LivesInput, GWL_STYLE);
        SetWindowLongPtr(LivesInput, GWL_STYLE, style | WS_DISABLED);   
        
        style = GetWindowLongPtr(SetDataButton, GWL_STYLE);
        SetWindowLongPtr(SetDataButton, GWL_STYLE, style | WS_DISABLED);

        style = GetWindowLongPtr(HealthInput, GWL_STYLE);
        SetWindowLongPtr(HealthInput, GWL_STYLE, style | WS_DISABLED);

        style = GetWindowLongPtr(LevelInput, GWL_STYLE);
        SetWindowLongPtr(LevelInput, GWL_STYLE, style | WS_DISABLED);

        style = GetWindowLongPtr(CharacterInput, GWL_STYLE);
        SetWindowLongPtr(CharacterInput, GWL_STYLE, style | WS_DISABLED);

        style = GetWindowLongPtr(WeaponLevelInput, GWL_STYLE);
        SetWindowLongPtr(WeaponLevelInput, GWL_STYLE, style | WS_DISABLED);

        style = GetWindowLongPtr(DifficultyInput, GWL_STYLE);
        SetWindowLongPtr(DifficultyInput, GWL_STYLE, style | WS_DISABLED);

        for (int i = 0; i < _ARRAYSIZE(ItemNames); ++i)
        {
            style = GetWindowLongPtr(ItemsInput[i], GWL_STYLE);
            SetWindowLongPtr(ItemsInput[i], GWL_STYLE, style | WS_DISABLED);
        }

        for (int i = 0; i < _ARRAYSIZE(CheatNames); ++i)
        {
            style = GetWindowLongPtr(CheatsInput[i], GWL_STYLE);
            SetWindowLongPtr(CheatsInput[i], GWL_STYLE, style | WS_DISABLED);
        }
    }
}

void ReDraw(HWND hwnd)
{
    RECT r;
    GetClientRect(hwnd, &r);
    InvalidateRect(hwnd, &r, true);
}

bool Close_Loaded_SaveGame(HWND hWnd)
{
    if (savefile != nullptr)
    {
        int result = fclose(savefile);
        if (!result)
        {
            Set_CanInput_RichText(false);
            savefile = nullptr;
            ReDraw(hWnd);
            return true;
        }
    }
    return false;
}

void SetSaveFile_Data(HWND hWnd)
{
    Set_CanInput_RichText(true);

    char* tempbuf = new char[50];

    ZeroMemory(tempbuf, 50);
    _itoa_s(savefile_data.lives, tempbuf, 50, 10);
    SetWindowTextA(LivesInput, tempbuf);

    ZeroMemory(tempbuf, 50);
    _itoa_s(savefile_data.health, tempbuf, 50, 10);
    SetWindowTextA(HealthInput, tempbuf);

    SendMessageA(LevelInput, CB_SELECTSTRING, 0L, (LPARAM)(LPSTR)LevelNames[savefile_data.level]);

    SendMessageA(WeaponLevelInput, CB_SELECTSTRING, 0L, (LPARAM)(LPSTR)WeaponUpgrade_Names[savefile_data.weapon_level]);

    SendMessageA(CharacterInput, CB_SELECTSTRING, 0L, (LPARAM)(LPSTR)CharacterNames[savefile_data.character]);

    SendMessageA(DifficultyInput, CB_SELECTSTRING, 0L, (LPARAM)(LPSTR)DifficultyNames[savefile_data.IsDifficultyHard]);

    SendMessageA(CheatsInput[0], BM_SETCHECK, (WPARAM)savefile_data.LevelSelect_Cheat, 0);
    SendMessageA(CheatsInput[1], BM_SETCHECK, (WPARAM)savefile_data.CDTrackSelect_Cheat, 0);
    SendMessageA(CheatsInput[2], BM_SETCHECK, (WPARAM)savefile_data.Unlimited_Cheat, 0);
    SendMessageA(CheatsInput[3], BM_SETCHECK, (WPARAM)savefile_data.CutBody_Cheat, 0);
    SendMessageA(CheatsInput[4], BM_SETCHECK, (WPARAM)savefile_data.Reduce_Cheat, 0);
    SendMessageA(CheatsInput[5], BM_SETCHECK, (WPARAM)savefile_data.PlayMonster_Cheat, 0);
    SendMessageA(CheatsInput[6], BM_SETCHECK, (WPARAM)savefile_data.DisableCombos_Cheat, 0);
    SendMessageA(CheatsInput[7], BM_SETCHECK, (WPARAM)savefile_data.TeamGreetings_Cheat, 0);
    SendMessageA(CheatsInput[8], BM_SETCHECK, (WPARAM)savefile_data.Blur_Cheat, 0);
    SendMessageA(CheatsInput[9], BM_SETCHECK, (WPARAM)savefile_data.Debug_Cheat, 0);



    for (int i = 0; i < 13; ++i)
    {
        ZeroMemory(tempbuf, 50);
        _itoa_s(savefile_data.items[i + 1], tempbuf, 50, 10);
        SetWindowTextA(ItemsInput[i], tempbuf);
    }


    delete[] tempbuf;

    ReDraw(hWnd);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NIGHTMARECREATURESSAVEEDITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NIGHTMARECREATURESSAVEEDITOR));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NIGHTMARECREATURESSAVEEDITOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NIGHTMARECREATURESSAVEEDITOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    GetClientRect(hWnd, &rect);

    LoadSaveButton = CreateWindowW(
        L"BUTTON",
        L"Load Save Game",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        50,
        150,
        25,
        hWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);

    CloseSaveButton = CreateWindowW(
        L"BUTTON",
        L"Close Save Game File",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        185,
        50,
        175,
        25,
        hWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);


    CreateSaveButton = CreateWindowW(
        L"BUTTON",
        L"Create Save Game",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        385,
        50,
        175,
        25,
        hWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);

    ExitButton = CreateWindowW(
        L"BUTTON",
        L"Exit",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        5,
        rect.bottom - 30,
        85,
        25,
        hWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);


    SetDataButton = CreateWindowW(
        L"BUTTON",
        L"Save Data",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_DISABLED,
        rect.right - 175,
        rect.bottom - 70,
        85,
        25,
        hWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);

    SaveNumberInput = CreateWindowW(
        L"COMBOBOX",
        L"0",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST,
        585,
        50,
        135,
        150,
        hWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);


    for (int i = 0; i < _ARRAYSIZE(SaveNumberNames); ++i)
    {
        SendMessageA(SaveNumberInput, 0x143, 0L, (LPARAM)(LPSTR)SaveNumberNames[i]);
    }
    SendMessageA(SaveNumberInput, CB_SELECTSTRING, 0L, (LPARAM)(LPSTR)SaveNumberNames[0]);

   LivesInput = CreateWindowW(
       L"EDIT",
       L"0",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | ES_NUMBER,
       rect.right/2+200,
       rect.bottom/4,
       25,
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   CreateWindowA(
       "STATIC",
       "Lives",
       WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
       rect.right / 2 + 200 - 70 - strlen("Lives"),
       rect.bottom / 4,
       90 + strlen("Lives"),
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);


   HealthInput = CreateWindowW(
       L"EDIT",
       L"0",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | ES_NUMBER,
       rect.right / 2 + 200,
       rect.bottom / 4 + 30,
       40,
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   CreateWindowA(
       "STATIC",
       "Health",
       WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
       rect.right / 2 + 200 - 70 - strlen("Health"),
       rect.bottom / 4 + 30,
       90 + strlen("Health"),
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   WeaponLevelInput = CreateWindowW(
       L"COMBOBOX",
       L"",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | CBS_DROPDOWNLIST,
       rect.right / 2 + 200,
       rect.bottom / 4 + 60,
       100,
       100,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   for (int i = 0; i < _ARRAYSIZE(WeaponUpgrade_Names); ++i)
   {
       SendMessageA(WeaponLevelInput, 0x143, 0L, (LPARAM)(LPSTR)WeaponUpgrade_Names[i]);
   }

   CreateWindowA(
       "STATIC",
       "Weapon Level",
       WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
       rect.right / 2 + 200 - 70 - strlen("Weapon Level") * 3,
       rect.bottom / 4 + 60,
       90 + strlen("Weapon Level"),
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   LevelInput = CreateWindowW(
       L"COMBOBOX",
       L"",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | CBS_DROPDOWNLIST,
       rect.right / 2 + 200,
       rect.bottom / 4 + 90,
       175,
       400,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   for (int i = 0; i < _ARRAYSIZE(LevelNames); ++i)
   {
       SendMessageA(LevelInput, 0x143, 0L, (LPARAM)(LPSTR)LevelNames[i]);
   }

   CreateWindowA(
       "STATIC",
       "Level",
       WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
       rect.right / 2 + 200 - 70 - strlen("Level"),
       rect.bottom / 4 + 90,
       90 + strlen("Level"),
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   CharacterInput = CreateWindowW(
       L"COMBOBOX",
       L"",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | CBS_DROPDOWNLIST,
       rect.right / 2 + 200,
       rect.bottom / 4 + 120,
       125,
       100,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   for (int i = 0; i < _ARRAYSIZE(CharacterNames); ++i)
   {
       SendMessageA(CharacterInput, 0x143, 0L, (LPARAM)(LPSTR)CharacterNames[i]);
   }

   CreateWindowA(
       "STATIC",
       "Character",
       WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
       rect.right / 2 + 200 - 70 - strlen("Character"),
       rect.bottom / 4 + 120,
       90 + strlen("Character"),
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);


   DifficultyInput = CreateWindowW(
       L"COMBOBOX",
       L"",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | CBS_DROPDOWNLIST,
       rect.right / 2 + 200,
       rect.bottom / 4 + 150,
       90,
       100,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   for (int i = 0; i < _ARRAYSIZE(DifficultyNames); ++i)
   {
       SendMessageA(DifficultyInput, 0x143, 0L, (LPARAM)(LPSTR)DifficultyNames[i]);
   }

   CreateWindowA(
       "STATIC",
       "Difficulty",
       WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
       rect.right / 2 + 200 - 70 - strlen("Difficulty"),
       rect.bottom / 4 + 150,
       90 + strlen("Difficulty"),
       20,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   int extray = 0;

   for (int i = 0; i < _ARRAYSIZE(ItemNames); ++i)
   {
       ItemsInput[i] = CreateWindowW(
           L"EDIT",
           L"0",
           WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | ES_NUMBER,
           rect.right/2,
           rect.bottom/4+extray,
           25,
           20,
           hWnd,
           NULL,
           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
           NULL);

       CreateWindowA(
           "STATIC",
           ItemNames[i],
           WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
           rect.right / 2 - 90 - strlen(ItemNames[i])*3,
           rect.bottom / 4 + extray,
           90+strlen(ItemNames[i])*3,
           20,
           hWnd,
           NULL,
           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
           NULL);

       extray += 30;
   }

   extray = 0;
    
   for (int i = 0; i < _ARRAYSIZE(CheatNames); ++i)
   {
       CheatsInput[i] = CreateWindowW(
           L"BUTTON",
           L"",
           WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_DISABLED | BS_AUTOCHECKBOX,
           rect.right/4,
           rect.bottom/4+extray,
           15,
           15,
           hWnd,
           NULL,
           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
           NULL);

       CreateWindowA(
           "STATIC",
           CheatNames[i],
           WS_TABSTOP | SS_SIMPLE | WS_VISIBLE | WS_CHILD,
           rect.right / 4 - 90 - strlen(CheatNames[i])*3,
           rect.bottom / 4 + extray,
           90+strlen(CheatNames[i])*3,
           20,
           hWnd,
           NULL,
           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
           NULL);

       extray += 30;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        if (lParam == (LPARAM)ExitButton)
        {
            if (savefile != nullptr)
            {
                fclose(savefile);
                savefile = nullptr;
            }
            PostQuitMessage(0);
        }

        if (lParam == (LPARAM)SetDataButton)
        {
            char* tempbuf = new char[50];

            ZeroMemory(tempbuf, 50);
            GetWindowTextA(LivesInput, tempbuf, 50);
            savefile_data.lives = atoi(tempbuf);

            ZeroMemory(tempbuf, 50);
            GetWindowTextA(HealthInput, tempbuf, 50);
            savefile_data.health = atoi(tempbuf);


            savefile_data.level = (short)ComboBox_GetCurSel(LevelInput);
            savefile_data.weapon_level = (short)ComboBox_GetCurSel(WeaponLevelInput);
            savefile_data.character = (short)ComboBox_GetCurSel(CharacterInput);
            savefile_data.IsDifficultyHard = (bool)ComboBox_GetCurSel(DifficultyInput);

            for (int i = 0; i < 13; ++i)
            {
                ZeroMemory(tempbuf, 50);
                GetWindowTextA(ItemsInput[i], tempbuf, 50);
                savefile_data.items[i + 1] = atoi(tempbuf);
            }
            savefile_data.LevelSelect_Cheat = SendMessageA(CheatsInput[0], BM_GETCHECK, 0, 0);
            savefile_data.CDTrackSelect_Cheat = SendMessageA(CheatsInput[1], BM_GETCHECK, 0, 0);
            savefile_data.Unlimited_Cheat = SendMessageA(CheatsInput[2], BM_GETCHECK, 0, 0);
            savefile_data.CutBody_Cheat = SendMessageA(CheatsInput[3], BM_GETCHECK, 0, 0);
            savefile_data.Reduce_Cheat = SendMessageA(CheatsInput[4], BM_GETCHECK, 0, 0);
            savefile_data.PlayMonster_Cheat = SendMessageA(CheatsInput[5], BM_GETCHECK, 0, 0);
            savefile_data.DisableCombos_Cheat = SendMessageA(CheatsInput[6], BM_GETCHECK, 0, 0);
            savefile_data.TeamGreetings_Cheat = SendMessageA(CheatsInput[7], BM_GETCHECK, 0, 0);
            savefile_data.Blur_Cheat = SendMessageA(CheatsInput[8], BM_GETCHECK, 0, 0);
            savefile_data.Debug_Cheat = SendMessageA(CheatsInput[9], BM_GETCHECK, 0, 0);


            Fix_Savefile_DataSumValue(&savefile_data);

            fseek(savefile, 0, 0);
            fwrite(&savefile_data, sizeof(char), NC_SAVE_FILE_SIZE, savefile);

            delete[] tempbuf;

            MessageBox(hWnd, L"Successfully saved new data for save file! Make sure to use \"Close Save Game File\" button before going back to the game.", L"Save Editor", MB_OK | MB_ICONINFORMATION);
        }

        if (lParam == (LPARAM)CreateSaveButton)
        {
            Close_Loaded_SaveGame(hWnd);

            char* tempbuf = new char[15];
            size_t itemindex = 0;
            char pathbuf[MAX_PATH] = {};
            char ncname[20] = {};

            GetWindowTextA(SaveNumberInput, tempbuf, 15);
            itemindex = SendMessageA(SaveNumberInput, CB_FINDSTRING, -1, (LPARAM)(LPSTR)tempbuf);

            delete[] tempbuf;

            sprintf_s(ncname, "NIGHTMARE.%d", itemindex);

            BROWSEINFOA BIA = {};
            BIA.hwndOwner = hWnd;
            BIA.lpszTitle = "Where do you want to create the new NC Save File?";
            BIA.ulFlags = BIF_NONEWFOLDERBUTTON;

            if (LPITEMIDLIST lid = SHBrowseForFolderA(&BIA))
            {
                if (SHGetPathFromIDListA(lid, pathbuf))
                {
                    sprintf_s(pathbuf, "%s\\%s", pathbuf, ncname);
                    memcpy_s(&savefile_data, sizeof(NC_SaveFile), &c_savefile_data, sizeof(NC_SaveFile));

                    fopen_s(&savefile, pathbuf, "rb+");
                    if (savefile)
                    {
                        int mbid = MessageBox(hWnd, L"A Nightmare Creatures save file with the same name was found in this directory. Do you wish to overwrite the original save file?", L"Existing save file found", MB_ICONQUESTION | MB_YESNO);
                        if (mbid == IDYES)
                        {
                            fseek(savefile, 0, 0);
                            fwrite(&savefile_data, sizeof(char), NC_SAVE_FILE_SIZE, savefile);
                            SetSaveFile_Data(hWnd);
                        }
                        else
                        {
                            Close_Loaded_SaveGame(hWnd);
                        }
                    }
                    else
                    {
                        fopen_s(&savefile, pathbuf, "wb+");
                        fwrite(&savefile_data, sizeof(char), NC_SAVE_FILE_SIZE, savefile);
                        SetSaveFile_Data(hWnd);
                    }
                }
            }
        }

        if (lParam == (LPARAM)LoadSaveButton)
        {
            bool ret = false;

            OPENFILENAMEA ofn = {};
            char szFile[260] = {};  

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "NC Save File\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileNameA(&ofn))
            {
                if (savefile != nullptr)
                {
                    Close_Loaded_SaveGame(hWnd);
                    ret = true;
                }

                fopen_s(&savefile, ofn.lpstrFile, "rb+");
                if (savefile != nullptr)
                {
                    size_t readitems = fread(&savefile_data, sizeof(char), NC_SAVE_FILE_SIZE, savefile);
                    if (readitems < NC_SAVE_FILE_SIZE)
                    {
                        MessageBox(hWnd, L"Failed to read save file. Size of file is too small.", L"Save Editor", MB_OK | MB_ICONERROR);
                        fclose(savefile);
                        savefile = nullptr;
                        if (ret)
                            ReDraw(hWnd);
                    }
                    else if (memcmp(savefile_data.identifier, _identifier, 256))
                    {
                        MessageBox(hWnd, L"Invalid Nightmare Creatures save file.", L"Save Editor", MB_OK | MB_ICONERROR);
                        fclose(savefile);
                        savefile = nullptr;
                        if (ret)
                            ReDraw(hWnd);
                    }
                    else
                    {
                        SetSaveFile_Data(hWnd);
                    }
                }
                else
                {
                    MessageBox(hWnd, L"File not found.", L"Save Editor", MB_OK | MB_ICONERROR);
                }
            }
        }

        if (lParam == (LPARAM)CloseSaveButton)
        {
            Close_Loaded_SaveGame(hWnd);
        }


        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;     
        case ID_USINGTOOL_CSF:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATINGSAVEFILES), hWnd, About);
            break;      
        case ID_USINGTOOL_HOWTOUSECHEATS:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_HOWTOUSECHEATS), hWnd, About);
            break;            
        case ID_USINGTOOL_SAVEFILES:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_SAVEFILES), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        HDC hdc = BeginPaint(hWnd, &ps);

        if (savefile == nullptr)
        {
            COLORREF ref = 0x000000FF; //Red Color
            SetTextColor(hdc, ref);
            TextOut(hdc, 10, 10, L"Save File Status: Not detected.", 31);
        }
        else
        {
            COLORREF ref = 0x0000FF00; //Green Color
            SetTextColor(hdc, ref);
            TextOut(hdc, 10, 10, L"Save File Status: Detected.", 27);
        }

        EndPaint(hWnd, &ps);

    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    
    }
    return 0;
}

// Message handler for about box.
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
