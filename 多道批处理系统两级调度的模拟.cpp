#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include<conio.h>

#define getpch(type)(type*)malloc(sizeof(type))

struct jcb{/*定义作业控制块JCB*/
    char name[10]; //作业名字
    int  state;
	int  size;  //作业大小
	int  atime; //到达时间
	int  ntime;  //估计运行时间
	int  drive;  //需要的磁带机的数量
    struct jcb*link;
}*jcbhead=NULL,*jcbtemp=NULL,*jcbq,*jcbp,*jcbpr,*jcbb;
typedef struct jcb JCB;

struct mcb{/*定义内存分配链表MCB*/
    char name[10];
    char state[20];
    int  state2;
	int  size;
	int  atime;
	int  ntime;
	int zouzhuan;//周转时间
	int  drive;
    struct mcb*link;
}*mcbhead=NULL,*mcbtemp=NULL,*mcbp,*mcbpr,*mcbq,*mcbb;
typedef struct mcb MCB;

int time=10;
int thedrive=4;
int findminjcb=1;
int selectrun=0;
double zhouzhuan = 0;//平均周转周期
int NUM = 0;
///////////////////////////////////////////////////////////////////////////////
//各函数定义//
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

    printf("\n 输入作业的个数:");
    scanf("%d",&num);
    NUM = num;
    for(i=0;i<num;i++){
	    jcbp=getpch(JCB);
        printf("\n 作业号 NO.%d:\n",i+1);
        printf("\n 输入作业名:");
        scanf("%s",jcbp->name);
        printf("\n 输入作业到达时间:");
        scanf("%d",&jcbp->atime);
		printf("\n 输入估计运行时间:");
		scanf("%d",&jcbp->ntime);
		printf("\n 输入作业大小:");
        scanf("%d",&jcbp->size);
		printf("\n 输入需要的磁带机的数量:");
		scanf("%d",&jcbp->drive);
		printf("\n");
		jcbp->state=0;
		jcbp->link=NULL;
		if(jcbp->size>mcbq->size){
            printf("\n 对不起,你输入的作业超过系统的资源!请重新输入!");
            i--;
		}else if(jcbp->drive>thedrive){
            printf("\n 对不起,你输入的作业需要的磁带机的数量超过系统的磁带机数量!请重新输入!");
			i--;
		}else{
			jcbq->link=jcbp;
			jcbq=jcbq->link;
		}
	}
	display();


}

void display(){
     printf("\n作业队列信息: ");
	 printf("\n");
	 printf("\n作业名 \t到达 \t运行 \t大小 \t磁带机\n ");
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
	printf("\n\t你选择是 作业先来先服务 和 短进程优先");
	printf("\n");
	jcbb=jcbhead->link;
	store1();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t你选择是 作业先来先服务 和 短进程优先");
		printf("\n");
		printf("\n\t当前运行时刻为:");
        printf("%d",time);
		printf("\n");
		run1();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t作业调度已结束!");
	printf("\n\t平均周转周期为%f",zhouzhuan/NUM);
	getch();
}

void FCFS(){
    system("cls");
	printf("\n\t你当前的选择是 作业先来先服务 和 进程先到先服务");
	printf("\n");
	jcbb=jcbhead->link;
	store1();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t你当前的选择是 作业先来先服务 和 进程先到先服务");
	    printf("\n");
		printf("\n\t当前运行时刻为:");
        printf("%d",time);
		printf("\n");
		run2();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t作业调度已结束!");
	printf("\n\t平均周转周期为%f",zhouzhuan/NUM);
	getch();
}

void SJFSPF (){
    system("cls");
	printf("\n\t你的选择是 短作业优先 和 短进程优先");
	printf("\n");
	jcbb=jcbhead->link;
	store2();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t你选择是 短作业优先 和 短进程优先");
	    printf("\n");
		printf("\n\t当前运行时刻为:");
        printf("%d",time);
		printf("\n");
		run1();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t作业调度已结束!");
	printf("\n\t平均周转周期为%f",zhouzhuan/NUM);
	getch();
}

void SJFFCFS(){
    system("cls");
	printf("\n\t你当前的选择是 短作业优先 和 进程先到先服务");
	printf("\n");
	jcbb=jcbhead->link;
	store2();
	printmcb();
	while(jcbb||mcbhead->link->link){
		system("cls");
		printf("\n\t你当前的选择是 短作业优先 和 进程先到先服务");
	    printf("\n");
		printf("\n\t当前运行时刻为:");
        printf("%d",time);
		printf("\n");
		run2();
		time=time+1;
		jcbb=jcbhead->link;
	}
	printf("\n\t作业调度已结束!");
	printf("\n\t平均周转周期为%f",zhouzhuan/NUM);
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
				printf("\n\t作业");
				printf("%s",mcbb->name);
                printf("运行完毕!");
				zhouzhuan =zhouzhuan + time - mcbb->atime;
				mcbfind=0;
				thedrive=thedrive+mcbb->drive;
                score();
			}else{
				mcbb->ntime=mcbb->ntime-1;
				printf("\n\t作业");
				printf("%s",mcbb->name);
                printf("正在运行!");
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
				 printf("\n\t作业");
				 printf("%s",mcbb->name);
                 printf("开始运行!");
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
				printf("\n\t作业");
				printf("%s",mcbb->name);
                printf("运行完毕!");
				zhouzhuan =zhouzhuan + time - mcbb->atime;
				mcbfind=0;
				thedrive=thedrive+mcbb->drive;
                score();
			}else{
				mcbb->ntime=mcbb->ntime-1;
				printf("\n\t作业");
				printf("%s",mcbb->name);
                printf("正在运行!");
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
				 printf("\n\t作业");
				 printf("%s",mcbb->name);
                 printf("开始运行!");
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

                 //进程内存空间分配
				 mcbp=getpch(MCB);
				 mcbpr=getpch(MCB);

				 strcpy(mcbp->name,jcbq->name);
				 mcbp->atime=time;
				 mcbp->ntime=jcbq->ntime;
				 mcbp->drive=jcbq->drive;
				 mcbp->size=jcbq->size;
				 strcpy(mcbp->state,"已分配");
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
				 strcpy(mcbpr->state,"未分配");
				 mcbpr->state2=0;
				 mcbpr->link=mcbq->link;

				 printf("\n\t作业");
				 printf("%s",jcbq->name);
                 printf("进入输入井!");

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

			 //进程内存空间分配
			 mcbp=getpch(MCB);
			 mcbpr=getpch(MCB);

			 strcpy(mcbp->name,jcbq->name);
			 mcbp->atime=time;
			 mcbp->ntime=jcbq->ntime;
			 mcbp->drive=jcbq->drive;
			 mcbp->size=jcbq->size;
			 strcpy(mcbp->state,"已分配");
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
			 strcpy(mcbpr->state,"未分配");
			 mcbpr->state2=0;
			 mcbpr->link=mcbq->link;

			 printf("\n\t作业");
			 printf("%s",jcbq->name);
             printf("进入输入井!");

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
				 strcpy(mcbq->name,"空");
				 mcbq->size=mcbpr->size+mcbq->size;
				 strcpy(mcbq->state,"未分配");
				 mcbq->link=mcbpr->link;
				 mcbq->state2=0;
			 }else{
				 strcpy(mcbq->name,"空");
				 strcpy(mcbq->state,"未分配");
				 mcbq->state2=0;
			 }
		 }else{
             if(mcbtemp->state2==0){
				 mcbtemp->size=mcbtemp->size+mcbq->size;
				 mcbtemp->link=mcbq->link;
			 }else{
				 strcpy(mcbq->name,"空");
				 strcpy(mcbq->state,"未分配");
				 mcbq->state2=0;
			 } 
		 }
		 printf("\n\t该作业已成功回收!");
		 getch();
	 }
	 
}


void printmcb(){
	 printf("\n");
	 printf("\n\t输入井的状态:");
	 printf("\n");
	 printf("\n\t 名字 \t大小 \t状态\n ");
	 mcbpr=mcbhead->link;
	 while(mcbpr){
		 printmp();
		 mcbpr=mcbpr->link;
     }
	 printf("\n\t请按任意键进入下一分钟...");
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
        printf("\n\t      数计学院18级计科1班 安民 P181713164        ");
		printf("\n\t                                                 ");
		printf("\n\t              主存空间的分配与回收               ");
        printf("\n\t                                                 ");
		printf("\n\t     1 ：创建作业                                ");
		printf("\n\t     2 ：按 作业先来先服务 和 短进程优先 执行    ");
		printf("\n\t     3 ：按 作业先来先服务 和 进程先到先服务 执行");
		printf("\n\t     4 ：按 短作业优先 和 短进程优先 执行        ");
		printf("\n\t     5 ：按 短作业优先 和 进程先到先服务 执行    ");
		printf("\n\t     0 ：退出"); 
		printf("\n\t-------------------------------------------------");
		printf("\n\t请选择输入：");
		scanf("%d",&choose);
		while(choose>6){
			printf("\n\t选择错误,请重新输入>>>>>");
			scanf("%d",&choose);
		}
		return choose;
}

////////////////////////////////////////////////////////////////////////////////////
int main(){
	   char more;
	   int exitFlag; 
	   mcbhead=getpch(MCB);
	   strcpy(mcbhead->state,"未分配");
	   mcbq=getpch(MCB);
	   strcpy(mcbq->name,"空");
	   strcpy(mcbq->state,"未分配");
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
                           printf("\n\t未创建作业,请先创建!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=1;
					       FCFSSPF(); //作业先来先服务 和 短进程优先
						   
					   }
					   break;
				  case 3:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\t未创建作业,请先创建!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=1;
					       FCFS();//作业先来先服务 和 进程先到先服务
					   }
					   break;
				  case 4:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\t未创建作业,请先创建!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=2;
					      SJFSPF();  //短作业优先 和 短进程优先
					   }
					   break;
				  case 5:
					   if(jcbhead==NULL||jcbhead->link==NULL){
                           printf("\n\t未创建作业,请先创建!");
						   getch();
					   }else{
						   time=0;
						   thedrive=4;
						   findminjcb=1;
						   selectrun=2;
					       SJFFCFS(); //短作业优先 和 进程先到先服务
					   }
					   break;
				  default:  
					   scanf("%s",&more);
					   printf("\n\t输入错误,请重试!"); 
					   getch();
					   break;
			 }
	   }
return 0;
}


