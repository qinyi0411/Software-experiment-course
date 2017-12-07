#include <stdio.h>
#include<stdlib.h>
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
}


int main()
{
    char name[20];
    struct store text[10000];
    printf("请输入要压缩的文件名：\n")；
    scanf("%s"， name)；
    FILE* fp；
    fp = fopen(name, "r")；
    Text_compress(fp)；
    fclose(fp);
    return 0;
}
