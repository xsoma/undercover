#include "undercover.h"
HMODULE hack_module;

DWORD WINAPI OnDllAttachStartHeartbeat(LPVOID base)
{

    while (1)
    {
        // security is here
        if (g_debugger.is_security_breached()) {

            // uninject.
            exit(0);
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return TRUE;

}
t_Username GetUsername;
typedef bool (*t_Login)();
typedef bool (*t_Logout)();
typedef bool (*t_InjectModule)(char* moduleName);

int __stdcall DllMain(HMODULE self, ulong_t reason, void* reserved) {


    hack_module = self;

    if (reason == DLL_PROCESS_ATTACH) {
        HANDLE thread = CreateThread(nullptr, 0, Client::init, reserved, 0, nullptr);
        if (!thread)
            return 0;

        CloseHandle(thread);

      //  Client::init(reserved);

        return 1;
    }

    return 0;
}