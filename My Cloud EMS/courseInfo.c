#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int choice;    // Used as an argument in getUserType() function.
char pass[30]; // To store password of user.
FILE *fPtr;    // To store returned address of fopen function.

struct CourseInfo // To store Course Info.
{
    char dgreName[30], brnchName[40], spclName[50], subName[50], subType[10],profName[40],subCode[10];
    int year;
    float subCredit;
} info, cInfo;

struct PrsnlInfo // To store personal details of Students and Employee
{
    char fstName[20], lstName[20], name[41], sex[10];
    char eMail[40], CurAdrs[100], PermAdrs[100], uniMailId[40];
    char qlifcn[100];
    char dob[10];
    unsigned long long sysID, mobNum;

} stud, emp; // stud->Student's Variable; emp->Employee's Variable

struct parentsInfo // To store Parents detail of Student
{
    char fthrName[40], mthrName[40], prntMail[40];
    unsigned long long prntMobNum;
} prnt;

struct classInfo
{
    int batch;
    char section[6], group[4];
} enrl;

//List of Function used in the program:-

const char *getUserType();
void setPass();
const char *passStrength(unsigned long long sysID, char pass[]);
void passDB();
const char *verifyAcc(unsigned long long sysID, char pass[25]);


const char *getUserType(int choice) //Returns pointer to character which store adddress of string. Returns User Type
{
    if (choice == 1)
    {
        return "Student";
    }
    else if (choice == 2)
    {
        return "Employee";
    }
    else if (choice == 0)
    {
        exit(0);
    }
    else
    {
        return "Again";
    }
}

void setPass(unsigned long long sysID) // Sets New Password for the user.
{
    char confirmPass[30];
    while (1)
    {
        printf("Enter Password: ");
        scanf("%s", &pass);
        // Checks the strength of password.
        const char *strngth = passStrength(sysID, pass);
        printf("Password Strength: %s\n", strngth);
        if (strcmp(strngth, "Poor") == 0)
        {
            printf("Choose a strong password\n");
        }
        else if (strcmp(strngth, "Length Error") == 0)
        {
            printf("Length of password must be between 8-25 characters\n");
        }
        else
        {
            break;
        }
    }
    printf("Confirm Password: ");
    scanf("%s", &confirmPass);
    if (strcmp(confirmPass, pass) != 0)
    {
        printf("\nPassword does not match!!!");
        printf("\nTry Again... \n");
        setPass(sysID); // Recursion
    }
    else
    {
        if (strcmp(getUserType(choice), "Employee") == 0)
        {
            passDB(emp.sysID, pass, choice); // Passed Employee's System ID
        }
        if (strcmp(getUserType(choice), "Student") == 0)
        {
            passDB(stud.sysID, pass, choice); // Passed Student's System ID
        }
    }
}


const char *passStrength(unsigned long long sysID, char pass[25])
{
    while (1)
    {
        int i = 0, strength = 0;
        char x;
        int spclSymb = 0, num = 0, upCase = 0, lowCase = 0;
        if (strlen(pass) < 8 || strlen(pass) > 25)
        {
            return "Length Error";
        }
        else
        {
            while (pass[i] != '\0')
            {
                x = (int)pass[i];
                if (x >= 97 && x <= 122)
                    lowCase = 1;

                if (x >= 65 && x <= 90)
                    upCase = 1;

                if (x >= 48 && x <= 57)
                    num = 1;

                if ((x > 32 && x <= 43) || (x >= 91 && x <= 96) || (x == 64))
                    spclSymb = 1;

                i++;
            }
            if (lowCase)
                strength += 10;
            if (upCase)
                strength += 10;
            if (num)
                strength += 10;
            if (spclSymb)
                strength += 10;

            if (strength == 40)
            {
                return "Excellent";
            }
            else if (strength == 30)
            {
                return "Average";
            }
            else
            {
                return "Poor";
            }
        }
    }
}
void passDB(unsigned long long sysID, char pass[], int choice) // Store ID Password into respective database
{
    if (strcmp(getUserType(choice), "Employee") == 0)
    {
        fPtr = fopen("EmpPassDataBase.txt", "a"); // Opening Employee's Database
    }
    else if (strcmp(getUserType(choice), "Student") == 0)
    {
        fPtr = fopen("StPassDataBase.txt", "a"); // Opening Stident's Database
    }
    else
    {
        printf("ERROR... Can't find database:(");
    }
    if (fPtr == NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        fprintf(fPtr, "\n%llu,%s", sysID, pass); // Writing id pass into text file
        fclose(fPtr);                            // Closing text file
        printf("\nPassword has been Set.");
    }
    fPtr = NULL; // Resetting FILE pointer to NULL
}


const char *verifyAcc(unsigned long long sysID, char pass[25])
{
    char ch,st[50], id[12], oPass[25];      // To store data from file
    if (fPtr==NULL)
    {
        return "File Error";
    }
    else
    {
        while (1)
        {
            ch = fgetc(fPtr);         //Reading the first character and moving the cursor to next one
            if(ch==EOF)
            {
                return "EOF Error";
                break;
            }
            else
            {
                fscanf(fPtr, "%[^\n]", st); // Reading line from file
                char* tok = strtok(st,",");     // Splitting the string 
                strcpy(id,tok);
                while(tok!=NULL)
                {
                    if (sysID==atoi(id))      // Convirting string to int and comparing
                    {
                        tok = strtok(NULL,",");     // Accessing next token
                        strcpy(oPass,tok);          
                        if (strcmp(pass,oPass)==0)
                        {
                            return "Matched";
                            break;  
                        }
                        else
                        { 
                            return "Wrong Password";
                            break;
                        }  
                    }
                    break;                   
                }
            }
        }
    }
    fclose(fPtr);
    fPtr==NULL;
}





void accInfoDB(unsigned long long sysID, char name[41])                 // Function for printing the Academic details
{
    fPtr = fopen("StudAccDtlsDB.txt", "a");
    if (fPtr == NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        int i;

        fprintf(fPtr, "\n\nName: %s\n",name);

        fprintf(fPtr, "System Id: %llu\n",sysID);

        fprintf(fPtr, "\tDegree Name: %s\n",info.dgreName);

        fprintf(fPtr, "\tBatch: %llu\n",enrl.batch);

        fprintf(fPtr, "\tBranch name: %s\n",info.brnchName);

        fprintf(fPtr, "\tSpecialization: %s\n", info.spclName);

        fprintf(fPtr, "\tSection: %s\n",enrl.section);

        fprintf(fPtr, "\tGroup: %s\n",enrl.group);

        for (i = 0; i < 120; i++)
        {
            fprintf(fPtr, "_");
        }
        fclose(fPtr);
        printf("\nCourse info Set\n");
    }
    fPtr = NULL;
}

void SetStudAccDetls(unsigned long long sysID, char name[41])       // Function for Entering the Academic details
{
    printf("Batch Year: ");
    scanf("%llu", &enrl.batch);

    printf("Degree Name : ");
    scanf("\n");
    scanf("%[^\n]%*c", info.dgreName);

    printf("Branch Name : ");
    scanf("\n");
    scanf("%[^\n]%*c", info.brnchName);

    printf("Specialization [Specialization Name/None]:\n");
    scanf("%[^\n]%*c", info.spclName);

    printf("Assign Section: ");
    scanf("%[^\n]%*c", enrl.section);

    printf("Assign Group: ");
    scanf("%[^\n]%*c", enrl.group);

    accInfoDB(sysID, name);
}

void prsnlInfoDb(unsigned long long sysID, char name[41])                // Function for printing the Personal details
{
    fPtr = fopen("StudPrsnlInfo.txt", "a");
    if (fPtr == NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        int i;

        fprintf(fPtr, "\nSystem Id: %llu",sysID);
        fprintf(fPtr, "\nName: %s\n",name);
        fprintf(fPtr, "\nPersonal Details \n");
        fprintf(fPtr, "\tDate of birth: %s\n",stud.dob);
        fprintf(fPtr, "\tGender: %s\n",stud.sex);
        fprintf(fPtr, "\tMobile Num: %llu \n",stud.mobNum);

        fprintf(fPtr, "\tUniversity Mail-Id: %s\n ",stud.uniMailId);

        fprintf(fPtr, "\tPersonal Mail-ID: %s\n",stud.eMail);

        fprintf(fPtr, "\nParents Info:-\n ");

        fprintf(fPtr, "\tFathers Name: %s\n", prnt.fthrName);
        fprintf(fPtr, "\tMothers Name: %s\n",prnt.mthrName);
        fprintf(fPtr, "\tMobile Num: %llu\n",prnt.prntMobNum);
        fprintf(fPtr, "\tE-Mail ID: %s\n\n",prnt.prntMail);
        fprintf(fPtr, "Qualification: %s \n",stud.qlifcn);

        fprintf(fPtr, "Address:-\n");

        fprintf(fPtr, "\tCurrent: %s\n",stud.CurAdrs);
        fprintf(fPtr, "\tPermanent: %s\n",stud.PermAdrs);

        for (i = 0; i < 120; i++)
        {
            fprintf(fPtr, "_");
        }
        fclose(fPtr);
        printf("\nInformation Set Successfully\n");
    }
    fPtr = NULL;
}

void GetStudPrsnlDetls(unsigned long long sysID, char name[41])           // Function for ENtering the Personal details
{

    printf("Date of birth: ");
    scanf("\n");
    scanf("%[^\n]%*c", stud.dob);

    printf("\nGender: ");
    scanf("%[^\n]%*c", stud.sex);

    printf("\nfathers Name: ");
    scanf("%[^\n]%*c", prnt.fthrName);

    printf("\nMothers Name: ");
    scanf("%[^\n]%*c", prnt.mthrName);

    printf("\n\nEnter Mobile number:\n");
    printf("\nStudent:- ");
    scanf("%llu", &stud.mobNum);

    printf("\nParents:- ");
    scanf("%llu", &prnt.prntMobNum);

    printf("\n\nEnter E-Mail ID:\n");
    printf("\nPersonal mail-Id- Student: ");
    scanf("\n");
    scanf("%[^\n]%*c", stud.eMail);

    printf("\nPersonal mail-Id- Parents: ");
    scanf("%[^\n]%*c", prnt.prntMail);

    printf("\nUniversity mail-Id for student: ");
    scanf("%[^\n]%*c", stud.uniMailId);

    printf("\n\nQuallification: ");
    scanf("%[^\n]%*c", stud.qlifcn);

    printf("\n\nAdderess: \n");

    printf("\nCurrent: ");
    scanf("%[^\n]%*c", stud.CurAdrs);

    printf("\nPermanenet: ");
    scanf("%[^\n]%*c", stud.PermAdrs);

    prsnlInfoDb(sysID, name);
}
void corsDtabs(int year, char dgreName[15],char brnchName[40],char subName[50],char subCode[10],int subCredit,char subType[10], char profName[40])
{
    fPtr = fopen("CourseDetails_database.txt","a");
    if (fPtr==NULL)
    {
        printf("Can't Open a file\n");
        exit(1);
    }
    else
    {
        fflush(stdin);
        int k;               
        fprintf(fPtr, "\nYear: %d\n",year);
        fprintf(fPtr, "Degree Name: %s\n",dgreName);
        fprintf(fPtr, "Branch Name: %s\n",brnchName);
        fprintf(fPtr, "Subject Name: %s\n",subName);
        fprintf(fPtr, "Subject Code: %s\n",subCode);
        fprintf(fPtr, "Subject Credit: %d\n",subCredit);
        fprintf(fPtr, "Subject Type: %s\n",subType);
        fprintf(fPtr, "Professor Name: %s\n\n",profName);
        for(k=0;k<150;k++)
            fprintf(fPtr,"*");
    }
    fPtr=NULL;
    fclose(fPtr);

}



void  course_Details()
{
    int i=1;
    while (1)
    {
        int check2;
        int j=1;
        printf("\t Student %d\n",i);
        i++;
        printf("Enter the Year: ");
        scanf("%d", &cInfo.year);
        printf("Enter Degree: ");
        scanf(" %[^\n]%*c",cInfo.dgreName);
        printf("Enter Branch: ");
        scanf(" %[^\n]%*c",cInfo.brnchName);
        while (1)
        {
            int check1;
            printf("\t Subject %d\n",j);
            j++;
            printf("Enter Subject Name: ");
            scanf(" %[^\n]%*c",cInfo.subName);
            printf("Enter Subject Code: ");
            scanf(" %[^\n]%*c", cInfo.subCode);
            printf("Enter Subject Credit: ");
            scanf(" %f", &cInfo.subCredit);
            printf("Enter Subject Type(Th/Pr) ");
            scanf(" %[^\n]%*c", cInfo.subType);
            printf("Enter Professor Name: ");
            scanf(" %[^\n]%*c", cInfo.profName);
            corsDtabs(cInfo.year,cInfo.dgreName,cInfo.brnchName,cInfo.subName,cInfo.subCode,cInfo.subCredit,cInfo.subType,cInfo.profName);
            printf("\nPress 1 to add more Subjects: \n");
            printf("Press 2 to Leave: \n");
            scanf("%d",&check1);
            if (check1==1)
                continue;
            else  
                break;
        }
        printf("\nPress 1 to add more Students : \n");
        printf("Press 2 to Leave: \n");
        scanf("%d",&check2);
        if (check2==1)
            continue;
        else  
            break;
    }
}


void subDetls()
{
    while (1)
    {
        int choice1, choice2;
        printf("Select 1 for student with Specialization \n");
        printf("Select 2 for student with Core \n");
        scanf("%d",&choice1);
        if (choice1==1)
        {
            course_Details();
            printf("Press 1 to change faculty\n");
            printf("Press 2 to exit\n");
            scanf("%d",&choice2);
            if (choice2==1)
                continue;
            else
                break;

            
        }
        if (choice1==2)
        {
        course_Details(); 
        printf("Press 1 to change faculty\n");
        printf("Press 2 to exit\n");
        scanf("%d",&choice2);
        if (choice2==1)
            continue;
        else
            break;
        
        }
    }

}

void employerOP(unsigned long long sysID)           // Employer Menu function
{

    while (1)
    {
        int input, opt;
        printf("\n\t1. Enroll New Student ");
        printf("\n\t2. Allot Timetable ");
        printf("\n\t3. Subjects "); 
        printf("\n\t4. Exit ");
        printf("\n");
        scanf("%d", &input);

        if (input == 1)
        {

            // printf("Enter the Students Name \n");
            printf("Student's First Name: ");
            scanf("\n");
            scanf("%[^\n]%*c", stud.fstName);        //First name
            printf("\nStudent's Last Name: ");
            scanf("%[^\n]%*c", stud.lstName);         // Last name

            strcat(stud.fstName, " ");             // Adding space after first name
            strcat(stud.fstName, stud.lstName);

            strcpy(stud.name, stud.fstName);            //Storing Name

            printf("\nSelect Operation:-\n");
            printf("\n1. Insert Academic Details");
            printf("\n2. Insert Personal Details\n");

            while (1)
            {
                scanf("%d", &opt);
                if (opt == 1)
                {
                    SetStudAccDetls(stud.sysID, stud.name);             // Calling the function to enter Academic details
                    break;
                }
                else if (opt == 2)
                {
                    GetStudPrsnlDetls(stud.sysID, stud.name);            // Calling the function to enter Personal details
                    break;
                }
                else
                {
                    printf("Enter the value again:");
                    // continue;
                }
            }
            break;
        }
        else if (input == 3)
        {
            subDetls();
        }
        else if (input == 4)
            break;
        else
        {
            printf("Enter the value again:");
            // continue;
        }
        
    }
}






void main() // Start
{
    int reply; // To store user's choice for operations
    printf("\n\n\n");
    printf("\n\t\t\t   Welcome");
    printf("\n\t\t ###### My Cloud EMS ######");
    printf("\n\n\n");
    printf("\nSelect User Type ");
    printf("\n1. Student");
    printf("\n2. Employee");
    printf("\n0. Exit");
    printf("\n");
    
    while (1)
    {
        scanf("%d", &choice);
        getUserType(choice); // Getting the type of User ie.., Student or Employee
        if (strcmp(getUserType(choice), "Employee") == 0)
        { // Menue for Employee
            printf("\n1. New User?? Sign Up");
            printf("\n2. Existing User?? Login");
            printf("\n9. Exit");
            printf("\n");
            scanf("%d", &reply);
            if (reply == 1)
            {
                printf("\nEnter System ID: ");
                scanf("%llu", &emp.sysID);
                setPass(emp.sysID); // calling function to set password
                
            }
            if (reply == 2)
            {   
                fPtr = fopen("EmpPassDataBase.txt","r");
                while(1)           // To ask for id pass again in case of wrong id pass
                {
                    printf("\nEnter System ID: ");
                    scanf("%llu",&emp.sysID);
                    printf("\nEnter Password: ");
                    scanf("%s", &pass);
                    
                    if(strcmp(verifyAcc(emp.sysID,pass),"Matched")==0)
                    {
                        printf("\n Welcome:)");
                        employerOP(emp.sysID);       // To enroll new student / time table allot.

                        break;
                    }
                    else
                    {
                        printf("\n%s",verifyAcc(emp.sysID,pass));   // Printing the returning value
                        printf("\nRetry");
                        // printf("\nPress 1 to exit");
                        
                    }
                }
            }
            break;
        }
        else if (strcmp(getUserType(choice), "Student") == 0)
        { 
            fPtr = fopen("StPassDataBase.txt","r");
            while (1)
            {
                printf("\nEnter System ID: ");
                scanf("%llu", &stud.sysID);
                printf("\nEnter Password: ");
                scanf("%s", pass);
                if(strcmp(verifyAcc(stud.sysID,pass),"Matched")==0)
                {
                    printf("\n Welcome:)");
                    break;
                }
                else
                {
                    printf("\n%s",verifyAcc(stud.sysID,pass));    // Printing the returning value
                    printf("\nRetry");
                    // printf("\nPress 1 to exit");
                }
                
            }
        }
        else if (strcmp(getUserType(choice), "Again") == 0)
        {
            printf("Is an Invalid Choice!!!");
            printf("\nPlease choose again:\n");
            continue;
        }
    }
}
