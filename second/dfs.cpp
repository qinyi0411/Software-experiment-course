#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
int r, w;
int top = 0;
int tmp, i, j, enterx, entery, leftx, lefty;
int ** ditu;
struct information {
	int x;
	int y;
	int lastx;
	int lasty;
};
struct information step[10000];
struct information road[10000];

void displayditu(int **ditu){
	int i, j;
	for(i = 0; i < r ; ++i){
		for(j = 0; j < w; ++j){
			if(ditu[j][i] == 1){
				printf("▇");
			} 
			else{
				printf("  ");
			}
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

void filestar(int **ditu){
        FILE* fp;
        char name[20];
        printf("请输入地图名字：");
        scanf("%s", name);
        fp = fopen(name, "r");
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
}

void starditu(void){
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
    enterx = 1;
    entery = 1;
	leftx = r;
	lefty = w;
    road[1].x = 0;
    road[1].y = 0;
    road[1].lastx = -1;
    road[1].lasty = -1;
    ditu[0][0] = 0;

}

void shengchengmigong(){
	int check = 0;
	i = 2;
	srand(time(NULL));
    for(check = 0; check < 1000; ++check){
		road[i].lastx = road[i-1].x;
 		road[i].lasty = road[i-1].y;				  //最后复制此代码，设计出5条通向死路的路径作为干扰
	    if((road[i].lasty - 1 >= 0 && ditu[road[i].lastx][road[i].lasty - 1] == 1) || (road[i].lastx + 1 < w && ditu[road[i].lastx + 1][road[i].lasty] == 1) || (road[i].lasty + 1 < r && ditu[road[i].lastx][road[i].lasty + 1] == 1)){	        
	        
	        int tmp = rand() % 4;
	        tmp++;
	        switch(tmp){
	            case 1:
	                if(road[i].lasty - 1 >= 0 && ditu[road[i].lastx][road[i].lasty - 1] == 1) {
		                road[i].x = road[i].lastx;
		                road[i].y = road[i].lasty - 1;
		                ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lastx + 1 < w && ditu[road[i].lastx + 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx + 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
                  
	                }else if(road[i].lastx - 1 >=  0 && ditu[road[i].lastx - 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx - 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lasty + 1 < r && ditu[road[i].lastx][road[i].lasty + 1] == 1) {
	                    road[i].x = road[i].lastx;
	                    road[i].y = road[i].lasty + 1;
	                    ditu[road[i].x][road[i].y] = 0;
	                }
	            break;
	            case 2:
	                if(road[i].lastx + 1 < w && ditu[road[i].lastx + 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx + 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lastx - 1 >=  0 && ditu[road[i].lastx - 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx - 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lasty - 1 >= 0 && ditu[road[i].lastx][road[i].lasty - 1] == 1) {
		                road[i].x = road[i].lastx;
		                road[i].y = road[i].lasty - 1;
		                ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lasty + 1 < r && ditu[road[i].lastx][road[i].lasty + 1] == 1) {
	                    road[i].x = road[i].lastx;
	                    road[i].y = road[i].lasty + 1;
	                    ditu[road[i].x][road[i].y] = 0;
	                }
	            break;
	            case 3:
	                if(road[i].lasty + 1 < r && ditu[road[i].lastx][road[i].lasty + 1] == 1) {
	                    road[i].x = road[i].lastx;
	                    road[i].y = road[i].lasty + 1;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lastx - 1 >=  0 && ditu[road[i].lastx - 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx - 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lasty - 1 >= 0 && ditu[road[i].lastx][road[i].lasty - 1] == 1) {
		                road[i].x = road[i].lastx;
		                road[i].y = road[i].lasty - 1;
		                ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lastx + 1 < w && ditu[road[i].lastx + 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx + 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }
	            break;
	            case 4:
	                if(road[i].lastx - 1 >=  0 && ditu[road[i].lastx - 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx - 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lasty - 1 >= 0 && ditu[road[i].lastx][road[i].lasty - 1] == 1) {
		                road[i].x = road[i].lastx;
		                road[i].y = road[i].lasty - 1;
		                ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lastx + 1 < w && ditu[road[i].lastx + 1][road[i].lasty] == 1) {
	                    road[i].x = road[i].lastx + 1;
	                    road[i].y = road[i].lasty;
	                    ditu[road[i].x][road[i].y] = 0;
	                }else if(road[i].lasty + 1 < r && ditu[road[i].lastx][road[i].lasty + 1] == 1) {
	                    road[i].x = road[i].lastx;
	                    road[i].y = road[i].lasty + 1;
	                    ditu[road[i].x][road[i].y] = 0;
	                }
	            break;
	        }
	        displayditu(ditu);
	    }else {
            i--;
            continue;
	    }
	    if(road[i].x == leftx - 1 && road[i].y == lefty - 1){
	        return;
	    }
		++i;

	}

}

void searchroad(void){
    for(i = 0; i < 10000; ++i){

    }
}
int main(void){
		printf("请问是从文件导入地图还是新建一个地图？文件导入请输入1，新建地图请输入2\n");
		scanf("%d", &tmp);
		switch(tmp){
			case 1:
				filestar(ditu);
				break;
			case 2:
				starditu();
				displayditu(ditu);
                shengchengmigong();
		}
		displayditu(ditu);
		searchroad();

	return 0;
}
