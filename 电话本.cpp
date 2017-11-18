/*main(): �����������л�ͼ�ν��淽ʽ��
CreateHTable():���ݸ�������ϵ�����鴴����ϣ��
SearchHTable():���ݸ������������ٲ�����ϵ�ˡ�
InsertHTable(): �����������ϵ�ˡ�
DeleteHTable():���ݸ���������ɾ����ϵ�ˡ�
DisplayHTable(): ��ʾ��ϣ���е�������ϵ����Ϣ��
*/
#include<stdio.h>
#include<string.h>

char name[1000][20];
char addr[1000][50];
char numb[1000][11];
int Hnumb[1000];//��ϣֵ
int Hflag[1000]; 
char nametmp[20];//�ݴ����� 
char addrtmp[50];
char numbtmp[11];
int Hnumbtmp;//�ݴ���ҹ�ϣֵ�����ڳ�ͻ���� 

int GetHkey(char *q){//�������������ϣ��ַ 
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

int CollisionKey(int Hnumbtmp){ //��ͻ���� 
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
				printf("\t������%12s\n\t�绰��%12s\n\tסַ��%12s\n\n", name[i], numb[i], addr[i]);
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
		printf("------��ӭʹ�õ绰��------\n\n");
		printf("\t\t�����ߣ���� 2016060107008\n\n");
		printf("\t����������ֲ��س���ִ�в���\n\n"); 
		printf("\t1.��˵����\n");	
		printf("\t2.�½��绰��\n"); 
		printf("\t3.���ļ��е���绰��\n");
		printf("\t4.�������ļ�\n");
		printf("\t5.������ϵ��\n");
		printf("\t6.�½���ϵ��\n");
		printf("\t7.�޸���ϵ��\n");
		printf("\t8.ɾ����ϵ��\n");
		printf("\t9.��ʾ��ϵ����Ϣ\n");
		printf("\t10.����������ϵ��\n");
		printf("\t11.չʾ������ϵ��\n");
		printf("\t12.�����ϵ����������\n");
		printf("\t13.�Ƴ���ϵ�˳�������\n");
		printf("\t14.��ʾ�������б�\n");
		printf("\t15.�˳�\n\n");
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
				printf("\t�˵绰��˵���飺\n\n\t����1�����2��ѡһ�򿪵绰����ÿ����򿪵绰������ܽ��в�����\n\t���绰��ϵͳ֧�ֶ�绰��������ͬ���ļ�����Ӧ��ͬ�ĵ绰����\n\t�򿪵绰���ɹ����õ���ʾ����ʱ�ɽ����б����в�������Ҫע��\n\t���ǣ���һ�в��� ��������ִ�в���4�Ա��棬�������ܴ��ڴ潫\n\t���ݱ������ļ�����ϵͳ��Ч���ȶ���ףʹ����죡\n\n");
				break; 
			case 2:
			//ָ��ָ���µ绰�����������֣���ӡ�½��ɹ����˳�
				printf("������绰�����֣�");
				scanf("%s", listname);
				fp = fopen(listname, "w+");
				printf("�½��ɹ��������������\n"); 
				break;
			case 3:
			//Ҫ������绰�����֣����룬����������롣ָ��ָ��򿪵绰�����������򲻿��Ĵ�����������ƴ����������󣩣���ӡ����ɹ����˳� 
				printf("������Ҫ�򿪵ĵ绰�����֣�");
				scanf("%s", listname);
				fp = fopen(listname, "r");
				store(fp); 
				printf("�򿪵绰���ɹ�����������Ĳ�����\n"); 
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
				printf("����ɹ���\n"); 
				break;
			case 5:
			//���������飬�����ʧ�ܣ���ѯ����Ӵ�����Ϣ 
				printf("Ҫ��ʾ��ϵ�˵�������");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				if(Hnumbtmp > 0){
						printf("������%s\t�绰:%s\t��ַ��%s\n", name[Hnumbtmp], numb[Hnumbtmp], addr[Hnumbtmp]);
				}else if(Hnumbtmp == -1){
					printf("����ʧ��\n�Ƿ���Ӵ�����Ϣ����1�س�ȷ�ϣ�����0\n");
					scanf("%d", &tmp);
					if(tmp){
						Hnumbtmp = GetHkey(nametmp);
						Hnumbtmp = CollisionKey(Hnumbtmp); 
						Hflag[Hnumbtmp] = 1; 
						strcpy(&name[Hnumbtmp][0], nametmp);
						printf("���������ϵ��סַ��");
						scanf("%s", addr[Hnumbtmp]);
						printf("��������ϵ�˵绰��");
						scanf("%s", numb[Hnumbtmp]); 
					}
				}		
				break;
			case 6:
			//�������绰��סַ�������ظ��ģ���ѯ���Ƿ񸲸� �����������ֺ�������ֱ�� 
				printf("������������");
				scanf("%s", nametmp);
				if(Hflag[CollisionKey(GetHkey(nametmp))] == 0){
					Hnumbtmp = GetHkey(nametmp);
					Hnumbtmp = CollisionKey(Hnumbtmp); 
					Hnumb[Hnumbtmp] = Hnumbtmp; 
					Hflag[Hnumbtmp] = 1; 
					strcpy(&name[Hnumbtmp][0], nametmp);
					printf("���������ϵ��סַ��");
					scanf("%s", addr[Hnumbtmp]);
					printf("��������ϵ�˵绰��");
					scanf("%s", numb[Hnumbtmp]); 
				}else{
					printf("����ϵ���Ѵ��ڣ��Ƿ񸲸ǣ���1�س�ȷ�ϣ�����0\n");
					scanf("%d", &tmp);
					if(tmp){
						Hnumbtmp = GetHkey(nametmp);
						Hflag[Hnumbtmp] = 1; 
						Hnumb[Hnumbtmp] = Hnumbtmp;
						strcpy(&name[Hnumbtmp][0], nametmp);
						printf("���������ϵ��סַ��");
						scanf("%s", addr[Hnumbtmp]);
						printf("��������ϵ�˵绰��");
						scanf("%s", numb[Hnumbtmp]); 
					}else{
						char plus[2] = {'*'};
						strcat(nametmp, plus);
						Hnumbtmp = GetHkey(nametmp);
						Hnumbtmp = CollisionKey(Hnumbtmp); 
						Hflag[Hnumbtmp] = 1; 
						Hnumb[Hnumbtmp] = Hnumbtmp;
						strcpy(&name[Hnumbtmp][0], nametmp);
						printf("���������ϵ��סַ��");
						scanf("%s", addr[Hnumbtmp]);
						printf("��������ϵ�˵绰��");
						scanf("%s", numb[Hnumbtmp]); 
					} 
				}
				printf("��ӳɹ���\n");					
				break;
			case 7:
			//�޸���ϵ�� 
				printf("Ҫ�޸���ϵ�˵�������");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				printf("�µ绰���룺");
				scanf("%s", numb[Hnumbtmp]); 
				printf("��סַ��");
				scanf("%s", addr[Hnumbtmp]); 
				printf("�޸ĳɹ�"); 
				break;
			case 8:
			//ɾ����ϵ�� 
				printf("������Ҫɾ����ϵ�˵����֣�");
				scanf("%s", nametmp); 
				DeleteHTable(nametmp);
				printf("ɾ���ɹ���\n");	
				break;
			case 9:
			//��ʾ��ϵ���������绰����ַ 
				DisplayHTable();
				break;
			case 10:
			//�޸�flag
				printf("������Ҫ��Ϊ������ϵ�˵����֣�");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				Hflag[Hnumbtmp] = 2; 
				printf("���óɹ���\n");	
				break; 
			case 11:
				for(i = 0; i < 1000; ++i){
					if(Hflag[i] == 2){
						printf("������%8s\t�绰��%8s\t��ַ��%8s\n", name[i], numb[i], addr[i]);
					}
				}
				break;
			case 12:
				printf("������Ҫ���ڵ���ϵ�ˣ�");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				Hflag[Hnumbtmp] = 3; 
				printf("���ڳɹ���\n");	
				break;
			case 13:
				printf("������Ӻ������Ƴ����ˣ�");
				scanf("%s", nametmp);
				Hnumbtmp =  SearchHTable(nametmp);
				Hflag[Hnumbtmp] = 1;
				printf("�Ƴ��ɹ���\n");	 
				break; 
			case 14:
				for(i = 0; i < 1000; ++i){
					if(Hflag[i] == 3){
						printf("������%8s\t�绰��%8s\t��ַ��%8s\n", name[i], numb[i], addr[i]);
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
