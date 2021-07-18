#include<stdio.h>
#include<string.h>
void passStrength(char pass[], char username[]);

void main()
{
    char pass[25];  
    char username[50];
    printf("Enter username\n");
    gets(username);
    printf("Enter Password\n");
    gets(pass);
    passStrength(pass,username);
}


void passStrength(char pass[], char username[])
{
    int i=0, check=0;
    char x;
    int spclSymb=0,num=0,upCase=0,lowCase=0;
    if (pass==username)
        printf("Enter password other than username\n");
    if (strlen(pass)<=8)
        printf("Password must be atleast 8 Characters\n");
    else if (strlen(pass)>20)
        printf("Password must be atmost 20 Characters\n");
    else
    {      
        while (pass[i]!='\0')
        {
            x=(int)pass[i];
            //printf("%d\n",x);
            if  (x>=97 && x<=122)
                lowCase=1;

            if (x>=65 && x<=90)
                upCase=1;

            if (x>=48 && x<=57)
                num=1;
                
            if ((x>=32 && x<=47) || (x>=58 && x<=64) || (x>=91 && x<=96) || (x>=123 && x<=126))  
                spclSymb=1;

            i++;
        } 

    if (lowCase) check+=10;
    if (upCase) check+=10;
    if (num) check+=10;
    if (spclSymb) check+=10;
    
    //printf("%d\n",check);

    if (check==40)
        printf("Excellent Password\n");
    else if (check==30)
        printf("Very Good Password\n");
    else if (check==20)
        printf("Average Password\n");
    else
        printf("Poor Password\n");
    }     
}

