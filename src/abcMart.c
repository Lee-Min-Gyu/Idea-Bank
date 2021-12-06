#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct shoes{
        char brand[10];
        int stock;
        int size;
        int price;
        int sold;
        struct shoes* next;
};
typedef struct shoes SHOES;

int search_shoes(SHOES* abc)
{
        SHOES* tmp=abc;
        char brand[10];
        int size;
        printf("찾으시는  신발 브랜드와 사이즈: ");
        scanf("%s %d",brand, &size);

        while(tmp!=NULL){
                if ((strcmp(tmp->brand,brand)==0)&&(tmp->size==size)){
                        printf("---------------------------------\n");
                        printf("Brand: %s\n",tmp->brand);
                        printf("Stock: %d\n",tmp->stock);
                        printf("price: %d\n",tmp->price);
                        printf("---------------------------------\n");
                        break;
                }
                tmp=tmp->next;
        }
        if(tmp==NULL)
                printf("찾으시는 물건이 없습니다.\n");
}
void add_stuff(SHOES* abc,int (*func)(SHOES*, int))
{
        SHOES* new= (SHOES*)malloc(sizeof(SHOES));
        SHOES* temp;
        temp=abc;

        char brand[10];
        int change;
        int size;
        int sold=0;
        printf("브랜드/사이즈/수량 입력:");
        scanf("%s %d %d",brand,&size,&change);
        while(temp!=NULL){
                if((strcmp(temp->brand,brand)==0)&&(temp->size==size)){
                        func(temp , change);
                        break;
                }
                temp=temp->next;
        }
        if(temp==NULL){
                temp=abc;
                while(temp->next!=NULL){
                        temp=temp->next;
                }
                int price;
                strcpy(new->brand,brand);
                new->size=size;
                new->stock=change;
                new->sold=sold;
                printf("가격입력:");
                scanf("%d",&price);
                new->price=price;
                temp->next=new;
                new->next=NULL;
        }
}
int payment(SHOES* abc,int (*func)(SHOES*, int))
{
        SHOES* temp2=abc;
        char brand[10];
        int change;
        int size;
        char reply[3];
        int price;
        printf("구매하실 브랜드/사이즈/수량 입력:");
        scanf("%s %d %d",brand,&size, &change);
        while(temp2!=NULL){
                if((strcmp(temp2->brand,brand)==0)&&(temp2->size==size)){
                        if (temp2->stock>=change){
                                price=(temp2->price)*change;
                                break;
                        }
                        else{
                                printf("재고 없음..\n");
                                goto out;
                        }
                }
                temp2=temp2->next;
        }
        if(temp2==NULL){
                printf("해당 상품 없음..\n");
                goto out;
        }

        printf("총금액: %d 결제하시겠습니까?(Yes/No)",price);
        scanf("%s",reply);
        if ((strcmp(reply,"Yes")==0)){
                func(temp2,(-change));
                temp2->sold+=(temp2->price)*change;
                printf("결제완료!\n");
                return 0;
        }
        else
                printf("승인취소..\n");
out:
        return 0;
}

int update(SHOES* cp, int change)
{
        SHOES* temp4=cp;
        temp4->stock+=change;
}

int total_sales(SHOES* abc)
{
        char  brand[10];
        printf("브랜드명 입력:");
        scanf("%s",brand);
        int total=0;
        SHOES* temp3 =abc;
        while(temp3!=NULL)
        {
                if(strcmp(temp3->brand,brand)==0){
                        total+=temp3->sold;
                        break;
                }
                temp3=temp3->next;
        }
        printf("%s의 총 판매액: %d\n",brand,total);
}
void file_load(SHOES* abc){
        char brand[10];
        int stock;
        int size;
        int price;
        int sold;

        FILE* fp=NULL;
        fp=fopen("storage.txt","a+");
        if(fp==NULL)
        {
                printf("실패!");
                return;
        }
        SHOES* start;
        SHOES* last;
        start = (SHOES*)malloc(sizeof(SHOES));
        fscanf(fp, "%s %d %d %d %d",brand, &stock, &size,&price,&sold);
        if (feof(fp)==0){
                strcpy(start->brand,brand);
                start->stock=stock;
                start->size=size;
                start->price=price;
                start->sold=sold;
                abc->next=start;
                start->next=NULL;
                last=start;
        }
        else free(start);
        while(1){
                start=(SHOES*)malloc(sizeof(SHOES));
                fscanf(fp, "%s %d %d %d %d",brand,&stock, &size,&price, &sold);
                if(feof(fp)==0){
                        strcpy(start->brand,brand);
                        start->stock=stock;
                        start->size=size;
                        start->price=price;
                        start->sold=sold;
                        last->next=start;
                        start->next=NULL;
                        last=start;
                }
                else{
                        free(start);
                        break;
                }
        }
        fclose(fp);
}

void menu(void)
{
        printf("========================\n");
        printf("1.검색\n");
        printf("2.입고\n");
        printf("3.결제\n");
        printf("4.판매 누적액\n");
        printf("5.종료\n");
        printf("========================\n");
}

void file_out(SHOES* abc)
{
        SHOES* exam=abc->next;
        FILE* fp=fopen("storage.txt","wt");
        if(exam==NULL)
                return;
        else{
                while(exam!=NULL){
                        fputs(exam->brand, fp);
                        fputs(" ", fp);
                        fprintf(fp,"%d",exam->stock);
                        fputs(" ", fp);
                        fprintf(fp,"%d",exam->size);
                        fputs(" ", fp);
                        fprintf(fp,"%d",exam->price);
                        fputs(" ", fp);
                        fprintf(fp,"%d",exam->sold);
                        fputs(" ", fp);
                        exam=exam->next;
                }
        }
        fclose(fp);
        return;
}

void main(void)
{
        int choice;
        SHOES* abc=(SHOES*)malloc(sizeof(SHOES));
        SHOES* tmp_node;
        abc->next=NULL;
        file_load(abc);

        while(1){
                menu();
                printf("메뉴를 선택하시오:");
                scanf("%d",&choice);

                if (choice<1||choice>=5){
                        file_out(abc);
                        break;
                }
                switch(choice){
                        case 1:
                                search_shoes(abc);
                                break;
                        case 2:
                                add_stuff(abc,update);
                                break;
                        case 3:
                                payment(abc,update);
                                break;
                        case 4:
                                total_sales(abc);
                                break;
                }

        }
        SHOES* pre1 = abc;
        SHOES* pre2;
        while(pre1!=NULL){
                pre2=pre1->next;
                free(pre1);
                pre1=pre2;
        }
}
