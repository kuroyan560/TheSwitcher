#include "DxLib.h"
#include "SystemMain.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	SystemMain system;
	if (system.init()) {
		system.main();
	}
	system.end();

	return 0;
}