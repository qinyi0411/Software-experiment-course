#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int ditu[100][100];
int r, w;
int stack[10000];
struct information {
	int x;
	int y;
	int lastx;
	int lasty;
	int lastid;
	int flag;
};

int starditu(){
	int tmp, i; 
	printf("�����Ǵ��ļ������ͼ�����½�һ����ͼ���ļ�����������1���½���ͼ������2\n"); 
	scanf("%d", &tmp);
	switch(tmp){
		case 1:
		
		break;
		case 2:
		printf("�������ͼ��������������");
		scanf("%d %d", &r, &w);
		for(i = 0;i < r; ++i){//����������for���߽���Ϊ-1 
			ditu[i][0] = -1;
			ditu[i][w] = -1;
		}
		ditu[i][w] = -1;
		ditu[r][0] = -1;
		ditu[0][w] = -1;
		for(i = 0; i < w; ++i){
			ditu[0][i] = -1;
			ditu[r][i] = -1;
		}
		//r��w�У���һ��ÿi�С�0����i�� �� r�е� 
		break;
	}
	return 0;
}

void shengchengmigong(){
	//��Ҫһ��������ֱ�ģ3���õ���·�����Ƿֱ�����ʱ����˳ʱ����߷� ��Ȼ��������������һ������������ӡ���Ҫһ�����������Ѿ����ɹ����Թ���������ѭ��
	//�������Ͻ��ߵ����Ͻ�
	//������ͬ�Ĵ�������Ͻ��ߵ�5����ͬ�ĵط���Ϊ�ϰ�. 

	road[1].x = 1;
	road[1].y = 1;
	road[1].lastx = -1;
	road[1].lasty = -1;
	road[1].lastid = -1;
	road[1].flag = 1;
	int seed = 8;
	int i, chu;
	for(i = 2; i < 1000;++i){
		if(road[i].flag != 1){
			road[i].flag = 1;
			road[i].lastid = i - 1;
			road[i].lastx = road[i-1].x;
			road[i].lasty = road[i-1].y;
			srand(time(NULL));
			int tmp = rand() % 3;
			tmp++;
			switch(tmp){
				case 1:
				break;
				case 2:
				break;
				case 3:
				break;
			}
		}
	}
}

void displayditu(void){
	int i, j;
	for(i = 1; i < r + 1; ++i){
		for(j = 1; j < w + 1; ++j){
			printf("%2d", &ditu[i][j]) ;
		/*	if(ditu[i][j] == -1){
				printf("%d", -1);
			}
			if(ditu[i][j] == 0){
				printf("%d", 0);
			}
			if(ditu[i][j] == 2){
				printf("%d", 2);
			}   */ 
		} 
		printf("\n");
	}
	printf("\n");
}




int storeditu(void){
	int tmp;
	printf("������Ҫ�������������棬�ļ����ݻ���ʧ����ʹ�Ǵ��ļ�����ĵ�ͼ,����������1���������˳�������2\n");
	scanf("%d", &tmp);
	switch(tmp){
		case 1:
		
		break;
		case 2:
		break;
	}
}

int main(void){
	ditu[0][0] = 0;
	struct information step[10000];
	struct information road[1000];
	return 0;
}
