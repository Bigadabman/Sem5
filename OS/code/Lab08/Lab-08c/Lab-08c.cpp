#include <stdio.h>
#include <windows.h>

void HeapInfo(HANDLE hHeap) {

	PROCESS_HEAP_ENTRY entry;
	entry.lpData = NULL;
	SIZE_T totalSize = 0;


	printf("heap info: \n");

	while (HeapWalk(hHeap, &entry)) {

		if (entry.wFlags & PROCESS_HEAP_REGION)
		{
			printf("\tREGION  start: %p  size: %llu\n", entry.lpData, (unsigned long long)entry.Region.dwCommittedSize);

			totalSize += entry.Region.dwCommittedSize;
		}
		else if (entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE)
		{
			printf("\tUNCOMMITED start: %p  size: %llu\n", entry.lpData, (unsigned long long)entry.cbData);
		}
		else if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
		{
			printf("\tBUSY start: %p  size: %llu\n", entry.lpData, (unsigned long long)entry.cbData);
		}
	}

	printf("Total committed heap size: %llu bytes\n\n", (unsigned long long)totalSize);

}



int main()
{

	const SIZE_T BASE_SIZE = 1024 * 1024;
	const SIZE_T MAX_SIZE = 8 * 1024 * 1024;
	const SIZE_T BLOCK_SIZE = 512 * 1024;
	const int BLOCK_AMOUNT = 10;


	printf("-------- 1 stage ------------\n\n");


	HANDLE hHeap = HeapCreate(0, BASE_SIZE, MAX_SIZE);

	if (hHeap == NULL) {
		printf("Failed to create heap");
		return 1;
	}

	printf("Heap created\n");

	HeapInfo(hHeap);
	system("pause & cls");


	printf("-------- 2 stage ------------\n\n");



	LPVOID blocks[BLOCK_AMOUNT] = { 0 };


	for (int i = 0; i < BLOCK_AMOUNT; i++) {

		blocks[i] = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, BLOCK_SIZE);

		if (blocks[i] == NULL) {
			printf("Failed to create block %d\n", i);
			break;
		}


		printf("Allocated block %d\n", i);
		HeapInfo(hHeap);
		system("pause & cls");

	}


	printf("-------- 3 stage ------------\n\n");


	for (int i = 0; i < BLOCK_AMOUNT; i++) {

		int* arr = (int*)blocks[i];
		int count = BLOCK_SIZE / (sizeof(int));

		for (int j = 0; j < count; j++) {

			arr[j] = j;

		}
	}


	printf("Blocks filled with arrrays\n");

	system("pause & cls");


	printf("-------- 4 stage ------------\n\n");


	for (int i = 0; i < BLOCK_AMOUNT; i++) {

		if (blocks[i]) {
			HeapFree(hHeap, 0, blocks[i]);
			printf("block %d freed\n", i);
		}

	}
	HeapInfo(hHeap);
	printf("All blocks freed\n");

	system("pause & cls");


	printf("-------- 5 stage ------------\n\n");

	HeapDestroy(hHeap);

	printf("Heap destroyed\n");

	system("pause");

	return 0;
}

