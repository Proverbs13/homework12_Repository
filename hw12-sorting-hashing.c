/* �ʿ��� ������� �߰� */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //���� ������ ���� time �������

#define MAX_ARRAY_SIZE 13	// �迭 �ִ�ũ�� 13 (���ΰ��� 0 ~ 12)
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE // �ؽ����̺� �ִ�ũ�� 13

/* �Լ� ����Ʈ */
int initialize(int **a);  //�迭 �����Ҵ� �� �� �������� �ʱ�ȭ �Լ�
int freeArray(int *a);    //�迭 �����޸� ���� �Լ�
void printArray(int *a);  //�迭 ����Լ� 

int selectionSort(int *a); //�������� �Լ�
int insertionSort(int *a); //�������� �Լ�
int bubbleSort(int *a);    //�������� �Լ�
int shellSort(int *a);     //�� ���� �Լ� 

//����Լ��� ������ ������
int quickSort(int *a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command; //��� �Է¹���
	int *array = NULL; //�迭 ����ų ������ array

	int *hashtable = NULL; //�ؽ����̺� ����ų ������ hashtable
	int key = -1; //
	int index = -1;

	srand(time(NULL));
	printf("[----- [����] [2019038029] -----]\n");
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
			initialize(&array); //������ ���� ��ü�� �ּҸ� �μ��� ������
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

//�迭 �����Ҵ� �� �� �������� �ʱ�ȭ �Լ�
int initialize(int** a) // �������� �ּҰ��� �޾ƿ�, �Լ�����(*a) = array
{
	int *temp = NULL; //������ ������temp ����

	// �޾ƿ� array �� NULL�� ��
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); 
		//temp�� ����Ű�� ���� ������ �迭 �ִ�ũ�⸸ŭ �����Ҵ�
		*a = temp;  //�޸� �Ҵ�� temp�� ���� �ּҰ��� array �� ���� (�̸� ���� ���������ͷ� �޾ƿ�)
	} 
	else //�̹� array ( *a) �� ����Ű�� ������ �����Ҵ��� ���� ��
		temp = *a;  //�����Ҵ��س��� �ּҰ� temp�� ����

	//�迭 ���ΰ� �������� ���� ( �ߺ� ���� )
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 0 ~ 12 �� ��

	return 0; //�Լ�����
}

//�迭 �����޸� ���� �Լ�
int freeArray(int *a)
{
	//a�� ����Ű�� ������ ������� �ʴٸ�
	if(a != NULL)
		free(a);  //���� �޸� ����
	return 0; //�Լ�����
}

//�迭 ����Լ� 
void printArray(int *a)
{
	//a�� ����Ű�� ������ ����ִٸ�
	if (a == NULL) { 
		printf("nothing to print.\n"); 
		return ; //�Լ�����
	}
	//�迭 �ε��� ��ġ�� � ���� �ִ��� ���
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
	return ; //�Լ�����
}

//�������� �Լ� 
int selectionSort(int *a)
{
	int min; //�ּҰ� ������ ����
	int minindex; //�ּҰ��� �迭 ������ �ε��� 
	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a); //���� �� �迭 ���

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // i ������ i ��ġ �ε��� ����
		min = a[i];   // i ������ i ��ġ �� ����
		for(int j = i+1; j < MAX_ARRAY_SIZE; j++){ //�ε���i+1���� 12���� 
			if (min > a[j]){ //�����ص� min �� ���� ���� ��� Ž��
				min = a[j]; // ã�� �ε��� ��ġ �� ����
				minindex = j; // ã�� �ε��� ����
			}
		} // Ž����
		a[minindex] = a[i]; //ã�� �ε��� ��ġ�� i��ġ ���Ұ� ����
		a[i] = min; //ã�� �ּҰ� i��ġ ���ҿ� ����
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //���� ���� �迭 �� ���
	return 0; //�Լ�����
}

//�������� �Լ�
int insertionSort(int *a)
{
	int index, temp; //���� ���Ե� ������ �ε���, ���� ������ ������
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� �� �迭 ���

	for(int i = 1; i < MAX_ARRAY_SIZE; i++) // i=1���� ���ԵǴ� ���Ҹ� 1ĭ�� �ڷΰ��� �ݺ�
	{
		temp = a[i]; //���Ե� ���� �� ����
		index = i; //���Ե� ���� �ε��� ����
		
		//temp���� �ε���-1 ��ġ�� ���Ұ��� ū ���� �ݺ�
		while (a[index-1] > temp && index > 0){  
			a[index] = a[index-1]; //���Ե� ���� ���� ���� ���� �� ũ�Ƿ�
			// �� ���� ���� �ε��� ��ġ�� ����
			index--; //�ε��� �� ���� 
		}
		a[index] = temp; //���Ե� ���� ���� �ݺ��� �������� ������ �ε�����ġ�� ����
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ���� �迭 �� ���
	return 0; //�Լ�����
}

//�������� �Լ�
int bubbleSort(int *a)
{
	int temp; // swap �� ����
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� �� �迭 ���

	for(int i = 0; i < MAX_ARRAY_SIZE; i++){ //12ȸ �ݺ�
		for (int j = 0; j < MAX_ARRAY_SIZE-1; j++){ //j�� 0���� 12���� 
			if (a[j+1] < a[j]) //�ε��� j ���Ұ��� j+1 ���� ������ Ŭ ��
			{ 
				temp = a[j+1]; 
				a[j+1] = a[j];
				a[j] = temp;
			} //a[j] , a[j+1] ����
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ���� �迭 �� ���
	return 0; //�����Լ� ����
}

//�� ���� �Լ� 
int shellSort(int *a)
{
	int  h; // ���� ��Ÿ�� h
	int index, temp;
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� �� �迭 ���

	//������ 1/2��Ű�� ������ 1���� �۾��������� �ݺ�
	for ( h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{//h�� 1�Ǹ� /2�Ҷ� �������̶� ���� �ݺ��� 0�� = Ż��
		for (int i = 0; i < h; i++)
		{ //h ���� ��ŭ ������ ���ҵ鳢�� ���ո��鶧 ���� ���� ������ŭ �ݺ�
			for(int j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{ // h ���� ������ ���� �� ��������
				temp = a[j];
				index = j;
				//temp���� �ε���-h ��ġ�� ���Ұ��� ū ���� �ݺ�
				while (a[index-h] > temp && index > h-1){
					a[index] = a[index-h];
					index -= h;
				}
				a[index] = temp;
			}// �ε����� h ��ŭ ���ҵǴ°��� �����ϸ� �������� �˰���� ����
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//���� ���� �迭 �� ���
	return 0; //�����Լ� ����
}



//����Լ��� ������ ������
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



//�ؽ� �Լ���



int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
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