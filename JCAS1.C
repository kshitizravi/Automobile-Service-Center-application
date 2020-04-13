#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//defining the properties of the fields used in the program


#define IN 1
#define OUT 0

void login();
char pass[20]={"admin"};
void menu();
void Addjob();
void Searchjob();
void Displayjob();
void mechanic();
void joblist();
void Addmembr();
void Searchmem();
void issue();
void jobret();
void Exit();
void delay(int delay)
{
 int now=time(NULL);
 int later=now+delay;
 while(now<=later)now=time(NULL);
}

char info[500];


struct emp
{
  int cid;
  char cname[25] ;
  char mechanic[25];
  int  noofjobs;
  char titles[500];
  int  status;
}book;
struct record
{
  int  mid;
  char mname[25] ;
  char bike[25];
  int  availibcard;
  long phno;
}membr;


//initializing the files used in the program

FILE *librecord;
FILE *membrrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
main()
{
	login();
	getch();
}
void menu()
{
    int choice=0,i;
    printf("\n\t\t<<JOB ASSIGNING SYSTEM>> \n");
    do{
    printf("\n\t~~MENU~~\n 1> Add A New Job\n 2> Search for a Job \n 3> Display All Jobs of A Mechanic\n 4> List Jobs\n 5> Add A New Member\n 6> Search Member\n 7> Issue a Job\n 8> Return a Job\n 9>Exit the program\n\n Enter your choice <1-9>: ");
    scanf("%i",&choice);


    switch (choice)
    {
	case 1:
	    Addjob();
	    delay(2000);
	    break;
	case 2:
	    Searchjob();
	    delay(3000);
	    break;
	case 3:
	    mechanic();
	    delay(3000);
	    break;
	case 4:
	    joblist();
	    delay(3000);
	    break;
	case 5:
	    Addmembr();
	    delay(2000);
	    break;
	case 6:
	    Searchmem();
	    delay(3000);
	    break;
	case 7:
	    issue();
	    delay(3000);
	    break;
	case 8:
	    jobret();
	    delay(3000);
	    break;
	case 9:
	    exit(0);
	default:
	    printf(" ! Invalid Input...\n");
    }
}while(choice!=10);
}
void login()
{
	char ch, pwd[20];
	int i=0;
	printf("Enter Password: ");
	ch= getch();
	while(ch!=13)
	{
		if(ch!= 13 && ch!= 8)
		{
			printf("*");
			pwd[i]= ch;
			i++;
		}
		ch= getch();
	}
	pwd[i]= '\0';
	if(strcmp(pass,(pwd))==0)
	{
		printf("\nPassword Match");
		printf("\nContinuing in 3 seconds ...");
		delay(3000);
		menu();
	}
	else
	{
		printf("\nIncorrect Password");
		printf("\nExiting in 3 seconds ...");
		delay(3000);
		exit(0);
	}
}

void Addjob()
{
    int i;book.status=IN;
	    //opening the librecord file
    librecord = fopen("librecord.txt","a+");
    printf("Enter The uniqueid for The Job :(Integer) \n");
	scanf("%d",&book.cid);
    printf("Enter The Name for The Job :\n");
	scanf("%s",book.cname);
    printf("Enter The Name of Mechanic :\n");
	scanf("%s",book.mechanic);
    printf("Enter The Number of Titles for The Job:(Integer)\n");
	scanf("%d",&book.noofjobs);
    fprintf(librecord,"\n%d\t%s\t%s\t%d\t",book.cid,book.cname,book.mechanic,book.noofjobs);
    printf("Enter The Titles for The job : \n");
    for(i=0;i<book.noofjobs;i++)
    {
	scanf("%s",book.titles);
	fprintf(librecord,"%s\t",book.titles);
    }
    fclose(librecord);
    printf(" (' ' ) A New job has been Added Successfully...\n");

}

void Searchjob()
{
    int i;
    char Target[25],stats[3];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
	printf(" ! The File is Empty...\n\n");
    else
    {
	printf("\nEnter The Name Of Job : ");
	    scanf("%s",Target);
	while(!feof(librecord)&& Found==0)
	{
	fscanf(librecord,"%d %s %s %d %d", &book.cid,book.cname,book.mechanic,&book.status,&book.noofjobs);
	    if(strcmp(Target,book.cname)==0)
		Found=1;
	    for(i=0;i<book.noofjobs;i++)
		fscanf(librecord,"%s",book.titles);
	}
	if(Found)
	{
	    if(book.status==IN)
		strcpy(stats,"IN");
	    else
		strcpy(stats,"OUT");

	    printf("\nThe Unique ID of The Job:  %d\nThe Name of Job is:  %s\nThe Mechanic is:  %s\nThe job Status:%s\n\n",book.cid,book.cname,book.mechanic,stats);
	    }
	else if(!Found)
	    printf("! There is no such Entry...\n");
	fclose(librecord);
    }

}

void mechanic()
{
    int i;
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
    printf(" ! The file is empty... \n\n");
    else
    {
	printf("\nEnter The Name Of Mechanic : ");
	    scanf("%s",Target);
	printf("\nJobs:");
	while(!feof(librecord))
	{
	    fscanf(librecord,"%d %s %s %d %d",&book.cid,book.cname,book.mechanic,&book.status,&book.noofjobs);
	    if(strcmp(Target,book.mechanic)==0)
	    {
		Found=1;
		printf("\n\t%s",book.cname);
	    }
	    for(i=0;i<book.noofjobs;i++)
		fscanf(librecord,"%s",book.titles);
	}
	if(!Found)
	    printf(" ! There is no such Entry...\n");
	fclose(librecord);
    }

}
void joblist()
{
    int i;
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
	printf(" ! The file is empty...\n\n");
    else
    {
	printf("\nEnter The Job Name :");
	scanf("%s",Target);
	while(!feof(librecord)&& Found==0)
	{
	    fscanf(librecord,"%d %s %s %d %d",&book.cid,book.cname,book.mechanic,&book.status,&book.noofjobs);
	    if(strcmp(Target,book.cname)==0)
		{
		    Found=1;
		    break;
		}
	    for(i=0;i<book.noofjobs;i++)
		fscanf(librecord,"%s",book.titles);
	}
	if(Found)
	{
	    printf("\nThe Titles:\n");
	    for(i=0;i<book.noofjobs;i++)
	    {
		fscanf(librecord,"%s",book.titles);
		    printf("%d.%s......\n",i+1,book.titles);
	    }
	}
	else if(!Found)
	    printf(" ! There is no such Entry...\n");
	fclose(librecord);
    }

}

void Addmembr()
{
    int i;

    membrrecord = fopen("membrrecord.txt","a+");
    printf("Enter The userid of the customer(Integer) :\n");
	scanf("%d",&membr.mid);
    printf("Enter The Name of the customer :\n");
	scanf("%s",membr.mname);
    printf("Enter The brand of bike he owns\n");
	scanf("%s",membr.bike);
    printf("Enter The phone number of the member:\n");
	scanf("%ld",&membr.phno);
    membr.availibcard=5;
    fprintf(membrrecord,"\n%d\t%s\t%s\t%ld\t%d\t",membr.mid,membr.mname,membr.bike,membr.phno,membr.availibcard);
    fclose(membrrecord);
    printf("\n (' ') Added A New member Successfully...\n");
}

void Searchmem()
{
    int i, id;
    char stats[3];
    int Found=0;
    if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
	printf(" ! The File is Empty...\n\n");
    else
    {
	printf("\nEnter The User Id Of Member : ");
	    scanf("%d", &id);
	while(!feof(membrrecord)&& Found==0)
	{
	fscanf(membrrecord,"%d %s %s %d %ld", &membr.mid,membr.mname,membr.bike,&membr.availibcard,&membr.phno);
	    if(id==membr.mid)
		Found=1;
	}
	if(Found)
	{
	 printf("\nThe User ID of The Member:  %d\nThe Name of Member is:  %s\nThe Bike is:  %s\nThe Phone Number Is: %ld\n\n",membr.mid,membr.mname,membr.bike,membr.phno);
	}
	else if(!Found)
	    printf("! There is no such Entry...\n");
	fclose(membrrecord);
    }
}

void issue()
{
	int mid, i, Found1 = 0, Found2 = 0; char jobname[20];
	printf("\nEnter The userid of the Member : \n");
	scanf("%d", &mid);
	if ((membrrecord = fopen("membrrecord.txt", "r")) == NULL)
		printf(" ! The file is empty...\n\n");
	else
	{
		while (!feof(membrrecord) && Found1 == 0)
		{
			fscanf(membrrecord, "%d %s %s %ld %d ", &membr.mid, membr.mname, membr.bike, &membr.phno, &membr.availibcard);
			if (mid == membr.mid)
			{
				Found1 = 1;
			}
		}
		if (Found1)
		{
			if (membr.availibcard<1)
			{
				printf(" ! Job card not available...\n");
			}
			else
			{
				printf("\nEnter The Name of Job :");
				scanf("%s",jobname);
				if ((librecord = fopen("librecord.txt", "r")) == NULL)
					printf(" ! The file is empty...\n\n");
				else
				{
					while (!feof(librecord) && Found2 == 0)
					{
						fscanf(librecord, "%d %s %s %d %d", &book.cid, book.cname, book.mechanic, &book.status, &book.noofjobs);
						if (strcmp(jobname, book.cname) == 0)
							Found2 = 1;
						for (i = 0; i<book.noofjobs; i++)
							fscanf(librecord, "%s", book.titles);
					}
					if (Found2)
					{
						if (book.status == 0)
						{
							printf(" ! Job already issued...\n");
						}
						else
						{

							fp2 = fopen("fp2.txt", "w");
							if ((temp2 = fopen("membrrecord.txt", "r")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp2))
								{
									fscanf(temp2, "%d %s %s %ld %d ", &membr.mid, membr.mname, membr.bike, &membr.phno, &membr.availibcard);


									if (mid == membr.mid)
									{
										membr.availibcard--;
										fprintf(fp2, "\n %d\t%s\t%s\t%ld\t%d\t", membr.mid, membr.mname, membr.bike, membr.phno, membr.availibcard);
									}
									else{
										fprintf(fp2, "\n %d\t%s\t%s\t%ld\t%d\t", membr.mid, membr.mname, membr.bike, membr.phno, membr.availibcard);
									}
									if (feof(temp2))
										break;
								}
							}
							fclose(temp2);
							fclose(fp2);


							fp1 = fopen("fp1.txt", "w");
							if ((temp1 = fopen("librecord.txt", "r")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp1))
								{
									fscanf(temp1, "%d %s %s %d %d", &book.cid, book.cname, book.mechanic, &book.status, &book.noofjobs);
									if (feof(temp1))
										break;
									if (strcmp(jobname, book.cname) != 0)
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.cid, book.cname, book.mechanic, book.status, book.noofjobs);
									}
									else
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.cid, book.cname, book.mechanic, book.noofjobs);
									}
									for (i = 0; i<book.noofjobs; i++)
									{
										fscanf(temp1, "%s", book.titles);
										fprintf(fp1, "%s\t", book.titles);
									}
								}
							}
							fclose(temp1);
							fclose(fp1);
							fclose(librecord);
							fclose(membrrecord);
							remove("librecord.txt");
							rename("fp1.txt", "librecord.txt");
							remove("membrrecord.txt");
							rename("fp2.txt", "membrrecord.txt");
							printf(" (' ') Job Successfully issued...\n");
						}
					}
					else if (!Found2)
						printf(" ! There is no such Job...\n");

				}
			}
		}
		else if (!Found1)
			printf(" ! Invalid User id...\n");
}

}

void jobret()
{
	int mid, i, Found1 = 0, Found2 = 0, flag = 0; char retjobname[20];
	printf("\nEnter The userid of the Member :\n");
	scanf("%d", &mid);
	if ((membrrecord = fopen("membrrecord.txt", "r")) == NULL)
		printf(" ! The file is empty...\n\n");
	else
	{
		while (!feof(membrrecord) && Found1 == 0)
		{
			fscanf(membrrecord, "%d %s %s %ld %d ", &membr.mid, membr.mname, membr.bike, &membr.phno, &membr.availibcard);
			if (mid == membr.mid)
			{
				Found1 = 1;
			}
		}
		if (Found1)
		{
			if (membr.availibcard >= 5)
			{
				printf(" ! Error...\n");
			}
			else
			{
				printf("\nEnter The Name of Job :");
				scanf("%s", retjobname);
				if ((librecord = fopen("librecord.txt", "r")) == NULL)
					printf(" ! The file is empty\n\n");
				else
				{
					while (!feof(librecord) && Found2 == 0)
					{
						fscanf(librecord, "%d %s %s %d %d", &book.cid, book.cname, book.mechanic, &book.status, &book.noofjobs);
						if (strcmp(retjobname, book.cname) == 0)
							Found2 = 1;
						for (i = 0; i<book.noofjobs; i++)
							fscanf(librecord, "%s", book.titles);
					}
					if (Found2)
					{
						if (book.status == 1)
						{
							printf(" ! Error:Job already in issued...\n");
						}
						else
						{

							fp2 = fopen("fp2.txt", "w");
							if ((temp2 = fopen("membrrecord.txt", "a+")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp2))
								{
									fscanf(temp2, "%d %s %s %ld %d ", &membr.mid, membr.mname, membr.bike, &membr.phno, &membr.availibcard);


									if (mid == membr.mid)
									{
										membr.availibcard++;
										fprintf(fp2, "\n %d\t%s\t%s\t%ld\t%d\t", membr.mid, membr.mname, membr.bike, membr.phno, membr.availibcard);
									}
									else
									{
										fprintf(fp2, "\n %d\t%s\t%s\t%ld\t%d\t", membr.mid, membr.mname, membr.bike, membr.phno, membr.availibcard);
									}
									if (feof(temp2))
										break;
								}
							}
							fclose(temp2);
							fclose(fp2);


							fp1 = fopen("fp1.txt", "w");
							if ((temp1 = fopen("librecord.txt", "r")) == NULL)
								printf(" ! The file is empty...\n\n");
							else
							{
								while (!feof(temp1))
								{
									fscanf(temp1, "%d %s %s %d %d", &book.cid, book.cname, book.mechanic, &book.status, &book.noofjobs);
									if (feof(temp1))
										break;
									if (strcmp(retjobname, book.cname) != 0)
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d    \t", book.cid, book.cname, book.mechanic, book.status, book.noofjobs);
									}
									else
									{
										fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.cid, book.cname, book.mechanic, book.noofjobs);
									}
									for (i = 0; i<book.noofjobs; i++)
									{
										fscanf(temp1, "%s", book.titles);
										fprintf(fp1, "%s\t", book.titles);
									}
								}
							}
							fclose(temp1);
							fclose(fp1);
							fclose(librecord);
							fclose(membrrecord);
							printf("('') Vehicle Successfully Returned...\n");
							remove("librecord.txt");
							rename("fp1.txt", "librecord.txt");
							remove("membrrecord.txt");
							rename("fp2.txt", "membrrecord.txt");

						}
					}
					else if (!Found2)
						printf("! There is no such Job...\n");

				}
			}
		}
		else if (!Found1)
			printf("! Invalid User id...\n");
}
}

void Exit()
{
  exit(1);
}
