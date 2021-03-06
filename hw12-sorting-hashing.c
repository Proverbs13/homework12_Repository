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

//해시코드 생성기 키를 % MAX_HASH_TABLE_SIZE 연산으로 해시코드 생성 , 사실상 같음
int hashCode(int key);

//배열로 해시테이블 구상
int hashing(int *a, int **ht);

//해시테이블에서 검색하는 함수
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
			printArray(array);// 해싱 대상 배열 출력
			hashing(array, &hashtable); //해시테이블 구상
			printArray(hashtable); //해시테이블 출력
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
int quickSort(int *a, int n) //n = MAX_ARRAY_SIZE
{
	int pivot; //피벗용 변수 
	int temp;  //임시 저장용 변수 temp
	int i; //피벗 기준 왼쪽부터 증가할 인덱스 나타낼 i
	int j; //피벗 기준 오른쪽부터 줄어들 인덱스 나타낼 j
	if (n > 1) //n 이 1보다 클 때
	{
		pivot = a[n-1]; //피벗은 배열 맨 오른쪽 원소 a[n-1]
		i = -1;    // ++i로 0부터 탐색시작 
		j = n - 1; // --j로 n-2부터 탐색시작

		while(1)// 무한루프
		{
			while(a[++i] < pivot); 
			//증가시킨 i 위치 원소가 피벗보다 클 때의 i 위치 찾을때까지 반복(i 증가)
			while(a[--j] > pivot);
			//감소시킨 j 위치 원소가 피벗보다 작을 때의 j 위치 찾을때까지 반복(j 증가)

			if (i >= j) break; //찾던도중 i가 j보다 크거나 같아질 때 반복문 탈출

			//찾은 i, j 인덱스 위치 값들에 대해서 a[i] & a[j] 스왑
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		//a[i] & a[n-1] 스왑 => 피벗의 값을 i위치 원소값과 교체
		temp = a[i];
		a[i] = a[n-1];
		a[n-1] = temp;

		//이번 루틴의 피벗값은 i로 이동되며 고정

		quickSort(a, i); // 피벗기준 왼쪽 부분집합 퀵정렬 호출
		// 배열 a(시작주소) , 피벗 왼쪽의 배열 크기는 인덱스 0 ~ i-1까지 i개 이므로 i 를 인수로 보내줌

		quickSort(a+i+1, n-i-1);// 피벗기준 오른쪽 부분집합 퀵정렬 호출
		//배열 a+i+1(a배열이 i번째 인덱스다음 원소부터 시작해야하므로 a+i+1,
		//피벗 오른쪽의 배열 크기는 인덱스 i+1 ~ n-1 까지 n개 이므로 n 을 인수로 보내줌
	}
	return 0; // 함수종료
}


//해시코드 생성
int hashCode(int key) { 
   return key % MAX_HASH_TABLE_SIZE; // 키의 모듈러 연산
}

int hashing(int *a, int **ht) // 포인터의 주소값을 받아옴, 함수에서(*ht) = hashtable
{
	int *hashtable = NULL; //해시테이블 동적할당을 위한 포인터 생성

	// 받아온 *ht 가 NULL일 때 - 첫 실행시
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //가리키는 공간에 해시테이블 크기만큼 동적할당
		*ht = hashtable; //메모리 할당된 hashtable이 가진 주소값을*ht 에 전달 (이를 위해 이중포인터로 받아옴)
	} 
	else {//이미  (*ht)가 가리키는 공간에 동적할당을 했을 시
		hashtable = *ht;//공간할당해놓은 주소값 hashtable에 대입
	
	}
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){ 
		hashtable[i] = -1;
	} //해시테이블 내부 -1로 초기화

	//해시테이블 구상용 변수들 기본 -1 로 초기화
	int key = -1; 
	int hashcode = -1;
	int index = -1;

	// 해시테이블 최대크기만큼 반복
	for (int i = 0; i < MAX_ARRAY_SIZE; i++){ //배열의 인덱스  i = 0 부터 12까지 반복
		key = a[i]; //배열 값을 key로 받아옴
		hashcode = hashCode(key); // key에 대한 해시코드 생성
		
		if (hashtable[hashcode] == -1){ //처음생성된 해시코드일 때
			hashtable[hashcode] = key; //해시테이블의 값 = 키, 인덱스 = 해시코드
		} 
		else { //이미 생성됬던 해시코드 일 때 (해시코드=인덱스 위치 값이 차있을 때)
			index = hashcode; // 인덱스에 해시코드 임시 저장하고
			while(hashtable[index] != -1){ //값이 -1인 해시테이블 빈자리 찾을 때 까지 반복
				index = (++index) % MAX_HASH_TABLE_SIZE;// 모듈러 연산이용 다음 칸으로 이동 
			}   // 인덱스 12 다음에 0으로 이동
			hashtable[index] = key; // 찾은 인덱스 위치에 키 대입
		}
	}
	return 0;//함수종료
}

//해시테이블에서 검색함수
int search(int *ht, int key)
{
	int index = hashCode(key); //검색하는 키에 대한 해시코드 받아옴

	if(ht[index] == key){ //테이블에 값 = 키, 인덱스 = 해시코드로 들어간 키라면
		return index; //바로 그 인덱스 반환하며 함수 종료
	}
	//인덱스 증가시키며 key 찾을 때까지 탐색
	while(ht[++index] != key){
		index = index % MAX_HASH_TABLE_SIZE;// 모듈러 연산이용 다음 칸으로 이동 
		// 인덱스 12 다음에 0으로 이동
	}
	return index; //인덱스 반환하며 함수 종료
}