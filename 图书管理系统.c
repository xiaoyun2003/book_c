#include <stdio.h>
#include<string.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */


//����ͼ������;
int BOOK_NUM=0; 
//����ͼ��Ŀ¼��Ϣ�ṹ�� 
typedef struct Book{
	//ͳһ��ţ�����������棬����������� 
	char *ISBN;
	//���� 
	char *name;
	//����
	char *author;
	//������ 
	char *puber;
	//�� 
	char *date; 
	//�۸� 
	double price;
}Book,*Bookptr; 
//��������ڵ�
typedef struct LNode{
	Book book;
	struct LNode *next;
}LNode,*LNodeptr; 

//��������ڵ㣬���Զ���ӵ�������� ,���ص�ǰ�����ýڵ�ָ�� 
LNodeptr creat_node(LNodeptr lptr,Book book){
	if(lptr==NULL){
		//����ͷ�ڵ� 
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
//����data��������ڵ㣬�����ҵ��ýڵ��ַ�����򷵻�null
//type=0:isbn
//type=1:���� 
LNodeptr find_node(LNodeptr lptr,int type,char *data){
	LNodeptr ptr=lptr;
	while(ptr!=NULL){
		//isbn����Ψһ�ԣ��ҵ��ͷ��� 
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
//ɾ��ָ���ڵ�,�ɹ�����ͷ�ڵ�ָ�룬���򷵻�NULL 
LNodeptr delete_node(LNodeptr lptr,char *isbn){
	LNodeptr ptr=lptr;
	//ǰ��ڵ�
	LNodeptr pptr=lptr; 
	while(ptr!=NULL){
		if(strcmp(ptr->book.ISBN,isbn)==0){
			if(ptr==pptr){
				//ɾ��ͷָ�� 
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
//��ӡ����ڵ�����
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
//��ӡ��������ڵ�����
void print_all_node(LNodeptr lptr){
	printf("ISBN--------- Title------------------------- Author-------------- Publisher--------------------- Pub-date-- Price---\n");
	LNodeptr ptr=lptr;
		while(ptr!=NULL){
		print_node(ptr);
		ptr=ptr->next;
	}
} 
//��������,����isbn�� ,ð�������㷨 
LNodeptr sort_node(LNodeptr lptr){
	//����һ��ͷ�ڵ�
	LNodeptr head=malloc(sizeof(LNode));
	LNode  * pre, * cur, *next, * end, * temp;
    head->next= lptr;
    end = NULL;
    //������ͷ��ʼ���ϴ�ֵ�����
    while(head -> next != end)
    {
        for(pre = head, cur = pre -> next, next = cur -> next; next != end; pre = pre -> next, cur = cur -> next, next = next -> next)
        {
            //���ڵĽڵ�Ƚ�
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

//���ںϷ��Լ��,�Ϸ�����0�����򷵻�-1 
int check_date(int year,int month,int day){

	//�����ж�
	if(!(1<=month && month<=12 && 1<=day && day<=31)) {
		return -1;
	}
	//�ж����� 
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


//���ͼ����Ϣ
LNodeptr insert_book(LNodeptr lptr) {
	//����Book
	Book book; 
	
	//Ϊchar*��ʼ��
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

//��������Ѱ��,������������ 
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
	//��������
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
				//��Ҳ��֪������ΪɶҪд������һ����ֱ�������� 
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
				//��Ҳ��֪������ΪɶҪд������һ����ֱ�������� 
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
					//��֮ǰ�Ľڵ�ɾ�� 
					cur_node=delete_node(head,a1);
					if(cur_node!=NULL)head=cur_node;
					//Ȼ�󴴽�Ӧ���µĽڵ㣬�Դ�ʵ���޸ģ�����..... 
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
