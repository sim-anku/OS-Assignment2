
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
int student[3][4]={0};
void *teacher();
void *student1();
void *student2();
void *student3();
pthread_mutex_t lck;
int ch1,ch2;
int r1,r2;
int main()
{
	printf("\t\tt\t---Welcom---\n");
	pthread_mutex_init(&lck,NULL);
	student[1][1]=1;
	student[2][2]=2;
	student[3][3]=1;
	pthread_t t_thread;
	pthread_t s_thread;
	printf("resources menu:\n\t\tpress'1' for pen \n\tpress '2' for paper\n\tpress '3' for question_paper\n");
	while(1)
	{
		if(student[1][4]==1 && student[2][4]==1 && student[3][4]==1)
		{
			break;
		}
		pthread_create(&t_thread,NULL,teacher,NULL);
		pthread_join(t_thread,NULL);
		if((ch1==1 && ch2==2 || ch2==1 && ch1==2) && student[3][4]==0)
		{
			pthread_create(&s_thread,NULL,student3,NULL);
			pthread_join(s_thread,NULL);
		}
		elseif((ch1==1 && ch2==3 || ch2==1 && ch1==3) && student[2][4]==0)
		{
			pthread_create(&s_thread,NULL,student2,NULL);
			pthread_join(s_thread,NULL);
		}
		elseif((ch1==2 && ch2==3 || ch2==2 && ch1==3) && student[1][4]==0)
		{
			pthread_create(&s_thread,NULL,student1,NULL);
			pthread_join(s_thread,NULL);
		}
		else
		{
			printf("\n\terror(007):try again..with different choices.\n");
		}
	}
	printf("\n\t----done---\n");
    void *teacher()
    {
    	pthread_mutex_lock(&lck);
    	printf("\nfirst resource on shared table:-\t");
    	scanf("%d",&ch1);
    	printf("second resource on shared table:-\t");
    	scanf("%d",&ch2);
    	pthread_mutex_unlock(&lck);
	}
	void *student2()
	{
		pthread_mutex_lock(&lck);
		printf("\nChoices made='pen','question_paper'\n");
		student[2][4]=1;
		printf("\n\tstudent2 has completed the assignment \n");
		pthread_mutex_unlock(&lck);
	}
	void *student3()
	{
		pthread_mutex_lock(&lck);
		printf("\nChoices made='pen','paper'\n");
		student[3][4]=1;
		printf("\n\tstudent3 has completed the assignment\n");
		pthread_mutex_unlock(&lck);
	}
	void *student1()
	{
		pthread_mutex_lock(&lck);
		printf("\nChoices made='paper','question_paper'\n");
		student[1][4]=1;
		printf("\n\tstudent 1 has completed the assignment\n");
		pthread_mutex_unlock(&lck);
	}
}
