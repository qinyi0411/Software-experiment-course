/*main(): 主程序。命令行或图形界面方式。
CreateHTable():根据给定的联系人数组创建哈希表。
SearchHTable():根据给定的姓名快速查找联系人。
InsertHTable(): 插入给定的联系人。
DeleteHTable():根据给定的姓名删除联系人。
DisplayHTable(): 显示哈希表中的所有联系人信息。
*/
#include<stdio.h>
#include<string.h>

char name[1000][20];
char addr[1000][50];
char numb[1000][11];
int Hnumb[1000];//哈希值
int Hflag[1000]; 
char nametmp[20];//暂存姓名 
char addrtmp[50];
char numbtmp[11];
int Hnumbtmp;//暂存查找哈希值，用于冲突处理 

int GetHkey(char *q){//根据姓名求出哈希地址 
	char *p = q;
	int itmp;
	int sum = 0;
	while(*p != '\0'){
		itmp = *p;
		sum += itmp;
		p++; 
	}
	return sum % 1009;
}

int CollisionKey(int Hnumbtmp){ //冲突处理 
	int i = 1;
	while(Hnumb[Hnumbtmp] != 0){
		if(Hnumb[Hnumbtmp + i*i] == 0){
			Hnumbtmp += i*i;
		}else if(Hnumb[Hnumbtmp - i*i] == 0){
			Hnumbtmp -= i*i;
			}
		i++;	 
		}
		
		return Hnumbtmp;
}
 
int SearchHTable(char *nametmp	){
	int tmp = GetHkey(nametmp);
	int i = 1, j = 0;
	while(strcmp(name[tmp], nametmp)){
		if(strcmp(name[tmp + i*i], nametmp) == 0){
			tmp += i*i;
		}
		if(strcmp(name[tmp - i*i], nametmp) == 0){
			tmp -= i*i;
		}
		if(++j > 15){
			return -1;
		}
		++i;
	}
	return tmp;
}


void DeleteHTable(char *nametmp){
	Hnumbtmp = SearchHTable(nametmp);
	Hflag[Hnumbtmp] = 0;
}

void DisplayHTable(){
	int i;
	for(i = 0; i < 1000; ++i){
		if(Hflag[i] >= 1){
				printf("\t姓名：%12s\n\t电话：%12s\n\t住址：%12s\n\n", name[i], numb[i], addr[i]);
		}
	}
}

void store(FILE *fp){	
	while(!feof(fp)){
		fscanf(fp, "%d", &Hnumbtmp);
		fscanf(fp, "%d %s %s %s\n",&Hflag[Hnumbtmp], name[Hnumbtmp], numb[Hnumbtmp], addr[Hnumbtmp]);
		//		fscanf(fp, "%d %d %s %s %s\n", &Hnumbtmp, &Hflag[Hnumbtmp], name[Hnumbtmp], numb[Hnumbtmp], addr[Hnumbtmp]);
//		printf("%d %d %s %s %s\n",Hnumbtmp, Hflag[Hnumbtmp], name[Hnumbtmp], numb[Hnumbtmp], addr[Hnumbtmp]); 
		Hnumb[Hnumbtmp] = Hnumbtmp;
	}
} 

void displayList(void){
		printf("------欢迎使用电话本------\n\n");
		printf("\t\t制作者：覃翊 2016060107008\n\n");
		printf("\t输入操作数字并回车以执行操作\n\n"); 
		printf("\t1.打开说明书\n");	
		printf("\t2.新建电话本\n"); 
		printf("\t3.从文件中导入电话本\n");
		printf("\t4.导出至文件\n");
		printf("\t5.查找联系人\n");
		printf("\t6.新建联系人\n");
		printf("\t7.修改联系人\n");
		printf("\t8.删除联系人\n");
		printf("\t9.显示联系人信息\n");
		printf("\t10.设置亲情联系人\n");
		printf("\t11.展示亲情联系人\n");
		printf("\t12.添加联系人至黑名单\n");
		printf("\t13.移除联系人出黑名单\n");
		printf("\t14.显示黑名单列表\n");
		printf("\t15.退出\n\n");
		printf("-------------------------\n");
}

int main(void){
	int mode = 1;
	int i, tmp;
	char listname[20];
	Hnumb[1] = Hflag[0] = 0;
	FILE *fp;
	while(mode){
		displayList();
		scanf("%d", &mode);
		switch(mode){
			case 1:
				printf("\t此电话本说明书：\n\n\t操作1与操作2二选一打开电话本，每次需打开电话本后才能进行操作，\n\t本电话本系统支持多电话本管理，不同的文件名对应不同的电话本，\n\t打开电话本成功后会得到提示，此时可进行列表所有操作，需要注意\n\t的是，当一切操作 结束后，需执行操作4以保存，这样才能从内存将\n\t数据保存至文件，本系统高效，稳定，祝使用愉快！\n\n");
				break; 
			case 2:
			//指针指向新电话本，输入名字，打印新建成功，退出
				printf("请输入电话本名字：");
				scanf("%s", listname);
				fp = fopen(listname, "w+");
				printf("新建成功，请继续操作。\n"); 
				break;
			case 3:
			//要求输入电话本名字，密码，检查名字密码。指针指向打开电话本，包含若打不开的错误输出（名称错误和密码错误），打印导入成功，退出 
				printf("请输入要打开的电话本名字：");
				scanf("%s", listname);
				fp = fopen(listname, "r");
				store(fp); 
				printf("打开电话本成功，请继续您的操作。\n"); 
				fclose(fp);
				break;
			case 4:
				fp = fopen(listname, "w+");
				for(i = 0; i < 1000; ++i){
					if(Hflag[i] >= 1){
						fprintf(fp, "%d\t%d\t%s\t%s\t%s\n", Hnumb[i], Hflag[i], name[i], numb[i], addr[i]);
					}
				}
				fclose(fp);
				printf("保存成功！\n"); 
				break;
			case 5:
			//根据姓名查，如果查失败，则询问添加此人信息 
				printf("要显示联系人的姓名：");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				if(Hnumbtmp > 0){
						printf("姓名：%s\t电话:%s\t地址：%s\n", name[Hnumbtmp], numb[Hnumbtmp], addr[Hnumbtmp]);
				}else if(Hnumbtmp == -1){
					printf("查找失败\n是否添加此人信息？按1回车确认，否则按0\n");
					scanf("%d", &tmp);
					if(tmp){
						Hnumbtmp = GetHkey(nametmp);
						Hnumbtmp = CollisionKey(Hnumbtmp); 
						Hflag[Hnumbtmp] = 1; 
						strcpy(&name[Hnumbtmp][0], nametmp);
						printf("请输入该联系人住址：");
						scanf("%s", addr[Hnumbtmp]);
						printf("请输入联系人电话：");
						scanf("%s", numb[Hnumbtmp]); 
					}
				}		
				break;
			case 6:
			//姓名，电话，住址，若有重复的，则询问是否覆盖 ，否则在名字后添加数字编号 
				printf("请输入姓名：");
				scanf("%s", nametmp);
				if(Hflag[CollisionKey(GetHkey(nametmp))] == 0){
					Hnumbtmp = GetHkey(nametmp);
					Hnumbtmp = CollisionKey(Hnumbtmp); 
					Hnumb[Hnumbtmp] = Hnumbtmp; 
					Hflag[Hnumbtmp] = 1; 
					strcpy(&name[Hnumbtmp][0], nametmp);
					printf("请输入该联系人住址：");
					scanf("%s", addr[Hnumbtmp]);
					printf("请输入联系人电话：");
					scanf("%s", numb[Hnumbtmp]); 
				}else{
					printf("该联系人已存在，是否覆盖？按1回车确认，否则按0\n");
					scanf("%d", &tmp);
					if(tmp){
						Hnumbtmp = GetHkey(nametmp);
						Hflag[Hnumbtmp] = 1; 
						Hnumb[Hnumbtmp] = Hnumbtmp;
						strcpy(&name[Hnumbtmp][0], nametmp);
						printf("请输入该联系人住址：");
						scanf("%s", addr[Hnumbtmp]);
						printf("请输入联系人电话：");
						scanf("%s", numb[Hnumbtmp]); 
					}else{
						char plus[2] = {'*'};
						strcat(nametmp, plus);
						Hnumbtmp = GetHkey(nametmp);
						Hnumbtmp = CollisionKey(Hnumbtmp); 
						Hflag[Hnumbtmp] = 1; 
						Hnumb[Hnumbtmp] = Hnumbtmp;
						strcpy(&name[Hnumbtmp][0], nametmp);
						printf("请输入该联系人住址：");
						scanf("%s", addr[Hnumbtmp]);
						printf("请输入联系人电话：");
						scanf("%s", numb[Hnumbtmp]); 
					} 
				}
				printf("添加成功！\n");					
				break;
			case 7:
			//修改联系人 
				printf("要修改联系人的姓名：");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				printf("新电话号码：");
				scanf("%s", numb[Hnumbtmp]); 
				printf("新住址：");
				scanf("%s", addr[Hnumbtmp]); 
				printf("修改成功"); 
				break;
			case 8:
			//删除联系人 
				printf("请输入要删除联系人的名字：");
				scanf("%s", nametmp); 
				DeleteHTable(nametmp);
				printf("删除成功！\n");	
				break;
			case 9:
			//显示联系人姓名，电话，地址 
				DisplayHTable();
				break;
			case 10:
			//修改flag
				printf("请输入要设为亲情联系人的名字：");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				Hflag[Hnumbtmp] = 2; 
				printf("设置成功！\n");	
				break; 
			case 11:
				for(i = 0; i < 1000; ++i){
					if(Hflag[i] == 2){
						printf("姓名：%8s\t电话：%8s\t地址：%8s\n", name[i], numb[i], addr[i]);
					}
				}
				break;
			case 12:
				printf("请输入要拉黑的联系人：");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				Hflag[Hnumbtmp] = 3; 
				printf("拉黑成功！\n");	
				break;
			case 13:
				printf("请输入从黑名单移除的人：");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				Hflag[Hnumbtmp] = 1;
				printf("移除成功！\n");	 
				break; 
			case 14:
				for(i = 0; i < 1000; ++i){
					if(Hflag[i] == 3){
						printf("姓名：%8s\t电话：%8s\t地址：%8s\n", name[i], numb[i], addr[i]);
					}
				}
				break;
			case 15:
				mode = 0;
				break;
			
		}
	}
	fclose(fp); 
	return 0;
} 
