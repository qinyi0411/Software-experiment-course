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
		printf("请问是从文件导入地图还是新建一个地图？文件导入请输入1，新建地图请输入2\n"); 
		scanf("%d", &tmp);
		switch(tmp){
			case 1:
				FILE* fp;
				char name[20];
				printf("请输入地图名字：");
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
				printf("请输入地图的行数和列数：");
	 			scanf("%d %d", &r, &w);
				ditu = (int **)malloc(sizeof(int *) * r);
				for(i = 0; i < w; ++i){
					ditu[i] = (int *)malloc(sizeof(int *) * w);
				}
				//接下来是初始化
				for(i = 0; i < r; ++i){
					for(j = 0; j < w; ++j){
						ditu[i][j] = 1;
					}
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
	return 0;
}
