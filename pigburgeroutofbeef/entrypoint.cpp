// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#define CreateThreadArg(func, arg) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)func, (LPVOID)arg, NULL, NULL);
#define CreateThreadMin(func) CreateThreadArg(func, NULL);
bool hooked = false;
FILE* _con;
DWORD WINAPI _init()
{

    //if (hooked)
    //    return 1;
    std::cout << "requesting to inject\n";
    AllocConsole();
    freopen_s(&_con, "CONOUT$", "w", stdout);
    cg::CG_DllEntry();

    while (!false) {

        Sleep(1000);
    }

    return 1;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        //DisableThreadLibraryCalls(hModule);

        if (!hooked) {
            //DWORD oldProtect;
            //VirtualProtect(GetModuleHandle(nullptr), 0xD536000, PAGE_EXECUTE_READWRITE, &oldProtect);
            ////hook* a = nullptr;

            ////a->install(&(PVOID&)WinMainCRTStartup_f, dll_init);

            std::thread(_init).detach();
            std::cout << "hello\n";
            //__asm {
            //    mov esi, _init;
            //    call esi;
            //    //add esp, 0;
            //}
            hooked = true;
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:

        //if (lpReserved != nullptr)
        //{
        //    break;
        //}
        //if (_con) {
        //    fclose(_con);
        //    FreeConsole();
        //}
        //MessageBoxA(NULL, "DLL_PROCESS_DETACH", "DLL_PROCESS_DETACH", 0);
        break;
    }
    return TRUE;
}

void cg::CG_DllEntry()
{
    std::cout << "hello form CG_DllEntry\n";
    fs::Log_Create(fs::GetExePath() + "\\pigburger_log.txt");

    if (!(DWORD)GetModuleHandleA("csgo.exe")) {
        
        fs::Log_Write(LOG_ERROR, "failure to find module 'csgo.exe'\n");
        return;
    }
    CG_Init();

}