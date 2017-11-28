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
	printf("请问是从文件导入地图还是新建一个地图？文件导入请输入1，新建地图请输入2\n"); 
	scanf("%d", &tmp);
	switch(tmp){
		case 1:
		
		break;
		case 2:
		printf("请输入地图的行数和列数：");
		scanf("%d %d", &r, &w);
		for(i = 0;i < r; ++i){//接下来两个for将边界设为-1 
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
		//r行w列，第一行每i列【0】【i】 第 r行第 
		break;
	}
	return 0;
}

void shengchengmigong(){
	//需要一随机数，分别模3，得到的路径就是分别是来时方向顺时针的走法 ，然后该随机数又是下一个随机数的种子。需要一个标记来标记已经生成过的迷宫避免走入循环
	//最后从左上角走到右上角
	//再用相同的代码从左上角走到5个不同的地方作为障碍. 

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
	printf("请问需要保存吗？若不保存，文件数据会消失，即使是从文件导入的地图,保存请输入1，不保存退出请输入2\n");
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
