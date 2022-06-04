/* 필요한 헤더파일 추가 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //난수 생성을 위한 time 헤더파일

#define MAX_ARRAY_SIZE 13	// 배열 최대크기 13 (내부값은 0 ~ 12)
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE // 해시테이블 최대크기 13

/* 함수 리스트 */
int initialize(int **a);  //배열 동적할당 및 값 랜덤으로 초기화 함수
int freeArray(int *a);    //배열 동적메모리 해제 함수
void printArray(int *a);  //배열 출력함수 

int selectionSort(int *a); //선택정렬 함수
int insertionSort(int *a); //삽입정렬 함수
int bubbleSort(int *a);    //버블정렬 함수
int shellSort(int *a);     //셸 정렬 함수 

//재귀함수로 구현한 퀵정렬
int quickSort(int *a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; //명령 입력받을
	int *array = NULL; //배열 가리킬 포인터 array

	int *hashtable = NULL; //해시테이블 가리킬 포인터 hashtable
	int key = -1; //
	int index = -1;

	srand(time(NULL));
	printf("[----- [이찬] [2019038029] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //포인터 변수 자체의 주소를 인수로 보내줌
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1; 
}

//배열 동적할당 및 값 랜덤으로 초기화 함수
int initialize(int** a) // 포인터의 주소값을 받아옴, 함수에서(*a) = array
{
	int *temp = NULL; //정수형 포인터temp 선언

	// 받아온 array 가 NULL일 때
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); 
		//temp가 가리키는 곳에 정수형 배열 최대크기만큼 동적할당
		*a = temp;  //메모리 할당된 temp가 가진 주소값을 array 에 전달 (이를 위해 이중포인터로 받아옴)
	} 
	else //이미 array ( *a) 가 가리키는 공간에 동적할당을 했을 시
		temp = *a;  //공간할당해놓은 주소값 temp에 대입

	//배열 내부값 랜덤으로 설정 ( 중복 가능 )
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 0 ~ 12 가 들어감

	return 0; //함수종료
}

//배열 동적메모리 해제 함수
int freeArray(int *a)
{
	//a가 가리키는 공간이 비어있지 않다면
	if(a != NULL)
		free(a);  //동적 메모리 해제
	return 0; //함수종료
}

//배열 출력함수 
void printArray(int *a)
{
	//a가 가리키는 공간이 비어있다면
	if (a == NULL) { 
		printf("nothing to print.\n"); 
		return ; //함수종료
	}
	//배열 인덱스 위치에 어떤 값이 있는지 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
	return ; //함수종료
}

//선택정렬 함수 
int selectionSort(int *a)
{
	int min; //최소값 저장할 변수
	int minindex; //최소값인 배열 원소의 인덱스 
	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 전 배열 출력

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // i 증가전 i 위치 인덱스 저장
		min = a[i];   // i 증가전 i 위치 값 저장
		for(int j = i+1; j < MAX_ARRAY_SIZE; j++){ //인덱스i+1부터 12까지 
			if (min > a[j]){ //저장해둔 min 값 보다 작은 경우 탐색
				min = a[j]; // 찾은 인덱스 위치 값 저장
				minindex = j; // 찾은 인덱스 저장
			}
		} // 탐색후
		a[minindex] = a[i]; //찾은 인덱스 위치에 i위치 원소값 대입
		a[i] = min; //찾은 최소값 i위치 원소에 대입
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 이후 배열 값 출력
	return 0; //함수종료
}

//삽입정렬 함수
int insertionSort(int *a)
{
	int index, temp; //현재 삽입될 원소의 인덱스, 값을 저장할 변수들
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 전 배열 출력

	for(int i = 1; i < MAX_ARRAY_SIZE; i++) // i=1부터 삽입되는 원소를 1칸씩 뒤로가며 반복
	{
		temp = a[i]; //삽입될 원소 값 저장
		index = i; //삽입될 원소 인덱스 저장
		
		//temp보다 인덱스-1 위치의 원소값이 큰 동안 반복
		while (a[index-1] > temp && index > 0){  
			a[index] = a[index-1]; //삽입될 원소 앞의 원소 값이 더 크므로
			// 그 값을 현재 인덱스 위치에 삽입
			index--; //인덱스 값 감소 
		}
		a[index] = temp; //삽입될 원소 값을 반복문 빠져나온 순간의 인덱스위치에 삽입
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 이후 배열 값 출력
	return 0; //함수종료
}

//버블정렬 함수
int bubbleSort(int *a)
{
	int temp; // swap 용 변수
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 전 배열 출력

	for(int i = 0; i < MAX_ARRAY_SIZE; i++){ //12회 반복
		for (int j = 0; j < MAX_ARRAY_SIZE-1; j++){ //j를 0부터 12까지 
			if (a[j+1] < a[j]) //인덱스 j 원소값이 j+1 원소 값보다 클 때
			{ 
				temp = a[j+1]; 
				a[j+1] = a[j];
				a[j] = temp;
			} //a[j] , a[j+1] 스왑
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 이후 배열 값 출력
	return 0; //메인함수 종료
}

//셸 정렬 함수 
int shellSort(int *a)
{
	int  h; // 간격 나타낼 h
	int index, temp;
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 전 배열 출력

	//간격을 1/2시키며 간격이 1보다 작아질때까지 반복
	for ( h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{//h가 1되면 /2할때 정수형이라 다음 반복때 0됨 = 탈출
		for (int i = 0; i < h; i++)
		{ //h 간격 만큼 떨어진 원소들끼리 집합만들때 생긴 집합 개수만큼 반복
			for(int j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{ // h 간격 사이의 원소 간 삽입정렬
				temp = a[j];
				index = j;
				//temp보다 인덱스-h 위치의 원소값이 큰 동안 반복
				while (a[index-h] > temp && index > h-1){
					a[index] = a[index-h];
					index -= h;
				}
				a[index] = temp;
			}// 인덱스가 h 만큼 감소되는것을 제외하면 삽입정렬 알고리즘과 동일
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 이후 배열 값 출력
	return 0; //메인함수 종료
}



//재귀함수로 구현한 퀵정렬
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}



//해싱 함수들



int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}