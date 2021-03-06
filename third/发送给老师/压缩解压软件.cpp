#include <stdio.h>
#include <cstdlib>
#include <windows.h>
typedef int ElemType;  
typedef struct BTreeNode  
{  
    ElemType data;  
    ElemType data2;
    struct BTreeNode* left;  
    struct BTreeNode* right;  
}BTreeNode;
int qj=0;

BTreeNode* CreateHuffman(int a[][2], int n)  
	{  
	    int i, j;  
	    BTreeNode **b, *q=NULL;  
	    b =  (BTreeNode **)malloc(n*sizeof(BTreeNode));  
	    for (i = 0; i < n; i++)                          
	    {  
	        b[i] = (BTreeNode *)malloc(sizeof(BTreeNode));  
	        b[i]->data = a[i][1];
			b[i]->data2 = a[i][0];  
	        b[i]->left = b[i]->right = NULL;  
	    }  
	    for (i = 1; i < n; i++)  
	    {  
	        //k1表示森林中具有最小权值的树根结点的下标，k2为次最小的下标  
	        int k1 = -1, k2;  
	        for (j = 0; j < n; j++)                      //让k1初始指向森林中第一棵树，k2指向第二棵  
	        {  
	            if (b[j] != NULL && k1 == -1)  
	            {  
	                k1 = j;  
	                continue;  
	            }  
	            if (b[j] != NULL)  
	            {  
	                k2 = j;  
	                break;  
	            }  
	        }  
	        for (j = k2; j < n; j++)                 //构造最优解  
	        {  
	            if (b[j] != NULL)  
	            {  
	                if (b[j]->data < b[k1]->data)  
	                {  
	                    k2 = k1;  
	                    k1 = j;  
	                }  
	                else if (b[j]->data < b[k2]->data)  
	                    k2 = j;  
	            }  
	        }  
	        q = (BTreeNode *)malloc(sizeof(BTreeNode));  
	        q->data = b[k1]->data + b[k2]->data;  
	        q->left = b[k1];  
	        q->right = b[k2];  
	  
	        b[k1] = q;  
	        b[k2] = NULL;  
	    }  
	    free(b);   
	    return q;   
	}

BTreeNode* unzip(BTreeNode *node,char flag){
	if(flag == 0)
	return node->left;
	if(flag == 1)
	return node->right;
} 


void HuffManCoding(BTreeNode* FBT, int len,char HuffNode[][20])  
{  
    static char a[20];  
    if (FBT != NULL)      
    {  
        if (FBT->left == NULL && FBT->right == NULL)  
        {  
            int i;   
            HuffNode[qj][0]=FBT->data2;
			for(i=1;i<len+1;i++)
				HuffNode[qj][i]= a[i-1];
			HuffNode[qj][len+1]='|';

   			printf("ASCII码为%d的编码：",HuffNode[qj][0]);  
            for (i = 1; i < len+1; i++)  
                printf("%d", HuffNode[qj][i]);  
            printf("\n"); 
 			qj++;
        }  
        else  
        {     
            a[len] = (00000000);  
            HuffManCoding(FBT->left, len + 1,HuffNode);  
            a[len] = (00000001);  
            HuffManCoding(FBT->right, len + 1,HuffNode);  
        }  
    } 
}
int main(int argc, char *argv[])
{
	printf("-------------文本压缩软件-------------\n\t\t\t\t制作者：覃翊 2016060107008\n");	
	int data[256][2];
	for(int i=0;i<256;i++) 
		for(int j=0;j<2;j++)
			data[i][j]=0;
	int n=0;int i=0;
	char m;
	freopen("data.txt","rb",stdin);
	while(scanf("%c",&m)!=EOF){
		int biaoji=0;
		m=(int)m;
		for(int j=0;j<=n;j++)
			{
				if(data[j][0]==m)
				{
					data[j][1]=data[j][1]+1;biaoji=1;break;
				}
			}
		if(biaoji==0)
		{
			data[n][0]=m;data[n][1]=1;n++;
		}
	}
	/* 
	for(int i=0;i<n;i++) 
			for(int j=0;j<2;j++)
				printf("%d ",data[i][j]);
	printf("\n");
	*/
	fclose(stdin);
	BTreeNode* hfm;
	hfm=CreateHuffman(data,n);
	
	char HuffNode[256][20];
    HuffManCoding(hfm,0,HuffNode);


/*
    for(int i=0;i<=25;i++)
    	for(int j=0;HuffNode[i][j]!='|';j++)
    		printf("%c ",HuffNode[i][j]);*/


	int length=0;
	int length1=0;
	FILE *fpr = fopen("data.txt","rb");
	FILE *fpw = fopen("zip.txt","wb");
	char zifu;
	unsigned char savechar=0;
	int num=0; 
	while((zifu=fgetc(fpr))!=EOF){
		//printf("%c",zifu);
		length++;
    		for(i=0;i<256;i++){              //变成int i=0后出现bug 
    			if(zifu==HuffNode[i][0]) break;}
			//printf("%d ",i);
			for(int j=1;HuffNode[i][j]!='|';j++){
				savechar=savechar+HuffNode[i][j];
				//printf("%d ",savechar);
				num++;
				if(num==8){
					fwrite(&savechar,sizeof(char),1,fpw);
					savechar=0;
					num=0;
					length1++;
					//printf("OK");
				}
				else{
					savechar=savechar<<1;
				}
			}
	}
	if(num != 8){
	savechar = savechar<<(7-num);
	fwrite(&savechar,sizeof(char),1,fpw);
	length1++;
	}
	fclose(fpr);
	fclose(fpw);
	int counttime = 20;
	printf("\n");
	printf("正在压缩，请稍等\n压缩进度："); 
	while(counttime > 0){
		printf("■");
		Sleep(counttime*10);
		counttime--; 
	} 
	printf("\n");
	printf("\n压缩完成！压缩文件名为：zip.txt\n");
	
	printf("\n下面开始解压\n");
	int changdu=0;
	FILE *fpr1= fopen("zip.txt","rb");
//	fseek(fpr1,0L,SEEK_SET);
	FILE *fpw1 = fopen("unzip.txt","w");
	unsigned char op=(10000000);unsigned char s;
	BTreeNode *z=hfm; 
	int x=0;
	while(x!=length1){
		zifu=fgetc(fpr1);
		x++;
		for(int k=0;k<8;k++){
			s=op&zifu;
			s=s>>7;
			zifu=zifu<<1;                                        
			z=unzip(z,s);
			if(z->left == NULL || z->right == NULL){
				fprintf(fpw1,"%c",z->data2);
				z=hfm;
				changdu++;
			}
			if(changdu==length)break;
		}
	
	}
//	printf("%d %d",length,changdu); 
	fclose(fpr1);
	fclose(fpw1);
	counttime = 20;
	printf("\n解压中，请稍等\n解压进度：");
	while(counttime > 0){
		printf("■");
		Sleep(counttime*10);
		counttime--; 
	} 
	printf("\n");
	printf("\n解压完成！请到文件中查看解压后内容\n");
	Sleep(8000);
	return 0;
}
