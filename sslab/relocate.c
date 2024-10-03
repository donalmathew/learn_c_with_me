#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    
    int i,j;

    //read the file
    FILE *fp=fopen("input.txt","r");
    char line[100];
    fscanf(fp,"%s",line);

    printf("%s",line);

    //print the program name
    char name1[50],name2[50];
    for(i=1,j=0;i<7,j<6;i++,j++) {name1[j]=line[i];} name1[j]='\0';
    printf("\n%s\n",name1);

    //check whether prgrm name is correct
    /*
    printf("enter the name of prgrm");
    scanf("%s",name2);
    if(strcmp(name1,name2)==0){
        printf("file fetched\n");
    } else printf("\nfile not found\n");
    */

    
   //find the existing addr
   char caddr[50];
    for(i=7,j=0;i<13,j<6;i++,j++) {caddr[j]=line[i];} caddr[j]='\0';
    printf("address\n%s\n",caddr);
    //convert to int
    int addr=atoi(caddr);


   //new starting address
   printf("enter the start address");
   int startaddr;
   scanf("%d",&startaddr);

   //new relocating address
   int reloc=addr+startaddr;

    char content[100];
    char segment[100];
    long int isegment;
    char *endpointer;

    while(!feof(fp)){
        
        //read text record
        fscanf(fp,"%s",line);
        //printf("%s\n",line);

        if(line[0]=='T'){

            //finding length of content
            for(i=12,j=0;i!='\0',j<100;i++,j++) {content[j]=line[i];} content[j]='\0';
            printf("\n%s\n",content);
            int l=strlen(content);
            printf("lenfth is %d",l);

            //segments
            int nsegments=l/6;

            //printing each value
            int k,m=12;
            i=6;
            for(k=0;k<nsegments;k++){

                //storing a segemnt
                
                for(i=m,j=0;i<i+6,j<6;i++,j++) {segment[j]=line[i];} segment[j]='\0';

                
                isegment=strtol(segment,&endpointer,16);

                printf("\n[%d]-  %x",reloc,isegment+reloc);
                m+=6;
            }

        }
        else{
            fclose(fp);
            exit(0);
        }
    }

}