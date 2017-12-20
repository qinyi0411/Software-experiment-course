#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

//函数结果状态代码
#define  TRUE                 1
#define  FALSE                0
#define   OK                  1
#define  ERROR                0
#define  INFEASIBLE           -1
#define  OVERFLOW             -2
typedef  int Status;
typedef unsigned long UInt32;
typedef struct {
     UInt32 weight;             // 节点权重
     int parent,lchild,rchild;  // 双亲和左右孩子节点下标
}HTNode,*HuffmanTree,*HTree;

typedef char**HuffmanCode;      //霍夫曼编码类型

/**
 * 从森林中找出两个根结点权重最小的树。
 * 将找到的两棵树的根结点的下标用l和r带回。
 * 入参   T：森林结点数组
 *        n：森林结点数组长度
 */
void Select(HuffmanTree T,int n,int&l,int&r)
{
    //从T的一到n个节点中找出没有结合（即parent=0）的节点中权重weight最小的两个节点的下标；用l，r带回；
    HuffmanTree p=T+1;int a=0,b=0;
    for(int i=1;i<=n;++i,++p){
        if(!p->parent){//找出双亲节点为空的节点；
            if(!a){l=i;a=1;}
            else if(!b){r=i;b=1;}
            else if(p->weight<(T+l)->weight||p->weight<(T+r)->weight){
                if((T+l)->weight<=(T+r)->weight)r=i;
                else l=i;
            }
        }
    }
}

void StrCopy(char*str,const char*c)
{
    char *s=str;
    while(*c!='\0')*s++=*c++;
    *s='\0';
}

/**
 *
 */
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
    int f,c,start,m1,m2,i,m=2*n-1;HuffmanTree p;
    HT=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));
    if(!HT){printf("内存不足，操作失败！");exit(OVERFLOW);}
    for(p=HT+1,i=1;i<=n;++i,++w,++p){
        p->weight=*w;p->parent=0;p->lchild=0;p->rchild=0;
    }
    for(i=n+1;i<=m;++i,++p){
        p->weight=0;p->parent=0;p->lchild=0;p->rchild=0;
    }
    for(i=n+1,p=HT+i;i<=m;++i,++p){
        Select(HT,i-1,m1,m2);
        p->weight=(HT+m1)->weight+(HT+m2)->weight;
        p->lchild=m1;p->rchild=m2;
        (HT+m1)->parent=i;(HT+m2)->parent=i;
    }

    //for(i=1;i<=m;i++)
    //printf("%d  %d  %d  %d  ",HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);

    HC=(HuffmanCode)malloc(sizeof(char*)*(n+1));
    if(!HC){
        printf("内存不足，操作失败！");exit(OVERFLOW);
    }
    char *cd=(char*)malloc(sizeof(char)*n);cd[n-1]='\0';
    for(i=1;i<=n;++i){
        start=n-1;
        for(f=HT[i].parent,c=i; f!=0;c=f,f=HT[f].parent)//叶到根逆向求编码
            if(HT[f].lchild==c)cd[--start]='0';  else cd[--start]='1';
        HC[i]=(char*)malloc(sizeof(char)*(n-start));
        StrCopy(HC[i],cd+start);
    }
    free(cd);
}

/**
 * 输出霍夫曼编码
 */
void PrintHuffmanCode(HuffmanCode C,int* s,int n)
{
    char *p;
    for(int i=1;i<=n;++i){
        printf("权重：%3d，编码：", s[i-1]);
        p=C[i];
        while(*p!='\0')
        printf("%c",*p++);
        printf("\n");
    }
}

/**
 * 根据霍夫曼树，将霍夫曼编码后的字符进行解码。
 */
Status Rewin(HuffmanTree &T,char*s,int*x,int n,int &m)
{
    //根据huffman树，将s所指向的字符串解码,要求字符串以#结束。用 x 带回解码在数组中的下标, x 从 1 开始。
    HuffmanTree p=T+2*n-1;m=0;
     while(*s!='#'){
         if(*s=='0'&&p->lchild)p=T+p->lchild;
         else if(*s=='1'&&p->rchild)p=T+p->rchild;
//       else return FALSE;
         if(!p->lchild&&!p->rchild){
            if(*s=='0')*x=(T+p->parent)->lchild;
            else *x=(T+p->parent)->rchild;
            x++;p=T+2*n-1;m++;
        }
        s++;
    }
    return OK;
}

int huffmantree()
{
    int s[20]={7 ,19, 2 ,6 ,32, 3, 21, 10}; // 结点对应得权重
    int x[20],n=8,m;                        // n：叶节点的数目

    HuffmanCode HC;HuffmanTree HT;
    HuffmanCoding(HT,HC,s,n);
    PrintHuffmanCode(HC,s,n);

    printf("\n解码测试\n");
    char*c="0011101110101#";
    if(Rewin(HT,c,x,n,m))//x为每个字符在s中的下标+1；
    printf("编码 %s，解码后对应的权重值如下：\n", c);
    for(int i=0;i<m;i++)
        printf("%4d ",s[x[i]-1]);
}
#define NAMESIZE 500

void zip(const char*s)
{
    // 实现压缩功能
    // s：为要压缩的地址和文件名。 
    FILE*pr,*pw;    
    int a,i=0 ,w[256],j,n=256,m=2*n-1;
    HuffmanCode HC,hc;HuffmanTree HT;
    char zipname[NAMESIZE]="zip",c=' ';//压缩后的压缩文件名为zip+原文件名+.txt. 
    while(s[i]!='.'){zipname[3+i]=s[i];i++;}
    zipname[3+i]='.';zipname[4+i]='t';zipname[5+i]='x';zipname[6+i]='t';zipname[7+i]='\0';

    pr=fopen(s,"rb");

    if(!pr){
        printf("文件打开失败！");exit(1);
    }
    for(int i=0;i<256;i++)w[i]=0;
    a=fgetc(pr);
    while(!feof(pr))
    {
        w[a]++;a=fgetc(pr);
    }
    fclose(pr);

    HuffmanCoding(HT,HC,w,256);//求出霍夫曼书，下面将文件的扩展名和霍夫曼树存入压缩文件中；

    pw=fopen(zipname,"wb");

    //先写入扩展名 ，扩展名占 4 个字节。 不足4个用空格' '补齐; 
    j=0;
    while(s[++i]){
        fwrite(s+i,1,1,pw);j++;
    }
    while(j++<4)fwrite(&c,1,1,pw);
    //下面是写入霍夫曼树。 
    for(int i=n+1;i<=m;i++) {
        fwrite(&((HT+i)->lchild),2,1,pw);
        fwrite(&((HT+i)->rchild),2,1,pw);
    }

    //此时霍夫曼树已经存入压缩文件中。 
    pr=fopen(s,"rb");//重新打开文件遍历文件进压缩。 
    a=fgetc(pr);
    i=0;int b=0;hc=HC;char*p=*(hc+a+1);
    while(!feof(pr)||*p!='\0')
    {
        for(i=0;i<8;i++){
            if(*p=='\0'){
                a=fgetc(pr);
                if(a>=0)p=hc[a+1];
                else {
                        int h=1;
                        for(int j=0;j<8-i;j++)h=h*2;
                        b=b*h;break;
                    }
            }
            int h=1;
            for(int j=0;j<7-i;j++)h=h*2;
            b=b+(*p-48)*h;
            ++p;
        }
        fwrite(&b,1,1,pw);b=0;
    }
    printf("压缩成功！\n");

    fclose(pr);fclose(pw);
}

void rezip(const char*s)
{
    // 实现解压功能
    // S：为压缩文件的地址和文件名。
    printf("进行文件解压\n");
    FILE*pr,*pw;    
    int a,i=0,j,n=256,m=2*n-1;UInt32 w[256];
    HuffmanCode HC,hc;HuffmanTree HT;
    char rezipname[NAMESIZE]="re";
    i=0;
    while(s[i]!='.'){rezipname[2+i]=s[i];i++;}
    rezipname[2+i]='.';i++;

    pr=fopen(s,"rb");
    if(!pr){
        printf("文件打开失败！");exit(1);
    }
    j=0;a=fgetc(pr);
    while(j<4){
        rezipname[2+i]=a;if(j<3)a=fgetc(pr);j++;i++;
    }
    HT=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));
    HT[0].weight=0;HT[0].parent=0;HT[0].lchild=0;HT[0].rchild=0;
    for(i=1;i<=n;i++){
        HT[i].weight=0;//此时不需要权重，所以可以随便赋值。 
        HT[i].lchild=0;
        HT[i].rchild=0;
    }

    for(i=n+1;i<=m;i++)
    {
        HT[i].weight=0;//此时不需要权重，所以可以随便赋值。 
        fread(&a,2,1,pr);HT[i].lchild=a;HT[a].parent=i;
        fread(&a,2,1,pr);HT[i].rchild=a;HT[a].parent=i;
    }
    HT[m].parent=0;
    //此时HT为霍夫曼树。

    // 下面重新读取原文件根据Huffman树得到对应的Huffman编码，写入压缩后的文件。
    int gm=0;
    char aa[80000],b[8];int x[10000],d;a=fgetc(pr);
    while(!feof(pr))
    {
            for(int i=0;i<8;i++){
                if(a){
                    b[7-i]=48+a%2;
                    a=a/2;
                }
                else b[7-i]='0';
            }
            for(int i=0;i<8;i++){
                aa[8*j+i]=b[i];
            }
            j++;
            d=a;
            a=fgetc(pr);
    }
    for(i=0;i<8;i++){
        if(a){
            b[7-i]=48+a%2;
            a=a/2;
        }
        else break;
    }
    for(int k=0;k<i;k++){
        aa[8*j-8+k]=b[8-i+k];
    }

    aa[8*j-8+i]='0';
    aa[8*j-8+i+1]='#';

    Rewin(HT,aa,x,n,gm);
    FILE *fw;

    fw=fopen(rezipname,"wb");
    for(int i=0;i<gm;i++)
    {x[i]=x[i]-1;fwrite(x+i,1,1,fw);}
    fclose(fw);fclose(pr);
    printf("解压成功！\n");
}
int main()
{
    const char*s="mystring.txt";
    const char*str2="zipmystring.txt";
    huffmantree();
    zip(s);
    rezip(str2);
    return 0; 
}
/*
int main()
{	
	int tmp;
	char*s;
	char*str2="zip";
	printf("-------------文本压缩软件-------------\n\t\t\t\t制作者：覃翊 2016060107008\n");	
	printf("请输入操作，按1并回车压缩文件，按2并回车解压文件\n");
	scanf("%d", &tmp);
	switch(tmp){
		case 1:
			printf("请输入要压缩的文件名：\n");
		    scanf("%s", s);
		    strcat(str2,s);    
		    mainHuffmantree();
	        zip(s);
		break;
		case 2:
			printf("请输入要解压的文件名：\n");
		    scanf("%s", s);
		    strcat(str2,s);    
		    mainHuffmantree();
		    rezip(str2);
		break;
	}
    return 0; 
}
*/
