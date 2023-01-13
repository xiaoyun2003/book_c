#include <stdio.h>
#include<string.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */


//定义图书数量;
int BOOK_NUM=0; 
//定义图书目录信息结构体 
typedef struct Book{
	//统一书号，用整形数组存，方便后面排序 
	char *ISBN;
	//书名 
	char *name;
	//作者
	char *author;
	//出版社 
	char *puber;
	//年 
	char *date; 
	//价格 
	double price;
}Book,*Bookptr; 
//定义链表节点
typedef struct LNode{
	Book book;
	struct LNode *next;
}LNode,*LNodeptr; 

//创建链表节点，并自动添加到链表后面 ,返回当前创建得节点指针 
LNodeptr creat_node(LNodeptr lptr,Book book){
	if(lptr==NULL){
		//创建头节点 
		lptr=malloc(sizeof(LNode));
		lptr->next=NULL;
		lptr->book=book;
		return lptr;
	}
	while(lptr->next!=NULL){
		lptr=lptr->next;
	}
	LNodeptr new_nodeptr=malloc(sizeof(LNode));
	new_nodeptr->next=NULL;
	new_nodeptr->book=book;
	lptr->next=new_nodeptr;
	return new_nodeptr;
} 
//根据data查找链表节点，返回找到得节点地址，否则返回null
//type=0:isbn
//type=1:书名 
LNodeptr find_node(LNodeptr lptr,int type,char *data){
	LNodeptr ptr=lptr;
	while(ptr!=NULL){
		//isbn具有唯一性，找到就返回 
		if(type==0){
		if(strcmp(ptr->book.ISBN,data)==0){
			return ptr;
		}
	    } 
	if(type==1){
		if(strcmp(ptr->book.name,data)==0){
			return ptr;
		}	
	}
		ptr=ptr->next;
	}
	return NULL;
}
//删除指定节点,成功返回头节点指针，否则返回NULL 
LNodeptr delete_node(LNodeptr lptr,char *isbn){
	LNodeptr ptr=lptr;
	//前向节点
	LNodeptr pptr=lptr; 
	while(ptr!=NULL){
		if(strcmp(ptr->book.ISBN,isbn)==0){
			if(ptr==pptr){
				//删除头指针 
			lptr=lptr->next;
			}else{
			pptr->next=ptr->next;
		    }
			ptr->next=NULL;
			free(&ptr->book);
			return lptr;
		}
		pptr=ptr;
		ptr=ptr->next;
	}
	return NULL;
} 
//打印链表节点数据
void print_node (LNodeptr lptr){
	Book book=lptr->book;
	printf("%-13s ",book.ISBN);
	printf("%-30s ",book.name);
	printf("%-20s ",book.author);
	printf("%-30s ",book.puber);
	printf("%s ",book.date);
	printf("%.2f ",book.price);
	printf("\n");
}
//打印所有链表节点数据
void print_all_node(LNodeptr lptr){
	printf("ISBN--------- Title------------------------- Author-------------- Publisher--------------------- Pub-date-- Price---\n");
	LNodeptr ptr=lptr;
		while(ptr!=NULL){
		print_node(ptr);
		ptr=ptr->next;
	}
} 
//排序链表,根据isbn号 ,冒泡排序算法 
LNodeptr sort_node(LNodeptr lptr){
	//创建一个头节点
	LNodeptr head=malloc(sizeof(LNode));
	LNode  * pre, * cur, *next, * end, * temp;
    head->next= lptr;
    end = NULL;
    //从链表头开始将较大值往后沉
    while(head -> next != end)
    {
        for(pre = head, cur = pre -> next, next = cur -> next; next != end; pre = pre -> next, cur = cur -> next, next = next -> next)
        {
            //相邻的节点比较
            if(strcmp(cur->book.ISBN,next->book.ISBN)>0)
            {
                cur -> next = next -> next;
                pre -> next = next;
                next -> next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
    return head->next;
}

//日期合法性检查,合法返回0，否则返回-1 
int check_date(int year,int month,int day){

	//基础判断
	if(!(1<=month && month<=12 && 1<=day && day<=31)) {
		return -1;
	}
	//判断闰年 
	if(month==2){
	if(day==29){
		if(year%400==0)return 0;
		if(year%100==0)return -1;
		if(year%4==0)return 0;
		return -1;
	}
	}
	if(day==31){
		if(month==1 || month==3 || month==5 || month==7 || month==8 ||month==10 || month==12)return 0;
		return -1;
	}
	return 0;
}


//添加图书信息
LNodeptr insert_book(LNodeptr lptr) {
	//创建Book
	Book book; 
	
	//为char*初始化
	book.ISBN= (char*)malloc(8);
	book.author=(char*)malloc(8);
	book.date= (char*)malloc(8);
	book.puber=(char*)malloc(8);
	book.name= (char*)malloc(8);
	
	gets(book.ISBN);
	printf("%10s ","ISBN:");
	gets(book.ISBN);
	
	printf("%10s ","Title:");
	gets(book.name);
	
	printf("%10s ","Author:");
	gets(book.author);
	
	printf("%10s ","Publisher:");
	gets(book.puber);
	
	
	printf("%10s ","Pub date:");
	char *temp;
	scanf("%s",&temp);
	int year,month,day;
	sscanf(&temp,"%d/%d/%d",&year,&month,&day);
	
    //sprintf(&temp,"%4d/02%d/02%d",year,month,day);
    while(check_date(year,month,day)!=0){
		printf("Incorrect date! Please reenter:");
		scanf("%s",&temp);
		sscanf(&temp,"%d/%d/%d",&year,&month,&day);
    }
    sprintf(book.date,"%4d/%02d/%02d",year,month,day);
 

	printf("%10s ","Price:");
	scanf("%lf",&book.price);
	

	lptr=creat_node(lptr,book);
	BOOK_NUM++;
	return lptr;
}

//根据书名寻找,返回链表结果集 
LNodeptr  find_book_by_name(LNodeptr lptr,char *name){
	LNodeptr r=find_node(lptr,1,name);
	LNodeptr pr=r;
	if(r==NULL){
		return NULL;
	}
	while(r->next!=NULL) {
	LNodeptr r1=find_node(r->next,1,name);
	if(r1!=NULL){
		r->next=r1;
		r=r1;
	}else{
		break;
	}
    }
    r->next=NULL;
    return pr;
}





int main(int argc, char *argv[]) {
	//创建链表
	LNodeptr head=NULL;
	LNodeptr cur_node;
	char *a1=(char*)malloc(8);
	char q;
	
	while(1){
		char input='0';
		if(input!='\n')printf("Append Find Remove Modify Show Quit >");
		input=getchar();
	
		
		if(input!='\n'){
		switch(input){
			case 'Q':case 'q':
				printf("Thank you! Goodbye!");
				return 0;
				break;
			case 'A':case'a':
				if(head==NULL){
					head=insert_book(head);
				}else{
					cur_node=insert_book(head);
				}
				break;
			case 'S':case 's':
				cur_node=sort_node(head);
				if(cur_node!=NULL){
				print_all_node(cur_node);
			    }
			    break;
			case 'F':case'f':
				printf("Title: ");
				gets(a1);
				gets(a1);
				cur_node=find_book_by_name(head,a1);
				if(cur_node==NULL){
					printf("Not found!\n");
				}else{
					print_all_node(cur_node);
				}
				break;
			case 'R':case 'r':
				printf("ISBN: ");
				//我也不知道这里为啥要写两个，一个就直接跳过了 
				gets(a1);
				gets(a1);
				if(find_node(head,1,a1)==NULL){
					printf("Not found!\n");
					break;
				}
				while(1){
					printf("Remove(y/n)? ");
					q=getchar();
					if(q=='Y' || q=='y' || q=='n' || q=='N'){
						break;
					}else{
						printf("Incorrect answer!\n");
					}
				}
				if(q=='y' || q=='Y'){
					cur_node=delete_node(head,a1);
					if(cur_node!=NULL)head=cur_node; 
				}
				break;
			case 'M':case'm':
				printf("ISBN: ");
				//我也不知道这里为啥要写两个，一个就直接跳过了 
				gets(a1);
				gets(a1);
				if(find_node(head,1,a1)==NULL){
					printf("Not found!\n");
					break;
				}
				
				while(1){
					printf("Modify(y/n)? ");
					q=getchar();
					if(q=='Y' || q=='y' || q=='n' || q=='N'){
						break;
					}else{
						printf("Incorrect answer!\n");
					}
				}
				if(q=='y' || q=='Y'){
					//把之前的节点删掉 
					cur_node=delete_node(head,a1);
					if(cur_node!=NULL)head=cur_node;
					//然后创建应该新的节点，以此实现修改，滑稽..... 
					insert_book(head);
				}
				break;
			default:
				printf("Incorrect choice!\n");
		}
		
	}
	}
	return 0;
}


int main1(){
	Book book; 
	char *a;
	book.ISBN=(char*)malloc(8);
    scanf("%s",book.ISBN);
	printf("%s",book.ISBN);
	
	return 0;
}
