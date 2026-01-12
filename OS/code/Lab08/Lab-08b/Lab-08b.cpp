#include <stdio.h>
#include <windows.h>


int main() {

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	DWORD dwPageSize = sysInfo.dwPageSize;
	LPVOID lpBaseAddress = VirtualAlloc(NULL, dwPageSize * 256, MEM_RESERVE, PAGE_NOACCESS);

	printf("-------- 1 stage ------------\n\n");


	if (lpBaseAddress == NULL) {

		printf("Failed to reserve pages");
		return 1;
	}


	printf("Pages address: %p\n\n", lpBaseAddress);

	system("pause");



	printf("-------- 2 stage ------------\n\n");


	LPVOID lpCommitAddress = VirtualAlloc((LPBYTE)lpBaseAddress + 128 * dwPageSize, dwPageSize * 128, MEM_COMMIT, PAGE_READWRITE);

	if (lpCommitAddress == NULL) {

		printf("Failed to commit physical memory");
		VirtualFree(lpBaseAddress, 0, MEM_RELEASE);
		return 1;
	}


	printf("Commited physical memory for second half\n");

	system("pause");



	printf("-------- 3 stage ------------\n\n");


	int* ptr = (int*)lpCommitAddress;
	int count = (dwPageSize * 128) / (sizeof(int));

	for (int i = 0; i < count; i++) {
		ptr[i] = i;
	}

	printf("Pages filled with numbers\n");

	system("pause");



	printf("-------- 4 stage ------------\n\n");

	DWORD oldProtect;

	if (!VirtualProtect(lpCommitAddress, dwPageSize * 128, PAGE_READONLY, &oldProtect)) {
		printf("Failed to change protection");
		VirtualFree(lpBaseAddress, 0, MEM_RELEASE);
		return 1;
	}

	printf("Changed protection to READONLY\n");


	system("pause");



	printf("-------- 5 stage ------------\n\n");

	if (!VirtualFree(lpCommitAddress, dwPageSize * 128, MEM_DECOMMIT)) {
		printf("Failed to decommit pages\n");
	}
	else {
		printf("Decommited pages\n");
	}



	system("pause");


	printf("-------- 6 stage ------------\n\n");

	if (!VirtualFree(lpBaseAddress, 0, MEM_RELEASE)) {
		printf("Failed to release pages\n");
	}
	else {
		printf("Released pages\n");
	}

	system("pause");


	return 0;
}