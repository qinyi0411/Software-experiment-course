#include <stdio.h>
#include<stdlib.h>
#define MAXBIT 10
#define MAXVALUE 1000

typedef struct HNode{/*定义节点结构*/
    int weight;
    int parent, lchild, rchild;
} HNode;

void HuffmanCoding ( HNode *HT, HCode *HC, int *w, int n){
    /*w存放n个字符的权值，构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC。*/
    if(n<=1) return;

    m=2*n-1;
    /*哈夫曼树的构造*/
    HT=(HNode *) malloc(m)*sizeof(HNode);

    for(p=HT,i=1; i<n; ++i, ++p, ++w){ /*初始化叶子节点信息*/
        (*p)->weight=*w; (*p)->lchild=-1; (*p)->rchild=-1; (*p)->parent=-1;
    }

    for(; i<m; ++i, ++p){ /*初始化分支节点信息*/
        (*p)->weight=0; (*p)->lchild=-1; (*p)->rchild=-1; (*p)->parent=-1;
    }

    for(i=n; i<m; ++i){ /*寻找根节点权值最小和次小的两棵子树*/
        m1=m2=MAXVALUE;
        x1=x2=0;
        for(j=0; j<i; ++j){
            if (HT[j].parent==-1 &&HT[j].weight<m1){
                m2=m1; x2=x1; m1=HT[j].weight; x1=j;}
            else if( HT[j].parent==-1 && HT[j].weight<m2){
                m2=HT[j].weight; x2=j;}
            }
        /*合并成一棵新的子树*/
        HT[x1].parent=i; HT[x2].parent=i;
        HT[i].lchild=x1; HT[i].rchild=x2;
        HT[i].weight=m1+m2;
    }

    /*字符编码*/
    HC=(HCode *) malloc(n)*sizeof(HCNode);

    for(i=0;i<n;++i){
        start=n-1;
        for(c=i, f=HT[i].parent; f!=-1; c=f,f=HT[f].parent)
            if(HT[f].lchild=c) HC[i].bit[start--]=0;
            else HC[i].bit[start--]=1;
        HC[i].start=start+1; /*记录编码的起始位置*/
    }
}





struct store{
    char c;
    int freq = 0;
} ;
void Text_compress(FILE *fp){
    int i = 0,j;
    char chartmp;
    while(fp != EOF){
        fscanf(fp, "%c", &chartmp); //底下各种i，j需要慢慢推敲
        for(j = 0; j < i + 1; ++j){
            if(chartmp != text[j].c && j == i - 1){
                i++;
                text[i].c = chartmp;
                text[i].freq = 1;
            }else if(chartmp == text[j].c){
                text[j].freq++;
                break;
            }
        }
    }
    for(i = 0; i < 100; ++i){
        if(text[i].freq > 0){
            printf("%c 出现了 %d 次.\n", text[i].c, text[i].freq);
        }
    }
}



typedef struct HCode{/*哈夫曼编码结构*/
    int bit [MAXBIT];
    int start;
} HCode;




int main()
{
    char name[20];
    struct store text[100];
    printf("请输入要压缩的文件名：\n")；
    scanf("%s"， name)；
    FILE* fp；
    fp = fopen(name, "r")；
    Text_compress(fp)；
    fclose(fp);
    return 0;
}
