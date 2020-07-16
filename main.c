#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <err.h>

int array[] = {1,2,3,4,5};

#define N  5
int results[N] = {0}; //保存已经找到的结果前缀数组
int results_end = 0; //结果前缀数组有效数据下标
int permcount=0;
int is_used[N] = {0}; //是否已经排列过了的标志

/**
 * 排列
 * @param deep 递归深度
 * @param n 数组最大长度
 */
void perm(int deep, int n,int **order)
{
    // printf("deep:%d,n:%d\n",deep,n);
    int i;
    if (deep > n) // 越界递归结束
    {
        return;
    }

    if (deep == n) // 找到结果，打印，递归结束
    {
        // printf("permcount:%d\n",permcount);
        for (i = 0; i < n; i++)
        {
            // printf("%d", results[i]);
            order[permcount][i] = results[i];
        }
        permcount++;
        // printf("\t");
        return ;
    }

    for (i = 0; i < n; i++)
    {
        if (is_used[i] == 0)
        {
            is_used[i] = 1;
            results[deep] = array[i];
            perm(deep+1, n,order);
            is_used[i] = 0;
        }
    }
}


static void printfbuffer(char **buffer){
    for (int i = 0; i < 100; i++){
        printf("No %d:",i+1);
        for(int t = 0; t<100; t++){
            printf("%c",buffer[i][t]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    int i,t;
    int **order;
    char **buffer;
    FILE * pf;
    if ((pf = fopen("count5/sample.txt", "w")) == NULL)
		err(1, "%s", "sample.txt");

    buffer = malloc(sizeof(char*)*5);
    for (i = 0; i < 5; i++){
        buffer[i] = malloc(sizeof(char)*100);
    }

    order = malloc(sizeof(int*)*120);
    for (i = 0; i < 120; i++){
        order[i] = malloc(sizeof(int)*5);
    }

    for (i = 0; i < 5; i++){
        for(t = 0; t<100; t++){
            buffer[i][t] = 'a'+rand()%26;
        }
    }
    for (i = 0; i < 5; i++){
        fprintf(pf,"No %d:",i);
        fwrite(buffer[i], 100, 1, pf);
        fprintf(pf,"\n");
    }

    if (fclose(pf))
		err(1, "fclose");

    // printfbuffer(buffer);


    perm(0, N,order);
    printf("perm finish\n");
    char *filename;
    filename = malloc(100);
    for(i=0;i<120;i++){
        sprintf(filename, "%s%d%d%d%d%d.txt", "count5/",order[i][0],order[i][1],order[i][2],order[i][3],order[i][4]);
        printf("%s\n",filename);
        if ((pf = fopen(filename, "w")) == NULL)
		    err(1, "%s", "sample.txt");
        for(t=0;t<5;t++){
            fwrite(buffer[order[i][t]-1], 100, 1, pf);
        }
        if (fclose(pf))
		err(1, "fclose");
    }

    return 0;
    
} 