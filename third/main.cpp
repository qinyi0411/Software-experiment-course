#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

//�������״̬����
#define  TRUE                 1
#define  FALSE                0
#define   OK                  1
#define  ERROR                0
#define  INFEASIBLE           -1
#define  OVERFLOW             -2
typedef  int Status;
typedef unsigned long UInt32;
typedef struct {
     UInt32 weight;             // �ڵ�Ȩ��
     int parent,lchild,rchild;  // ˫�׺����Һ��ӽڵ��±�
}HTNode,*HuffmanTree,*HTree;

typedef char**HuffmanCode;      //��������������

/**
 * ��ɭ�����ҳ����������Ȩ����С������
 * ���ҵ����������ĸ������±���l��r���ء�
 * ���   T��ɭ�ֽ������
 *        n��ɭ�ֽ�����鳤��
 */
void Select(HuffmanTree T,int n,int&l,int&r)
{
    //��T��һ��n���ڵ����ҳ�û�н�ϣ���parent=0���Ľڵ���Ȩ��weight��С�������ڵ���±ꣻ��l��r���أ�
    HuffmanTree p=T+1;int a=0,b=0;
    for(int i=1;i<=n;++i,++p){
        if(!p->parent){//�ҳ�˫�׽ڵ�Ϊ�յĽڵ㣻
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
    if(!HT){printf("�ڴ治�㣬����ʧ�ܣ�");exit(OVERFLOW);}
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
        printf("�ڴ治�㣬����ʧ�ܣ�");exit(OVERFLOW);
    }
    char *cd=(char*)malloc(sizeof(char)*n);cd[n-1]='\0';
    for(i=1;i<=n;++i){
        start=n-1;
        for(f=HT[i].parent,c=i; f!=0;c=f,f=HT[f].parent)//Ҷ�������������
            if(HT[f].lchild==c)cd[--start]='0';  else cd[--start]='1';
        HC[i]=(char*)malloc(sizeof(char)*(n-start));
        StrCopy(HC[i],cd+start);
    }
    free(cd);
}

/**
 * �������������
 */
void PrintHuffmanCode(HuffmanCode C,int* s,int n)
{
    char *p;
    for(int i=1;i<=n;++i){
        printf("Ȩ�أ�%3d�����룺", s[i-1]);
        p=C[i];
        while(*p!='\0')
        printf("%c",*p++);
        printf("\n");
    }
}

/**
 * ���ݻ������������������������ַ����н��롣
 */
Status Rewin(HuffmanTree &T,char*s,int*x,int n,int &m)
{
    //����huffman������s��ָ����ַ�������,Ҫ���ַ�����#�������� x ���ؽ����������е��±�, x �� 1 ��ʼ��
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
    int s[20]={7 ,19, 2 ,6 ,32, 3, 21, 10}; // ����Ӧ��Ȩ��
    int x[20],n=8,m;                        // n��Ҷ�ڵ����Ŀ

    HuffmanCode HC;HuffmanTree HT;
    HuffmanCoding(HT,HC,s,n);
    PrintHuffmanCode(HC,s,n);

    printf("\n�������\n");
    char*c="0011101110101#";
    if(Rewin(HT,c,x,n,m))//xΪÿ���ַ���s�е��±�+1��
    printf("���� %s��������Ӧ��Ȩ��ֵ���£�\n", c);
    for(int i=0;i<m;i++)
        printf("%4d ",s[x[i]-1]);
}
#define NAMESIZE 500

void zip(const char*s)
{
    // ʵ��ѹ������
    // s��ΪҪѹ���ĵ�ַ���ļ����� 
    FILE*pr,*pw;    
    int a,i=0 ,w[256],j,n=256,m=2*n-1;
    HuffmanCode HC,hc;HuffmanTree HT;
    char zipname[NAMESIZE]="zip",c=' ';//ѹ�����ѹ���ļ���Ϊzip+ԭ�ļ���+.txt. 
    while(s[i]!='.'){zipname[3+i]=s[i];i++;}
    zipname[3+i]='.';zipname[4+i]='t';zipname[5+i]='x';zipname[6+i]='t';zipname[7+i]='\0';

    pr=fopen(s,"rb");

    if(!pr){
        printf("�ļ���ʧ�ܣ�");exit(1);
    }
    for(int i=0;i<256;i++)w[i]=0;
    a=fgetc(pr);
    while(!feof(pr))
    {
        w[a]++;a=fgetc(pr);
    }
    fclose(pr);

    HuffmanCoding(HT,HC,w,256);//����������飬���潫�ļ�����չ���ͻ�����������ѹ���ļ��У�

    pw=fopen(zipname,"wb");

    //��д����չ�� ����չ��ռ 4 ���ֽڡ� ����4���ÿո�' '����; 
    j=0;
    while(s[++i]){
        fwrite(s+i,1,1,pw);j++;
    }
    while(j++<4)fwrite(&c,1,1,pw);
    //������д����������� 
    for(int i=n+1;i<=m;i++) {
        fwrite(&((HT+i)->lchild),2,1,pw);
        fwrite(&((HT+i)->rchild),2,1,pw);
    }

    //��ʱ���������Ѿ�����ѹ���ļ��С� 
    pr=fopen(s,"rb");//���´��ļ������ļ���ѹ���� 
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
    printf("ѹ���ɹ���\n");

    fclose(pr);fclose(pw);
}

void rezip(const char*s)
{
    // ʵ�ֽ�ѹ����
    // S��Ϊѹ���ļ��ĵ�ַ���ļ�����
    printf("�����ļ���ѹ\n");
    FILE*pr,*pw;    
    int a,i=0,j,n=256,m=2*n-1;UInt32 w[256];
    HuffmanCode HC,hc;HuffmanTree HT;
    char rezipname[NAMESIZE]="re";
    i=0;
    while(s[i]!='.'){rezipname[2+i]=s[i];i++;}
    rezipname[2+i]='.';i++;

    pr=fopen(s,"rb");
    if(!pr){
        printf("�ļ���ʧ�ܣ�");exit(1);
    }
    j=0;a=fgetc(pr);
    while(j<4){
        rezipname[2+i]=a;if(j<3)a=fgetc(pr);j++;i++;
    }
    HT=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));
    HT[0].weight=0;HT[0].parent=0;HT[0].lchild=0;HT[0].rchild=0;
    for(i=1;i<=n;i++){
        HT[i].weight=0;//��ʱ����ҪȨ�أ����Կ�����㸳ֵ�� 
        HT[i].lchild=0;
        HT[i].rchild=0;
    }

    for(i=n+1;i<=m;i++)
    {
        HT[i].weight=0;//��ʱ����ҪȨ�أ����Կ�����㸳ֵ�� 
        fread(&a,2,1,pr);HT[i].lchild=a;HT[a].parent=i;
        fread(&a,2,1,pr);HT[i].rchild=a;HT[a].parent=i;
    }
    HT[m].parent=0;
    //��ʱHTΪ����������

    // �������¶�ȡԭ�ļ�����Huffman���õ���Ӧ��Huffman���룬д��ѹ������ļ���
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
    printf("��ѹ�ɹ���\n");
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
	printf("-------------�ı�ѹ�����-------------\n\t\t\t\t�����ߣ���� 2016060107008\n");	
	printf("�������������1���س�ѹ���ļ�����2���س���ѹ�ļ�\n");
	scanf("%d", &tmp);
	switch(tmp){
		case 1:
			printf("������Ҫѹ�����ļ�����\n");
		    scanf("%s", s);
		    strcat(str2,s);    
		    mainHuffmantree();
	        zip(s);
		break;
		case 2:
			printf("������Ҫ��ѹ���ļ�����\n");
		    scanf("%s", s);
		    strcat(str2,s);    
		    mainHuffmantree();
		    rezip(str2);
		break;
	}
    return 0; 
}
*/
