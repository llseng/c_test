#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

//��ȡ���int����
unsigned int * rand_intarr(unsigned int *, unsigned int );
//int����-ѡ������
int * intarr_select_sort(int * , int , int); 

int main(int argc, char const *argv[]) {
	unsigned int intarr_len = 10;
	unsigned int intarr[intarr_len * 8];
	
	rand_intarr(intarr, intarr_len);
	intarr_select_sort(intarr, intarr_len, 1);
	unsigned int intarr_k = 0;
	
	while( intarr_k < intarr_len ) {
		printf(">%d", intarr_k);
		printf("->%d\n", intarr[intarr_k++]);
	} 
	
	return 0;
} 


unsigned int * rand_intarr(unsigned int *arr, unsigned int len) {
	time_t timestamp;
	srand((unsigned) time(&timestamp));
	unsigned int i = len;
	printf("i=%d\n", i);
	unsigned int k = 0;
	while( i ) {
		arr[k++] = rand();
		i--;
	}
	return arr;
}

int * intarr_select_sort(int * arr, int len, int t) {
	//��ʱ���� 
	int tmp;
	int i = 0;
	//��ʱ�� 
	int k = 0;
	for(; i<len; i++) {
		int j = i+1;
		//���ֿ�ʼ�� 
		k = i;
		for(; j<len; j++) {
			// ��С 
			if( t > 0 ) {
				if( arr[k] < arr[j] ) k = j;//�������ֵ��
			}else{
				if( arr[k] > arr[j] ) k = j;//������Сֵ�� 
			}
		} 
		//��ʱ����ǰ������ 
		if( k == i ) continue;
		tmp = arr[i];
		arr[i] = arr[k];
		arr[k] = tmp;
	}
	return arr; 
} 
 
