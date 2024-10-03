#include <stdio.h>

int main(void)
{
    FILE *fp;
    //int c;
char c;
    fp = fopen("hello.txt", "r");

    // while ((c = fgetc(fp)) != EOF)
       c=fgetc(fp);
        printf("%c", c);

    fclose(fp);
}