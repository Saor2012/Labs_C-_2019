#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define _UNICODE
#define UNICODE
#define LEN 255
//#define BUFFER_SIZE 4096

//#include "pch.h"
#include <iostream>
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <winuser.h>
#include <direct.h>
#include <tchar.h>
#include <winioctl.h>
//#include <TCHAR.h>
//#include <String.h>
#include <wchar.h>
#include <winbase.h>
#include <direct.h>
#include <TCHAR.h>
#include "Source.h"
#include <strsafe.h>

using namespace std;

void CreateNewProcess() {
	int isWaitTypeProcess = 0;
	cout << "Choose type process work (wait for end process): \n" << "1. Wait to process work\n" << "0. Ignore wait to process work and continue" << endl;
	do {
		cout << "Enter integer value: ";
		cin >> isWaitTypeProcess;
		//cout << (isWaitTypeProcess != 0) << (isWaitTypeProcess != 1) << !((isWaitTypeProcess != 0) || (isWaitTypeProcess != 1)) << endl;
		if ((isWaitTypeProcess != 0) && (isWaitTypeProcess != 1)) {
			int answer;
			cout << "Use this answer as 0 value? (1. Yes; 0. No)";
			cin >> answer;
			if (answer == 1) {
				isWaitTypeProcess = 0;
				break;
			}
		}
	} while (!((isWaitTypeProcess == 0) || (isWaitTypeProcess == 1)));
	//cout << "Wait: " << isWaitTypeProcess << endl;
	int err;
	//switch (isWaitTypeProcess) {
	//	case 0: if (!(err = _spawnl(P_WAIT, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64", NULL))) { //P_WAIT, 0
	//			printf("Error code %d\n", err);
	//			system("pause");
	//		} else cout << "AIDA64 lauched successfuly!\n" << endl;
	//		break;
	//	case 1: if (!(err = _spawnl(0, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64", NULL))) { //P_WAIT, 0
	//			printf("Error code %d\n", err);
	//			system("pause");
	//		} else cout << "AIDA64 lauched successfuly!\n" << endl;
	//		break;
	//	default: break;
	//}
	if (isWaitTypeProcess == 0) {
		if (!(err = _spawnl(P_WAIT, "C:\\Windows\\System32\\cmd.exe", "Test run cmd", NULL))) { //P_WAIT, 0
			printf("Error code %d\n", err);
			system("pause");
		} else cout << "cmd lauched successfuly!\n" << endl;
		//system("pause");
	} else if (isWaitTypeProcess == 1) {
		if (!(err = _spawnl(0, "C:\\Windows\\System32\\cmd.exe", "Test run cmd", NULL))) { //P_WAIT, 0
			printf("Error code %d\n", err);
			system("pause");
		} else cout << "cmd lauched successfuly!\n" << endl;
	} else {}
	char* cmdline = new char[1000];
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	int processPriority = 0, processNewTerminal = 0, terminalColors[2] = {};
	string terminalTitle = "";
	LPCTSTR projectWorkDirection = NULL;
	TCHAR lpTerminalTitle[MAX_PATH];
	char* strBuffer = new char[LEN]; //SetConsoleTitle()
	do {
		if (isWaitTypeProcess == -1) break;
		if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose type work ", MB_YESNO) == IDYES) {
			int priority = 0;
			if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose some process components ", MB_YESNO) == IDYES) {

				cout << "Change priority class?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					int value;
					cout << "Choose priority class for process: \n" << " 0. Value: NORMAL_PRIORITY_CLASS\n" << " 1. Value: IDLE_PRIORITY_CLASS\n" <<
						" 2. Value: BELOW_NORMAL_PRIORITY_CLASS\n" << " 3. Value: ABOVE_NORMAL_PRIORITY_CLASS\n" << " 4. Value: HIGH_PRIORITY_CLASS\n";
					cin >> value;
					switch (value) {
						case 0: processPriority = NORMAL_PRIORITY_CLASS;
							break;
						case 1: processPriority = IDLE_PRIORITY_CLASS;
							break;
						case 2: processPriority = BELOW_NORMAL_PRIORITY_CLASS;
							break;
						case 3: processPriority = ABOVE_NORMAL_PRIORITY_CLASS;
							break;
						case 4: processPriority = HIGH_PRIORITY_CLASS;
							break;
						default: processPriority = NORMAL_PRIORITY_CLASS;
							break;
					}
				}
				cout << "Priority: " << processPriority << endl;

				cout << "Create new console?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) processNewTerminal = CREATE_NEW_CONSOLE;
				cout << "New console: " << processNewTerminal << endl;

				cout << "Change terminal color?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					int value;
					cout << "Choose terminal color style: \n" << " 0. Value: fontColor - white\n" << " 1. Value: fontColor - Light Blue\n" <<
						" 2. Value: fontColor - Light Green\n";
					cin >> value;
					switch (value) {
						case 0: terminalColors[0] = 7;
							break;
						case 1: terminalColors[0] = 11;
							break;
						case 2: terminalColors[0] = 10;
							break;
						default: terminalColors[0] = 8;
							break;
					}
					//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
				} else terminalColors[0] = -1;
				cout << "Terminal color: " << terminalColors[0] << endl;

				cout << "Set title for new console?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					cout << "Enter title: ";
					cin >> strBuffer;
					if (strBuffer != "") {
						terminalTitle = strBuffer;
						//StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
					}
				}
				//LPCWSTR lpTerminalTitle = (LPCWSTR)terminalTitle.c_str();
				//SetConsoleTitle(lpTerminalTitle);


				cout << "Set cureent work directory?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					cout << "Enter title: ";
					cin >> strBuffer;
					if (strBuffer != "") {
						projectWorkDirection = (LPCTSTR)strBuffer;
					}
				}
				char oldDir[LEN];  //LPWSTR oldDir[BUFFER_SIZE]
				if (!GetCurrentDirectory(LEN, (LPWSTR)oldDir))
					cerr << "Error getting current work directory: #" << GetLastError();
				cout << "Current work directory: " << oldDir << '\n';
				//const char* newDir = R"(C:\path\to\directory\)";
				if (!SetCurrentDirectory(projectWorkDirection))
					cerr << "Error setting current directory: #" << GetLastError();
				cout << "Set current directory to " << projectWorkDirection << '\n';

			}

			if (CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, (processPriority != 0 ? processPriority : NULL) | (processNewTerminal != 0 ? processNewTerminal : NULL), NULL, NULL, &si, &pi)) { //"C:\\Windows\\System32\\cmd.exe"
				cout << "Process " << "C:\\Windows\\System32\\cmd.exe " << " created" << endl;
				cout << "A value that can be used to identify a process." << pi.dwProcessId << endl;
				cout << "A value that can be used to identify a thread. " << pi.dwThreadId << endl;
				if (!SetConsoleTitle(lpTerminalTitle)) {
					_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
				} else {
					_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
				}
				printf("\n\nEnd of work function CreateProcess\n");

				ExitProcess(NO_ERROR);
			} else
				printf("\n\nError working function CreateProcess!!!\n");

			cout << "Set title for new console?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) {
				cout << "Enter title: ";
				cin >> strBuffer;
				if (strBuffer != "") {
					//terminalTitle = strBuffer;
					StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
				}
			} //StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), terminalTitle);
			if (!SetConsoleTitle(lpTerminalTitle)) {
				_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
			} else {
				_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
		}
		int isContinue = 0;
		cout << "\n Try again?(Any. Yes; 0. No)";
		cin >> isContinue;
		switch (isContinue) {
			case 0: isWaitTypeProcess = -1;
				break;
			default: cout << "Start new process" << endl;
		}
		//if (true) isWaitTypeProcess = -1;
	} while (isWaitTypeProcess == -1);
	delete[]strBuffer;
	delete[]cmdline;
	/*if (isWaitTypeProcess == 0)
		if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose type work ", MB_YESNO) == IDYES) {
			int priority = 0;
			if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose some process components ", MB_YESNO) == IDYES) {

				cout << "Change priority class?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					int value;
					cout << "Choose priority class for process: \n" << " 0. Value: NORMAL_PRIORITY_CLASS\n" << " 1. Value: IDLE_PRIORITY_CLASS\n" <<
						" 2. Value: BELOW_NORMAL_PRIORITY_CLASS\n" << " 3. Value: ABOVE_NORMAL_PRIORITY_CLASS\n" << " 4. Value: HIGH_PRIORITY_CLASS\n";
					cin >> value;
					switch (value) {
						case 0: processPriority = NORMAL_PRIORITY_CLASS;
							break;
						case 1: processPriority = IDLE_PRIORITY_CLASS;
							break;
						case 2: processPriority = BELOW_NORMAL_PRIORITY_CLASS;
							break;
						case 3: processPriority = ABOVE_NORMAL_PRIORITY_CLASS;
							break;
						case 4: processPriority = HIGH_PRIORITY_CLASS;
							break;
						default: processPriority = NORMAL_PRIORITY_CLASS;
							break;
					}
				}
				cout << "Priority: " << processPriority << endl;

				cout << "Create new console?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) processNewTerminal = CREATE_NEW_CONSOLE;
				cout << "New console: " << processNewTerminal << endl;

				cout << "Change terminal color?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					int value;
					cout << "Choose terminal color style: \n" << " 0. Value: fontColor - white\n" << " 1. Value: fontColor - Light Blue\n" <<
						" 2. Value: fontColor - Light Green\n";
					cin >> value;
					switch (value) {
						case 0: terminalColors[0] = 7;
							break;
						case 1: terminalColors[0] = 11;
							break;
						case 2: terminalColors[0] = 10;
							break;
						default: terminalColors[0] = 8;
							break;
					}
					//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
				} else terminalColors[0] = -1;
				cout << "Terminal color: " << terminalColors[0] << endl;

				cout << "Set title for new console?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					cout << "Enter title: ";
					cin >> strBuffer;
					if (strBuffer != "") {
						terminalTitle = strBuffer;
						//StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
					}
				}
				//LPCWSTR lpTerminalTitle = (LPCWSTR)terminalTitle.c_str();
				//SetConsoleTitle(lpTerminalTitle);


				cout << "Set cureent work directory?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					cout << "Enter title: ";
					cin >> strBuffer;
					if (strBuffer != "") {
						projectWorkDirection = (LPCTSTR)strBuffer;
					}
				}
				char oldDir[LEN];  //LPWSTR oldDir[BUFFER_SIZE]
				if (!GetCurrentDirectory(LEN, (LPWSTR)oldDir))
					cerr << "Error getting current work directory: #" << GetLastError();
				cout << "Current work directory: " << oldDir << '\n';
				//const char* newDir = R"(C:\path\to\directory\)";
				if (!SetCurrentDirectory(projectWorkDirection))
					cerr << "Error setting current directory: #" << GetLastError();
				cout << "Set current directory to " << projectWorkDirection << '\n';

			}

			if (CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, (processPriority != 0 ? processPriority : 0) | (processNewTerminal != 0 ? processNewTerminal : 0), NULL, NULL, &si, &pi)) { //"C:\\Windows\\System32\\cmd.exe"
				cout << "Process " << "C:\\Windows\\System32\\cmd.exe " << " created" << endl;
				cout << "A value that can be used to identify a process." << pi.dwProcessId << endl;
				cout << "A value that can be used to identify a thread. " << pi.dwThreadId << endl;
				if (!SetConsoleTitle(lpTerminalTitle)) {
					_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
				} else {
					_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
				}
				printf("\n\nEnd of work function CreateProcess\n");

				ExitProcess(NO_ERROR);
			} else
				printf("\n\nError working function CreateProcess!!!\n");

			cout << "Set title for new console?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) {
				cout << "Enter title: ";
				cin >> strBuffer;
				if (strBuffer != "") {
					//terminalTitle = strBuffer;
					StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
				}
			} //StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), terminalTitle);
			if (!SetConsoleTitle(lpTerminalTitle)) {
				_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
			} else {
				_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
		}
	delete[]strBuffer;
	delete[]cmdline;*/
}

int main() {
	setlocale(LC_ALL, "ukr");
	// Test 1 system() and _spawnl()
	/*cout << "Test 1" << endl;
	if (system(NULL)) cout << "Command system() work" << endl;
	else {
		cout << "Throw exception at code " << GetLastError() << endl;
		exit(1);
	}
	cout << "Run for terminal \'ipconfig /all\' \n" << endl;
	int a = system("ipconfig /all");
	cout << "Result value " << a << endl;
	int err;
	if (!(err = _spawnl(P_WAIT, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64",NULL))) { //P_WAIT, 0
		printf("Error code %d\n", err);
		system("pause");
	} else cout << "AIDA64 lauched successfuly!\n" << endl;*/

	// Test 2
	/*cout << "Test 2" << endl;
	int isWaitTypeProcess = 0;
	cout << "Choose type process work (wait for end process work): \n" << "1. Wait to process work\n" << "0. Ignore wait to process work and continue" << endl;
	do {
		cout << "Enter integer value: ";
		cin >> isWaitTypeProcess;
		cout << (isWaitTypeProcess != 0) << (isWaitTypeProcess != 1) << !((isWaitTypeProcess != 0)||(isWaitTypeProcess != 1)) << endl;
		if ((isWaitTypeProcess != 0) && (isWaitTypeProcess != 1)) {
			int answer;
			cout << "Use this answer as 0 value? (1. Yes; 0. No)";
			cin >> answer;
			if (answer == 1) {
				isWaitTypeProcess = 0;
				break;
			}
		}
	} while (!((isWaitTypeProcess == 0) || (isWaitTypeProcess == 1)));
	cout << "Wait: " << isWaitTypeProcess << endl;
	int err;
	//switch (isWaitTypeProcess) {
	//	case 0: if (!(err = _spawnl(P_WAIT, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64", NULL))) { //P_WAIT, 0
	//			printf("Error code %d\n", err);
	//			system("pause");
	//		} else cout << "AIDA64 lauched successfuly!\n" << endl;
	//		break;
	//	case 1: if (!(err = _spawnl(0, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64", NULL))) { //P_WAIT, 0
	//			printf("Error code %d\n", err);
	//			system("pause");
	//		} else cout << "AIDA64 lauched successfuly!\n" << endl;
	//		break;
	//	default: break;
	//}
	if (isWaitTypeProcess == 0) {
		if (!(err = _spawnl(P_WAIT, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64", NULL))) { //P_WAIT, 0
			printf("Error code %d\n", err);
			system("pause");
		} else cout << "AIDA64 lauched successfuly!\n" << endl;
		//system("pause");
	} else if (isWaitTypeProcess == 1) {
		if (!(err = _spawnl(0, "D:\\AIDA64\\AIDA64 Extreme\\aida64.exe", "Test run aida64", NULL))) { //P_WAIT, 0
			printf("Error code %d\n", err);
			system("pause");
		} else cout << "AIDA64 lauched successfuly!\n" << endl;
	} else {}

	char* cmdline = new char[1000];
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	if (isWaitTypeProcess == 0)
		if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose type work ", MB_YESNO) == IDYES) {
			if (CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) { //"C:\\Windows\\System32\\cmd.exe"
				cout << "Process " << "C:\\Windows\\System32\\cmd.exe " << " created" << endl;
				cout << "A value that can be used to identify a process." << pi.dwProcessId << endl;
				cout << "A value that can be used to identify a thread. " << pi.dwThreadId << endl;

				printf("\n\nEnd of work function CreateProcess\n");

				ExitProcess(NO_ERROR);
			} else
				printf("\n\nError working function CreateProcess!!!\n");
		}

	delete[]cmdline;
	//ExitProcess(&pi);*/
	// Test 3
	/*cout << "Test 3" << endl;
	int isWaitTypeProcess = 0;
	cout << "Choose type process work (wait for end process work): \n" << "1. Wait to process work\n" << "0. Ignore wait to process work and continue" << endl;
	do {
		cout << "Enter integer value: ";
		cin >> isWaitTypeProcess;
		//cout << (isWaitTypeProcess != 0) << (isWaitTypeProcess != 1) << !((isWaitTypeProcess != 0) || (isWaitTypeProcess != 1)) << endl;
		if ((isWaitTypeProcess != 0) && (isWaitTypeProcess != 1)) {
			int answer;
			cout << "Use this answer as 0 value? (1. Yes; 0. No)";
			cin >> answer;
			if (answer == 1) {
				isWaitTypeProcess = 0;
				break;
			}
		}
	} while (!((isWaitTypeProcess == 0) || (isWaitTypeProcess == 1)));
	cout << "Wait: " << isWaitTypeProcess << endl;

	char* cmdline = new char[1000];
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	int processPriority, processNewTerminal, terminalColors[2];
	string terminalTitle;
	LPCTSTR projectWorkDirection = NULL;
	char* strBuffer = new char[LEN]; //SetConsoleTitle()
	if (isWaitTypeProcess == 0)
		if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose type work ", MB_YESNO) == IDYES) {
			if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose some process components ", MB_YESNO) == IDYES) {
				int priority;
				cout << "Change priority class?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					int value;
					cout << "Choose priority class for process: \n" << " 0. Value: NORMAL_PRIORITY_CLASS\n" << " 1. Value: IDLE_PRIORITY_CLASS\n" <<
						" 2. Value: BELOW_NORMAL_PRIORITY_CLASS\n" << " 3. Value: ABOVE_NORMAL_PRIORITY_CLASS\n" << " 4. Value: HIGH_PRIORITY_CLASS\n";
					cin >> value;
					switch (value) {
						case 0: processPriority = NORMAL_PRIORITY_CLASS;
							break;
						case 1: processPriority = IDLE_PRIORITY_CLASS;
							break;
						case 2: processPriority = BELOW_NORMAL_PRIORITY_CLASS;
							break;
						case 3: processPriority = ABOVE_NORMAL_PRIORITY_CLASS;
							break;
						case 4: processPriority = HIGH_PRIORITY_CLASS;
							break;
						default: processPriority = NORMAL_PRIORITY_CLASS;
							break;
					}
				}
				cout << "Priority: " << processPriority << endl;

				cout << "Create new console?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) processNewTerminal = CREATE_NEW_CONSOLE;
				cout << "New console: " << processNewTerminal << endl;

				cout << "Change terminal color?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					int value;
					cout << "Choose terminal color style: \n" << " 0. Value: fontColor - white\n" << " 1. Value: fontColor - Light Blue\n" <<
						" 2. Value: fontColor - Light Green\n";
					cin >> value;
					switch (value) {
						case 0: terminalColors[0] = 7;
							break;
						case 1: terminalColors[0] = 11;
							break;
						case 2: terminalColors[0] = 10;
							break;
						default: terminalColors[0] = 8;
							break;
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
				} else terminalColors[0] = -1;
				cout << "Terminal color: " << terminalColors[0] << endl;

				cout << "Set title for new console?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					cout << "Enter title: ";
					cin >> strBuffer;
					if (strBuffer != "") {
						terminalTitle = strBuffer;
						//StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
					}
				}
				//LPCWSTR lpTerminalTitle = (LPCWSTR)terminalTitle.c_str();
				//SetConsoleTitle(lpTerminalTitle);


				cout << "Set cureent work directory?(1. Yes; Any. No)";
				cin >> priority;
				if (priority != 0 && priority != 1) {
					priority = 0;
				}
				if (priority == 1) {
					cout << "Enter title: ";
					cin >> strBuffer;
					if (strBuffer != "") {
						projectWorkDirection = (LPCTSTR)strBuffer;
					}
				}
				char oldDir[LEN];  //LPWSTR oldDir[BUFFER_SIZE]
				if (!GetCurrentDirectory(LEN, (LPWSTR)oldDir))
					cerr << "Error getting current work directory: #" << GetLastError();
				cout << "Current work directory: " << oldDir << '\n';
				//const char* newDir = R"(C:\path\to\directory\)";
				if (!SetCurrentDirectory(projectWorkDirection))
					cerr << "Error setting current directory: #" << GetLastError();
				cout << "Set current directory to " << projectWorkDirection << '\n';

			}

			if (CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, (processPriority != 0 ? processPriority : 0) | (processNewTerminal != 0 ? processNewTerminal : 0), NULL, NULL, &si, &pi)) { //"C:\\Windows\\System32\\cmd.exe"
				cout << "Process " << "C:\\Windows\\System32\\cmd.exe " << " created" << endl;
				cout << "A value that can be used to identify a process." << pi.dwProcessId << endl;
				cout << "A value that can be used to identify a thread. " << pi.dwThreadId << endl;
				if (!SetConsoleTitle(lpTerminalTitle)) {
					_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
				} else {
					_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
				}
				printf("\n\nEnd of work function CreateProcess\n");

				ExitProcess(NO_ERROR);
			} else
				printf("\n\nError working function CreateProcess!!!\n");
		}
	delete[]strBuffer;
	delete[]cmdline;

	//ExitProcess(&pi);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
	//cout << "Color 111" << endl;*/

	//Test 4
	/*cout << "Test 4" << endl;
	int isWaitTypeProcess = 0;
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	cout << "Choose type process work (wait for end process work): \n" << "1. Wait to process work\n" << "0. Ignore wait to process work and continue" << endl;
	do {
		cout << "Enter integer value: ";
		cin >> isWaitTypeProcess;
		//cout << (isWaitTypeProcess != 0) << (isWaitTypeProcess != 1) << !((isWaitTypeProcess != 0) || (isWaitTypeProcess != 1)) << endl;
		if ((isWaitTypeProcess != 0) && (isWaitTypeProcess != 1)) {
			int answer;
			cout << "Use this answer as 0 value? (1. Yes; 0. No)";
			cin >> answer;
			if (answer == 1) {
				isWaitTypeProcess = 0;
				break;
			}
		}
	} while (!((isWaitTypeProcess == 0) || (isWaitTypeProcess == 1)));
	cout << "Wait: " << ((isWaitTypeProcess == 1) ? "true" : "false") << endl;
	int err, exitLoopKey;
	do {
		if (isWaitTypeProcess == 1) {
			if (!(err = _spawnl(P_WAIT, "C:\Windows\system32\cmd.exe", "Test run cmd", NULL))) { //P_WAIT, 0
				printf("Error code %d\n", err);
				system("pause");
			} else cout << "AIDA64 lauched successfuly with wait to end!\n" << endl;
			//system("pause");
		} else if (isWaitTypeProcess == 1) {
			if (!(err = _spawnl(0, "C:\Windows\system32\cmd.exe", "Test run cmd", NULL))) { //P_WAIT, 0
				printf("Error code %d\n", err);
				system("pause");
			} else cout << "AIDA64 lauched successfuly without wait to end!\n" << endl;
		} else {}
		if (MessageBox(NULL, L" Work again (Yes)\n Exit (No)\n", L"Retry? ", MB_YESNO) == IDYES) {
			exitLoopKey = 0;
			continue;
		} else exitLoopKey = -1;


	} while (exitLoopKey != -1);
	if (CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) { //"C:\\Windows\\System32\\cmd.exe"
		cout << "Process " << "C:\\Windows\\System32\\cmd.exe " << " created" << endl;
		cout << "A value that can be used to identify a process." << pi.dwProcessId << endl;
		//cout << "A value that can be used to identify a thread. " << pi.dwThreadId << endl;
		cout << "A value that can be used to handle a new process." << pi.hProcess << endl;
		//cout << "A value that can be used to handle a new process at thread." << pi.hThread << endl;
		//cout << "A value that can be used to copy console name." << si.lpTitle << endl;
		//cout << "A value that can be used to copy console name." << si.dwFlags << endl;
		//cout << "A value that can be used to identify a process: " << pi.dwProcessId << endl;

		//printf("A value that can be used to handle a new process: %s", pi.hProcess);
		printf("A value that can be used to copy console name: %s\n", si.lpTitle);
		_tprintf(_T("A value that can be used to copy console name: %s\n"), si.lpTitle);
		printf("A value that can be used to copy console name: %s\n", si.dwFlags);
		_tprintf(_T("A value that can be used to copy console name: %s\n"), si.dwFlags);


		printf("\n\nEnd of work function CreateProcess\n");

		ExitProcess(NO_ERROR);
	} else
		printf("\n\nError working function CreateProcess!!!\n");*/

//	string terminalTitle;
	/*TCHAR terminalTitle[MAX_PATH];
	TCHAR lpTerminalTitle[MAX_PATH];
	int priority;
	char* strBuffer = new char[LEN];
	cout << "Set title for new console?(1. Yes; Any. No)";
	cin >> priority;
	if (priority != 0 && priority != 1) {
		priority = 0;
	}
	if (priority == 1) {
		cout << "Enter title: ";
		cin >> strBuffer;
		if (strBuffer != "") {
			//terminalTitle = strBuffer;
			StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
		}
	}
	//StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), terminalTitle);
	if (!SetConsoleTitle(lpTerminalTitle)) {
		_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
	} else {
		_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
	}
	delete[]strBuffer;*/

	/*TCHAR szOldTitle[MAX_PATH];
	TCHAR szNewTitle[MAX_PATH];

	// Save current console title.

	if (GetConsoleTitle(szOldTitle, MAX_PATH)) {
	   // Build new console title string.

		StringCchPrintf(szNewTitle, MAX_PATH, TEXT("TEST: %s"), szOldTitle);

		// Set console title to new title
		if (!SetConsoleTitle(szNewTitle)) {
			_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
			return 1;
		} else {
			_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
		}
	}*/
	/*//TCHAR* oldDir = new TCHAR[BUFFER_SIZE];
	char oldDir[BUFFER_SIZE];  //LPWSTR oldDir[BUFFER_SIZE]
	if (!GetCurrentDirectory(BUFFER_SIZE, (LPWSTR)oldDir))
		std::cerr << "Error getting current work directory: #" << GetLastError();
	cout << "Current work directory: " << oldDir << '\n';*/
	//Full version
	/*int isWaitTypeProcess = 0;
	cout << "Choose type process work (wait for end process work): \n" << "1. Wait to process work\n" << "0. Ignore wait to process work and continue" << endl;
	do {
		cout << "Enter integer value: ";
		cin >> isWaitTypeProcess;
		//cout << (isWaitTypeProcess != 0) << (isWaitTypeProcess != 1) << !((isWaitTypeProcess != 0) || (isWaitTypeProcess != 1)) << endl;
		if ((isWaitTypeProcess != 0) && (isWaitTypeProcess != 1)) {
			int answer;
			cout << "Use this answer as 0 value? (1. Yes; 0. No)";
			cin >> answer;
			if (answer == 1) {
				isWaitTypeProcess = 0;
				break;
			}
		}
	} while (!((isWaitTypeProcess == 0) || (isWaitTypeProcess == 1)));
	//cout << "Wait: " << isWaitTypeProcess << endl;

	char* cmdline = new char[1000];
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	int processPriority, processNewTerminal, terminalColors[2];
	string terminalTitle;
	LPCTSTR projectWorkDirection = NULL;
	TCHAR lpTerminalTitle[MAX_PATH];
	char* strBuffer = new char[LEN]; //SetConsoleTitle()
	if (isWaitTypeProcess == 0)
	if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose type work ", MB_YESNO) == IDYES) {
		if (MessageBox(NULL, L" Continue work (Yes)\n Exit (No)\n", L"Choose some process components ", MB_YESNO) == IDYES) {
			int priority;
			cout << "Change priority class?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) {
				int value;
				cout << "Choose priority class for process: \n" << " 0. Value: NORMAL_PRIORITY_CLASS\n" << " 1. Value: IDLE_PRIORITY_CLASS\n" <<
					" 2. Value: BELOW_NORMAL_PRIORITY_CLASS\n" << " 3. Value: ABOVE_NORMAL_PRIORITY_CLASS\n" << " 4. Value: HIGH_PRIORITY_CLASS\n";
				cin >> value;
				switch (value) {
					case 0: processPriority = NORMAL_PRIORITY_CLASS;
						break;
					case 1: processPriority = IDLE_PRIORITY_CLASS;
						break;
					case 2: processPriority = BELOW_NORMAL_PRIORITY_CLASS;
						break;
					case 3: processPriority = ABOVE_NORMAL_PRIORITY_CLASS;
						break;
					case 4: processPriority = HIGH_PRIORITY_CLASS;
						break;
					default: processPriority = NORMAL_PRIORITY_CLASS;
						break;
				}
			}
			cout << "Priority: " << processPriority << endl;

			cout << "Create new console?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) processNewTerminal = CREATE_NEW_CONSOLE;
			cout << "New console: " << processNewTerminal << endl;

			cout << "Change terminal color?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) {
				int value;
				cout << "Choose terminal color style: \n" << " 0. Value: fontColor - white\n" << " 1. Value: fontColor - Light Blue\n" <<
					" 2. Value: fontColor - Light Green\n";
				cin >> value;
				switch (value) {
					case 0: terminalColors[0] = 7;
						break;
					case 1: terminalColors[0] = 11;
						break;
					case 2: terminalColors[0] = 10;
						break;
					default: terminalColors[0] = 8;
						break;
				}
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
			} else terminalColors[0] = -1;
			cout << "Terminal color: " << terminalColors[0] << endl;

			cout << "Set title for new console?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) {
				cout << "Enter title: ";
				cin >> strBuffer;
				if (strBuffer != "") {
					terminalTitle = strBuffer;
					//StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
				}
			}
			//LPCWSTR lpTerminalTitle = (LPCWSTR)terminalTitle.c_str();
			//SetConsoleTitle(lpTerminalTitle);


			cout << "Set cureent work directory?(1. Yes; Any. No)";
			cin >> priority;
			if (priority != 0 && priority != 1) {
				priority = 0;
			}
			if (priority == 1) {
				cout << "Enter title: ";
				cin >> strBuffer;
				if (strBuffer != "") {
					projectWorkDirection = (LPCTSTR)strBuffer;
				}
			}
			char oldDir[LEN];  //LPWSTR oldDir[BUFFER_SIZE]
			if (!GetCurrentDirectory(LEN, (LPWSTR)oldDir))
				cerr << "Error getting current work directory: #" << GetLastError();
			cout << "Current work directory: " << oldDir << '\n';
			//const char* newDir = R"(C:\path\to\directory\)";
			if (!SetCurrentDirectory(projectWorkDirection))
				cerr << "Error setting current directory: #" << GetLastError();
			cout << "Set current directory to " << projectWorkDirection << '\n';

		}

		if (CreateProcess(L"C:\\Windows\\System32\\cmd.exe", NULL, NULL, NULL, FALSE, (processPriority != 0 ? processPriority : 0) | (processNewTerminal != 0 ? processNewTerminal : 0), NULL, NULL, &si, &pi)) { //"C:\\Windows\\System32\\cmd.exe"
			cout << "Process " << "C:\\Windows\\System32\\cmd.exe " << " created" << endl;
			cout << "A value that can be used to identify a process." << pi.dwProcessId << endl;
			cout << "A value that can be used to identify a thread. " << pi.dwThreadId << endl;
			if (!SetConsoleTitle(lpTerminalTitle)) {
				_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
			} else {
				_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
			}
			printf("\n\nEnd of work function CreateProcess\n");

			ExitProcess(NO_ERROR);
		} else
			printf("\n\nError working function CreateProcess!!!\n");

		cout << "Set title for new console?(1. Yes; Any. No)";
		cin >> priority;
		if (priority != 0 && priority != 1) {
			priority = 0;
		}
		if (priority == 1) {
			cout << "Enter title: ";
			cin >> strBuffer;
			if (strBuffer != "") {
				//terminalTitle = strBuffer;
				StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
			}
		} //StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), terminalTitle);
		if (!SetConsoleTitle(lpTerminalTitle)) {
			_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
		} else {
			_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), terminalColors[0]);
	}
	delete[]strBuffer;
	delete[]cmdline;*/

	/*//TCHAR terminalTitle[MAX_PATH];
	TCHAR lpTerminalTitle[MAX_PATH];
	//int priority = 0;
	//char* strBuffer = new char[LEN];
	cout << "Set title for new console?(1. Yes; Any. No)";
	cin >> priority;
	if (priority != 0 && priority != 1) {
		priority = 0;
	}
	if (priority == 1) {
		cout << "Enter title: ";
		cin >> strBuffer;
		if (strBuffer != "") {
			//terminalTitle = strBuffer;
			StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), strBuffer);
		}
	}
	//StringCchPrintf(lpTerminalTitle, MAX_PATH, TEXT("TEST: %s"), terminalTitle);
	if (!SetConsoleTitle(lpTerminalTitle)) {
		_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
	} else {
		_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
	}
	//delete[]strBuffer;*/

	CreateNewProcess();
	system("pause");
}
