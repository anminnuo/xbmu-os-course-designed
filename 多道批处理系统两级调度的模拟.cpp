#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include<conio.h>

#define getpch(type)(type*)malloc(sizeof(type))

struct jcb{/*������ҵ���ƿ�JCB*/
    char name[10]; //��ҵ����
    int  state;
	int  size;  //��ҵ��С
	int  atime; //����ʱ��
	int  ntime;  //��������ʱ��
	int  drive;  //��Ҫ�ĴŴ���������
    struct jcb*link;
}*jcbhead=NULL,*jcbtemp=NULL,*jcbq,*jcbp,*jcbpr,*jcbb;
typedef struct jcb JCB;

struct mcb{/*�����ڴ��������MCB*/
    char name[10];
    char state[20];
    int  state2;
	int  size;
	int  atime;
	int  ntime;
	int zouzhuan;//��תʱ��
	int  drive;
    struct mcb*link;
}*mcbhead=NULL,*mcbtemp=NULL,*mcbp,*mcbpr,*mcbq,*mcbb;
typedef struct mcb MCB;

int time=10;
int thedrive=4;
int findminjcb=1;
int selectrun=0;
double zhouzhuan = 0;//ƽ����ת����
int NUM = 0;
///////////////////////////////////////////////////////////////////////////////
//����������//
void display();
void display1();
void run1();
void run2();
void store1();
void store2();
void printmcb();
void printmp();
void score();
///////////////////////////////////////////////////////////////////////////////

void CreatJob(){

	int i,num;
	jcbhead=getpch(JCB);
	jcbq=getpch(JCB);	
	jcbq=jcbhead;
    system("CLS"); 

    printf("\n ������ҵ�ĸ���:");
    scanf("%d",&num);
    NUM = num;
    for(i=0;i<num;i++){
	    jcbp=getpch(JCB);
        printf("\n ��ҵ�� NO.%d:\n",i+1);
        printf("\n ������ҵ��:");
        scanf("%s",jcbp->name);
        printf("\n ������ҵ����ʱ��:");
        scanf("%d",&jcbp->atime);
		printf("\n �����������ʱ��:");
		scanf("%d",&jcbp->ntime);
		printf("\n ������ҵ��С:");
        scanf("%d",&jcbp->size);
		printf("\n ������Ҫ�ĴŴ���������:");
		scanf("%d",&jcbp->drive);
		printf("\n");
		jcbp->state=0;
		jcbp->link=NULL;
		if(jcbp->size>mcbq->size){
            printf("\n �Բ���,���������ҵ����ϵͳ����Դ!����������!");
            i--;
		}else if(jcbp->drive>thedrive){
            printf("\n �Բ���,���������ҵ��Ҫ�ĴŴ�������������ϵͳ�ĴŴ�������!����������!");
			i--;
		}else{
			jcbq->link=jcbp;
			jcbq=jcbq->link;
		}
	}
	display();


}

void display(){
     printf("\n��ҵ������Ϣ: ");
	 printf("\n");
	 printf("\n��ҵ�� \t���� \t���� \t��С \t�Ŵ���\n ");
	 jcbpr=jcbhead->link;
	 while(jcbpr){
		 display1();
		 jcbpr=jcbpr->link;
     }
	 getch();
}

void display1(){
	 printf("|%s\t",jcbpr->name);
	 printf("|%d\t",jcbpr->atime);
     printf("|%d\t",jcbpr->ntime);
	 printf("|%d\t",jcbpr->size);
	 printf("|%d\n",jcbpr->drive);
}


///////////////////////////////////////////////////////////////////////

void FCFSSPF(){
    system("cls");
	printf("\n\t��ѡ���� ��ҵ�����ȷ��� �� �̽�������");
	printf("\n");
	jcbb=jcbhead->link;
	store1();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t��ѡ���� ��ҵ�����ȷ��� �� �̽�������");
		printf("\n");
		printf("\n\t��ǰ����ʱ��Ϊ:");
        printf("%d",time);
		printf("\n");
		run1();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t��ҵ�����ѽ���!");
	printf("\n\tƽ����ת����Ϊ%f",zhouzhuan/NUM);
	getch();
}

void FCFS(){
    system("cls");
	printf("\n\t�㵱ǰ��ѡ���� ��ҵ�����ȷ��� �� �����ȵ��ȷ���");
	printf("\n");
	jcbb=jcbhead->link;
	store1();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t�㵱ǰ��ѡ���� ��ҵ�����ȷ��� �� �����ȵ��ȷ���");
	    printf("\n");
		printf("\n\t��ǰ����ʱ��Ϊ:");
        printf("%d",time);
		printf("\n");
		run2();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t��ҵ�����ѽ���!");
	printf("\n\tƽ����ת����Ϊ%f",zhouzhuan/NUM);
	getch();
}

void SJFSPF (){
    system("cls");
	printf("\n\t���ѡ���� ����ҵ���� �� �̽�������");
	printf("\n");
	jcbb=jcbhead->link;
	store2();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t��ѡ���� ����ҵ���� �� �̽�������");
	    printf("\n");
		printf("\n\t��ǰ����ʱ��Ϊ:");
        printf("%d",time);
		printf("\n");
		run1();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t��ҵ�����ѽ���!");
	printf("\n\tƽ����ת����Ϊ%f",zhouzhuan/NUM);
	getch();
}

void SJFFCFS(){
    system("cls");
	printf("\n\t�㵱ǰ��ѡ���� ����ҵ���� �� �����ȵ��ȷ���");
	printf("\n");
	jcbb=jcbhead->link;
	store2();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t�㵱ǰ��ѡ���� ����ҵ���� �� �����ȵ��ȷ���");
	    printf("\n");
		printf("\n\t��ǰ����ʱ��Ϊ:");
        printf("%d",time);
		printf("\n");
		run2();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t��ҵ�����ѽ���!");
	printf("\n\tƽ����ת����Ϊ%f",zhouzhuan/NUM);
	getch();
}

///////////////////////////////////////////////////////////////////////

void run1(){	
	int mcbfind=0;
	int mcbntime=10000;
    mcbb=mcbhead->link;
	while(mcbb){
        if(mcbb->state2==2){
			if(mcbb->ntime<=0){
				mcbb->state2=3;
				printf("\n\t��ҵ");
				printf("%s",mcbb->name);
                printf("�������!");
				zhouzhuan =zhouzhuan + time - mcbb->atime;
				mcbfind=0;
				thedrive=thedrive+mcbb->drive;
                score();
			}else{
				mcbb->ntime=mcbb->ntime-1;
				printf("\n\t��ҵ");
				printf("%s",mcbb->name);
                printf("��������!");
				mcbfind=1;
			}
		}
		mcbb=mcbb->link;
	}
	if(selectrun==1){
    	store1();
	}else if(selectrun==2){
		while(findminjcb==1){
		    store2();
		}
	}
	if(mcbfind==0){
		mcbb=mcbhead->link;
		while(mcbb){
			if(mcbb->state2==1&&mcbb->ntime<=mcbntime){
				mcbntime=mcbb->ntime;
				mcbfind=2;
			}
			mcbb=mcbb->link;
		}
	}
	if(mcbfind==2){
        mcbb=mcbhead->link;
		while(mcbb){
			if(mcbb->state2==1&&mcbb->ntime==mcbntime){
                 mcbb->state2=2;
				 printf("\n\t��ҵ");
				 printf("%s",mcbb->name);
                 printf("��ʼ����!");
				 mcbb->ntime=mcbb->ntime-1;
			}
			mcbb=mcbb->link;
		}
	}
    printmcb();
	findminjcb=1;
}

void run2(){	
	int mcbfind=0;
	int mcbatime=10000;
    mcbb=mcbhead->link;
	while(mcbb){
        if(mcbb->state2==2){
			if(mcbb->ntime<=0){
				mcbb->state2=3;
				printf("\n\t��ҵ");
				printf("%s",mcbb->name);
                printf("�������!");
				zhouzhuan =zhouzhuan + time - mcbb->atime;
				mcbfind=0;
				thedrive=thedrive+mcbb->drive;
                score();
			}else{
				mcbb->ntime=mcbb->ntime-1;
				printf("\n\t��ҵ");
				printf("%s",mcbb->name);
                printf("��������!");
				mcbfind=1;
			}
		}
		mcbb=mcbb->link;
	}
	if(selectrun==1){
    	store1();
	}else if(selectrun==2){
		while(findminjcb==1){
		    store2();
		}
	}

	if(mcbfind==0){
		mcbb=mcbhead->link;
		while(mcbb){
			if(mcbb->state2==1&&mcbb->atime<=mcbatime){
				mcbatime=mcbb->atime;
				mcbfind=2;
			}
			mcbb=mcbb->link;
		}
	}
	if(mcbfind==2){
        mcbb=mcbhead->link;
		while(mcbb){
			if(mcbb->state2==1&&mcbb->atime==mcbatime){
                 mcbb->state2=2;
				 printf("\n\t��ҵ");
				 printf("%s",mcbb->name);
                 printf("��ʼ����!");
				 mcbb->ntime=mcbb->ntime-1;
			}
			mcbb=mcbb->link;
		}
	}
    printmcb();
	findminjcb=1;
}
//////////////////////////////////////////////////////////////////////////
void store1(){
	 int  assign;
	 assign=0;
	 jcbq=jcbhead->link;
	 jcbtemp=jcbhead;
	 while(jcbq!=NULL&&jcbq->atime<=time){
		 if(jcbq->atime<=time&&jcbq->drive<=thedrive&&jcbq->state==0){
			 mcbq=mcbhead->link;
			 mcbtemp=mcbhead;
			 while(mcbq){
				 if((mcbq->state2==0)&&(mcbq->size>=jcbq->size)){
					 assign=1;
					 break;
				 }else{
					 mcbtemp=mcbtemp->link;
					 mcbq=mcbq->link;
				 }
			 }
			 if(assign==1){

                 //�����ڴ�ռ����
				 mcbp=getpch(MCB);
				 mcbpr=getpch(MCB);

				 strcpy(mcbp->name,jcbq->name);
				 mcbp->atime=time;
				 mcbp->ntime=jcbq->ntime;
				 mcbp->drive=jcbq->drive;
				 mcbp->size=jcbq->size;
				 strcpy(mcbp->state,"�ѷ���");
				 mcbp->state2=1;
				 mcbp->link=mcbpr;

				 thedrive=thedrive-jcbq->drive;


               
				 if(mcbtemp==mcbhead){
					 mcbhead->link=mcbp;
				 }else{
					 mcbtemp->link=mcbp;
				 }

				 strcpy(mcbpr->name,mcbq->name);
				 mcbpr->atime=0;
				 mcbpr->ntime=0;
				 mcbpr->drive=0;
				 mcbpr->size=mcbq->size-mcbp->size;
				 strcpy(mcbpr->state,"δ����");
				 mcbpr->state2=0;
				 mcbpr->link=mcbq->link;

				 printf("\n\t��ҵ");
				 printf("%s",jcbq->name);
                 printf("�������뾮!");

				 getch();

				 if(jcbtemp==jcbhead){
					 jcbhead->link=jcbq->link;
				 }else{
					 jcbtemp->link=jcbq->link;
				 }

			 }
		 }
		 assign=0;
		 jcbq=jcbq->link;
		 jcbtemp=jcbtemp->link;
	 }
	 
}

void store2(){
	 int  assign;
	 int jcbntime=10000;
	 assign=0;
	 jcbq=jcbhead->link;
	 jcbtemp=jcbhead;
	 while(jcbq!=NULL&&jcbq->atime<=time){
		 if(jcbq->atime<=time&&jcbq->drive<=thedrive&&jcbq->state==0&&jcbq->ntime<=jcbntime){				 
			 mcbq=mcbhead->link;
			 mcbtemp=mcbhead;
			 while(mcbq){
				 if((mcbq->state2==0)&&(mcbq->size>=jcbq->size)){
					 jcbntime=jcbq->ntime;
					 findminjcb=1;
					 break;
				 }else{
					 mcbtemp=mcbtemp->link;
					 mcbq=mcbq->link;
				 }
			 }
		 }
		 assign=0;
		 jcbq=jcbq->link;
		 jcbtemp=jcbtemp->link;
	 }


     jcbq=jcbhead->link;
	 jcbtemp=jcbhead;
	 while(jcbq!=NULL&&jcbq->atime<=time){
		 if(jcbq->atime<=time&&jcbq->drive<=thedrive&&jcbq->state==0&&jcbq->ntime==jcbntime){
			 break;
		 }
		 assign=0;
		 jcbq=jcbq->link;
		 jcbtemp=jcbtemp->link;
	 }

	 if(jcbntime!=10000){
		 mcbq=mcbhead->link;
		 mcbtemp=mcbhead;
		 while(mcbq){
			 if((mcbq->state2==0)&&(mcbq->size>=jcbq->size)){
				 assign=1;
				 break;
			 }else{
				 mcbtemp=mcbtemp->link;
				 mcbq=mcbq->link;
			 }
		 }
		 if(assign==1){

			 //�����ڴ�ռ����
			 mcbp=getpch(MCB);
			 mcbpr=getpch(MCB);

			 strcpy(mcbp->name,jcbq->name);
			 mcbp->atime=time;
			 mcbp->ntime=jcbq->ntime;
			 mcbp->drive=jcbq->drive;
			 mcbp->size=jcbq->size;
			 strcpy(mcbp->state,"�ѷ���");
			 mcbp->state2=1;
			 mcbp->link=mcbpr;

			 thedrive=thedrive-jcbq->drive;



			 if(mcbtemp==mcbhead){
				 mcbhead->link=mcbp;
			 }else{
				 mcbtemp->link=mcbp;
			 }

			 strcpy(mcbpr->name,mcbq->name);
			 mcbpr->atime=0;
			 mcbpr->ntime=0;
			 mcbpr->drive=0;
			 mcbpr->size=mcbq->size-mcbp->size;
			 strcpy(mcbpr->state,"δ����");
			 mcbpr->state2=0;
			 mcbpr->link=mcbq->link;

			 printf("\n\t��ҵ");
			 printf("%s",jcbq->name);
             printf("�������뾮!");

			 getch();

			 if(jcbtemp==jcbhead){
				 jcbhead->link=jcbq->link;
			 }else{
				 jcbtemp->link=jcbq->link;
			 }

		 }
	 }else{
		 findminjcb=0;
	 }
	 
}

/////////////////////////////////////////////////////////////////////////////

void score(){
	 int  find=0;
	 mcbtemp=getpch(MCB);
	 mcbpr=getpch(MCB);
	 mcbtemp=mcbhead;
	 mcbq=mcbhead->link;
     while(mcbq){
		 if(mcbq->state2==3){
             find=1;
			 break;
		 }else{
		     mcbq=mcbq->link;
			 mcbtemp=mcbtemp->link;
		 }
	 }	
	 if(find){

		 mcbpr=mcbq;

		 if(mcbq->link!=NULL){
			 mcbpr=mcbq->link;
			 if((mcbtemp->state2==0)&&(mcbpr->state2==0)){
				 mcbtemp->size=mcbtemp->size+mcbq->size+mcbpr->size;
				 mcbtemp->link=mcbpr->link;
			 }else if(mcbtemp->state2==0){
				 mcbtemp->size=mcbtemp->size+mcbq->size;
				 mcbtemp->link=mcbq->link;
			 }else if(mcbpr->state2==0){
				 strcpy(mcbq->name,"��");
				 mcbq->size=mcbpr->size+mcbq->size;
				 strcpy(mcbq->state,"δ����");
				 mcbq->link=mcbpr->link;
				 mcbq->state2=0;
			 }else{
				 strcpy(mcbq->name,"��");
				 strcpy(mcbq->state,"δ����");
				 mcbq->state2=0;
			 }
		 }else{
             if(mcbtemp->state2==0){
				 mcbtemp->size=mcbtemp->size+mcbq->size;
				 mcbtemp->link=mcbq->link;
			 }else{
				 strcpy(mcbq->name,"��");
				 strcpy(mcbq->state,"δ����");
				 mcbq->state2=0;
			 } 
		 }
		 printf("\n\t����ҵ�ѳɹ�����!");
		 getch();
	 }
	 
}


void printmcb(){
	 printf("\n");
	 printf("\n\t���뾮��״̬:");
	 printf("\n");
	 printf("\n\t ���� \t��С \t״̬\n ");
	 mcbpr=mcbhead->link;
	 while(mcbpr){
		 printmp();
		 mcbpr=mcbpr->link;
     }
	 printf("\n\t�밴�����������һ����...");
	 getch();
}

void printmp(){
     printf("\t");
	 printf("|%s\t",mcbpr->name);
     printf("|%d\t",mcbpr->size);
	 printf("|%s\n",mcbpr->state);
}

///////////////////////////////////////////////////////////////////////////////////

int menu(){
		int choose;
		printf("\n\n");
		printf("\n\t-------------------------------------------------");
        printf("\n\t      ����ѧԺ18���ƿ�1�� ���� P181713164        ");
		printf("\n\t                                                 ");
		printf("\n\t              ����ռ�ķ��������               ");
        printf("\n\t                                                 ");
		printf("\n\t     1 ��������ҵ                                ");
		printf("\n\t     2 ���� ��ҵ�����ȷ��� �� �̽������� ִ��    ");
		printf("\n\t     3 ���� ��ҵ�����ȷ��� �� �����ȵ��ȷ��� ִ��");
		printf("\n\t     4 ���� ����ҵ���� �� �̽������� ִ��        ");
		printf("\n\t     5 ���� ����ҵ���� �� �����ȵ��ȷ��� ִ��    ");
		printf("\n\t     0 ���˳�"); 
		printf("\n\t-------------------------------------------------");
		printf("\n\t��ѡ�����룺");
		scanf("%d",&choose);
		while(choose>6){
			printf("\n\tѡ�����,����������>>>>>");
			scanf("%d",&choose);
		}
		return choose;
}

////////////////////////////////////////////////////////////////////////////////////
int main(){
	   char more;
	   int exitFlag; 
	   mcbhead=getpch(MCB);
	   strcpy(mcbhead->state,"δ����");
	   mcbq=getpch(MCB);
	   strcpy(mcbq->name,"��");
	   strcpy(mcbq->state,"δ����");
	   mcbq->size=100;
	   mcbq->state2=0;
	   mcbq->link=NULL;
	   mcbhead->link=mcbq;
	   exitFlag=0;
	   while(!exitFlag){
			 system("cls");
			 switch(menu()){
				  case 0:
					   exitFlag=1;
					   break;
				  case 1:
					   CreatJob();
					   break;
				  case 2:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\tδ������ҵ,���ȴ���!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=1;
					       FCFSSPF(); //��ҵ�����ȷ��� �� �̽�������
						   
					   }
					   break;
				  case 3:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\tδ������ҵ,���ȴ���!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=1;
					       FCFS();//��ҵ�����ȷ��� �� �����ȵ��ȷ���
					   }
					   break;
				  case 4:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\tδ������ҵ,���ȴ���!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=2;
					      SJFSPF();  //����ҵ���� �� �̽�������
					   }
					   break;
				  case 5:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\tδ������ҵ,���ȴ���!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=2;
					       SJFFCFS(); //����ҵ���� �� �����ȵ��ȷ���
					   }
					   break;
				  default:  
					   scanf("%s",&more);
					   printf("\n\t�������,������!"); 
					   getch();
					   break;
			 }
	   }
return 0;
}


