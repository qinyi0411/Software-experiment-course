#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
int r, w;
int stack[10000];
int top = 0;
struct information {
	int x;
	int y;
	int lastx;
	int lasty;
	int id;
	int lastid;
	int flag;
};
struct information step[10000];
struct information road[1000];
 
int starditu(){
		int tmp, i, j, enterx, entery, leftx, lefty; 
		int ** ditu;
		printf("�����Ǵ��ļ������ͼ�����½�һ����ͼ���ļ�����������1���½���ͼ������2\n"); 
		scanf("%d", &tmp);
		switch(tmp){
			case 1:
				FILE* fp;
				char name[20];
				printf("�������ͼ���֣�");
				scanf("%s", name);
				fp = fopen(name, "w+");
				fscanf(fp, "%d %d %d %d %d %d\n",&r, &w, &enterx, &entery, &leftx, &lefty);		
				ditu = (int **)malloc(sizeof(int *) * r);
				for(i = 0; i < w; ++i){
					ditu[i] = (int *)malloc(sizeof(int *) * w);
				}
				while(!feof(fp)){
					for(i = 0; i < r; ++i){
						for(j = 0; j < w; ++j){
							fscanf(fp,"%d", &ditu[i][j]);
						}
					} 
				}
				break;
			case 2:
				printf("�������ͼ��������������");
	 			scanf("%d %d", &r, &w);
				ditu = (int **)malloc(sizeof(int *) * r);
				for(i = 0; i < w; ++i){
					ditu[i] = (int *)malloc(sizeof(int *) * w);
				}
				//�������ǳ�ʼ��
				for(i = 0; i < r; ++i){
					for(j = 0; j < w; ++j){
						ditu[i][j] = 1;
					}
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
	road[1].id = 1;
	road[1].flag = 1;
	int i;
	for(i = 2; i < 1000;++i){
		if(road[i].flag != 1){
			road[i].flag = 1;
			top++;
			stack[i] = i;
			road[i].lastid = i - 1;
			road[i].lastx = road[i-1].x;
			road[i].lasty = road[i-1].y;
			srand(time(NULL));
			int tmp = rand() % 4;
			tmp++;
			switch(tmp){
				case 1:
				if(ditu[road[i].lastx][road[i].lasty - 1] == 0) {
					road[i].x = road[i].lastx;
					road[i].y = road[i].lasty - 1;
					ditu[road[i].x][road[i].y] == 1;
				}
				break;
				case 2:
				if(ditu[road[i].lastx + 1][road[i].lasty] == 0) {
					road[i].x = road[i].lastx + 1;
					road[i].y = road[i].lasty;
					ditu[road[i].x][road[i].y] == 1;
				}
				break;
				case 3:
				if(ditu[road[i].lastx][road[i].lasty + 1] == 0) {
					road[i].x = road[i].lastx;
					road[i].y = road[i].lasty + 1;
					ditu[road[i].x][road[i].y] == 1;
				}
				break;
				case 4:
				if(ditu[road[i].lastx - 1][road[i].lasty] == 0) {
					road[i].x = road[i].lastx - 1;
					road[i].y = road[i].lasty;
					ditu[road[i].x][road[i].y] == 1;
				}
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
	return 0;
}
