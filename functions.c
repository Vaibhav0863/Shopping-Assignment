#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/declarations.h"

// // Checking authentication of user
// int is_customer_authorized()
// {

// }
NODE *head = NULL;

int len = 0;
int order_count = 0;
int cust_id = 0;

// Getting choice for main menu from user
int get_main_menu_choice()
{
	int choice;

	printf("----------------------------\n");
	printf("==============MAIN MENU===============\n");
	printf("0. EXIT\n1. REGISTER CUSTOMER\n2. CUSTOMER\n3. ADMIN\n");
	printf("----------------------------\n");

	printf("Enter Your Choice\n");
	scanf("%d",&choice);

	return choice;
}

int get_customer_menu_choice()
{
	int choice;
	printf("-----------------------------------\n");
	printf("================== CUSTOMER MENU ====================\n");
	printf("0. EXIT\n1. LIST PRODUCT CATEGORIES\n2. PRODUCT ITEMS BY NAME\n3. PRODUCT ITEMS PY PRICE\n4. ORDER AN ITEM\n5. LIST PENDING ORDER\n6. LIST DELIVERED ORDER\n");
	printf("Enter Choice : ");
	scanf("%d",&choice);
	printf("\n");

	return choice;
}

int get_admin_menu_choice()
{
	int choice;
	printf("------------------------------------\n");
	printf("================= ADMIN MENU ========================\n");
	printf("0. EXIT\n1. LIST PRODUCT CATEGORIES\n2. ADD PRODUCT CATEGORIES\n3. LIST ALL PRODUCT\n4. FIND PRODUCT BY NAME\n5. EDIT PRODUCT\n6. DELETE PRODUCT\n7. LIST PENDING OPDERS\n8. LIST DELIVERED ORDERS\n9. DISPATCH ORDER\n10. ADD PRODUCT\n");
	printf("\nEnter Your Choice : ");
	scanf("%d",&choice);

	return choice;
}

// Registraing user
void register_customer(FILE *file)
{
	file = fopen("customer.db","ab+");

	customer_data cust,cust1;

	// Taking Customer details from user

	get_customer_details(&cust1);

	if(file != NULL)
	{
		int flag = 0;

		while(fread(&cust,sizeof(cust),1,file))
		{
			if(cust.id == cust1.id)
			{
				flag = 1;
				break;
			}
		}

		if(flag == 1)
		{
			printf("------------------------------------\n");
			printf("CUSTOMER IS ALREADY REGISTERED     |\n");
			printf("------------------------------------\n");
		}
		else
		{
			fwrite(&cust1,sizeof(cust1),1,file);
			printf("------------------------------\n");
			printf("REGISTERED SUCCESSFULLY..... |\n");
			printf("------------------------------\n");
		}
	}
	else
	{
		printf("FILE ERROR\n");
	}

	fclose(file);
}

void get_customer_details(customer_data *cust)
{
	printf("=============================\n");
	printf("CUSTOMER REGIstartION\n");
	printf("\n");

		printf("Enter Id\n");
		scanf("%d",&cust->id);
	
		// cust_id++;
		// scanf("%d",&cust->id);

		printf("Enter Name\n");
		scanf("%s",cust->name);

		printf("Enter Address\n");
		scanf("%s",cust->address);	

	printf("==============================\n");
}


// ############# LISTING PRODUCT CATEGORIES##################
void list_product_categories(FILE *file)
{
	char data[SIZE];

	file = fopen("category.txt","r");

	if(file != NULL)
	{
		int flag = 0;
		printf("---------------------------\n");
		printf("CATEGORIES                |\n");
		printf("---------------------------\n");
		while(fgets(data,SIZE,file) != NULL)
		{
			printf("%s", data);
			flag = 1;
		}
		printf("\n");

		if(flag == 0)
		{
			printf("------------------------\n");
			printf("CATEGORY FILE IS EMPTY |\n");
			printf("------------------------\n");
		}
	}
	else
	{
		printf("FILE ERROR\n");
	}
	fclose(file);

}

// ######################## ADDING CATEGORIES IN FILE

void add_product_categories(FILE *file)
{
	char cat[SIZE];
	char data[SIZE];
	printf("Enter new category\n");
	scanf("%s",cat);

	// printf("%d\n", strcmp("mobile",cat));

	FILE *fp = fopen("category.txt","r");

	file = fopen("category.txt","a");

	if(file != NULL)
	{
		int flag = 0;
		// fputs(cat,file);
		// fputs("\n",file);

		while(fscanf(fp,"%s",data) != EOF)
		{
			if(strcmp(data,cat) == 0)
			{
				flag = 1;
				break;
			}
		}

		if(flag == 1)
		{
			printf("=========================\n");
			printf("CATEGORY ALREADY PRESENT |\n");
			printf("=========================\n");
		}
		else
		{
			fprintf(file,"%s\n",cat);
			printf("==================\n");
			printf("CATEGORY ADDED    |\n");
			printf("==================\n");

		}

		
	}
	else
	{
		printf("FILE ERROR\n");
	}
	fclose(file);
}

// ################# LOADING PRODUCT FILE INTO LIST ##################

void loadData(FILE *fp)
{
	DATA data;

	fp = fopen("product.db","rb");

	if(fp == NULL)
	{
		printf("PRODUCT FILE NOT FOUND\n");
		exit(1);
	}
	else
	{
		int flag = 0;

		while(fread(&data,sizeof(DATA),1,fp))
		{
			addLastNode(&data);
			flag = 1;
		}
		if(flag == 0)
		{
			printf("PRODUCT FILE WAS EMPTY\n");
		}
		else
		{
			printf("------------------------\n");
			printf("PRODUCT FILE LOADED... |\n");
			printf("------------------------\n");
		}
	}
	fclose(fp);
	///////////////////////////////

	order_details details;

	fp = fopen("orders.db","r");

	if(fp == NULL)
	{
		printf("-------------------------------\n");
		printf("ORDER FILE NOT FOUND          |\n");
		printf("-------------------------------\n");
	}
	else
	{
		int flag = 0;

		while(fread(&details,sizeof(order_details),1,fp))
		{
			addLastOrder(&details);
			flag = 1;
		}
		if(flag == 0)
		{
			printf("-------------------------------\n");
			printf("|ORDER FILE WAS EMPTY         |\n");     
			printf("-------------------------------\n");
		}
		else
		{
			printf("------------------------\n");
			printf("|ORDER FILE LOADED...  |\n");
			printf("------------------------\n");
		}
	}
}

void addLastNode(DATA *file_data)
{
	NODE *newNode,*temp;
	newNode = malloc(sizeof(NODE));

	newNode->data = *file_data;
	newNode->next = NULL;

	if(head == NULL)
	{
		head = newNode;
	}
	else
	{
		temp = head;

		while(temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
	len++;
}

///////////////////////////////////////////////////////////
void addLastOrder(order_details *file_data)
{
	ORD *newNode,*temp;
	newNode = malloc(sizeof(ORD));

	newNode->data = *file_data;
	newNode->next = NULL;

	if(start == NULL)
	{
		start = newNode;
	}
	else
	{
		temp = start;

		while(temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
	order_count++;
}

// ################ DISPLAYING DATA FROM PRODUCT FILE ###################
void display()
{
	NODE *trav = head;

	if(len>0)
	{
		for(int i=0;i<len;i++)
		{
			printf("-------------------------------------------------\n");
			printf("ID : %d\n", trav->data.id);
			printf("NAME : %s\n", trav->data.name);
			printf("CATEGORY : %s\n", trav->data.category);
			printf("RATE : %d\n", trav->data.rate);
			printf("-------------------------------------------------\n");

			trav = trav->next;
		}
		printf("\n");
	}
	else
	{
		printf("--------------------------------\n");
		printf("DATA NOT FOUND...\n");
		printf("--------------------------------\n");
	}
}

//################ DISPLAYING PENDING ORDERS FROM ORDER FILE ############
void display_Pending_Orders()
{
	ORD *trav = start;

	if(order_count>0)
	{
		for(int i=0;i<order_count;i++)
		{
			if(trav->data.status == 'P')
			{
				printf("-------------------------------------------------\n");
				printf("CUSTOMER ID : %d\n", trav->data.customer_id);
				printf("PRODUCT ID : %d\n", trav->data.product_id);
				printf("QUANTITY : %d\n", trav->data.quantity);
				printf("DATE : %d/%d/%d\n", trav->data.date.dd,trav->data.date.mm,trav->data.date.yy);
				printf("STATUS : %c\n", trav->data.status);
				printf("-------------------------------------------------\n");
			}

			trav = trav->next;
		}
		printf("\n");
	}
	else
	{
		printf("--------------------------------\n");
		printf("DATA NOT FOUND...              |\n");
		printf("--------------------------------\n");
	}
}

//################ DISPLAYING PENDING ORDERS FROM ORDER FILE ############
void display_Delivered_Orders()
{
	ORD *trav = start;

	if(order_count>0)
	{
		for(int i=0;i<order_count;i++)
		{
			if(trav->data.status == 'D')
			{
				printf("-------------------------------------------------\n");
				printf("CUSTOMER ID : %d\n", trav->data.customer_id);
				printf("PRODUCT ID : %d\n", trav->data.product_id);
				printf("QUANTITY : %d\n", trav->data.quantity);
				printf("DATE : %d/%d/%d\n", trav->data.date.dd,trav->data.date.mm,trav->data.date.yy);
				printf("STATUS : %c\n", trav->data.status);
				printf("-------------------------------------------------\n");
			}

			trav = trav->next;
		}
		printf("\n");
	}
	else
	{
		printf("--------------------------------\n");
		printf("DATA NOT FOUND...              |\n");
		printf("--------------------------------\n");
	}
}

char* getName()
{
	char *name = malloc(sizeof(char)*10);
	printf("Enter Product Name\n");
	scanf("%s",name);

	return name;
}

void findByName(char *name)
{
		NODE *trav = head;
		int flag = 0;

		// strlwr(name);

		int i=0;
		while(i < len)
		{
			if(strstr((trav->data.name),name) != NULL)
			{
				printf("====================================\n");
				printf("ID : %d\n", trav->data.id);
				printf("NAME : %s\n", trav->data.name);
				printf("CATEGORY : %s\n", trav->data.category);
				printf("RATE : %d\n", trav->data.rate);
				printf("====================================\n");
				
				flag = 1;
			}
			trav = trav->next;
			i++;
		}

		if (flag == 0)
		{
			printf("---------------------------------\n");
			printf("DATA NOT FOUND                  |\n");
			printf("---------------------------------\n");
		}

}


void editData()
{
	int id;
	printf("Enter ID for edit data\n");
	scanf("%d",&id);

	NODE *trav = head;

	if(trav == NULL)
	{
		printf("``````````````````````````\n");
		printf("FILE IS EMPTY            |\n");
		printf("``````````````````````````\n");
	}
	else
	{
		int flag = 0;
		while(trav != NULL)
		{
			if(trav->data.id == id)
			{
				flag = 1;
				break;
			}
			trav = trav->next;
		}

		if(flag == 1)
		{
			int temp;
			printf("Enter New Rate : ");
			scanf("%d",&temp);

			trav->data.rate = temp;

			printf("-------------------------\n");
			printf("RATE UPDATED            |\n");
			printf("-------------------------\n");
		}
		else
		{
			printf("```````````````````````````\n");
			printf("RECORD NOT FOUND          |\n");
			printf("```````````````````````````\n");
		}
	}

}

void delFirst()
{
	NODE *temp = malloc(sizeof(NODE));
	
	if(head == NULL)
	{
		printf("LIST IS EMPTY\n");
	}
	else
	{
		// printf("%d\n", head->data);
		temp = head;
		head = head->next;
		free(temp);
		len--;
	}
	
}

void delLast()
{
	if(head == NULL || len<1)
	{
		printf("LIST IS EMPTY\n");
	}
	else
	{
		NODE *trav = head;
		NODE *temp;
		for(int i=1;i<len-1;i++)
		{	
			trav = trav->next;
		}
		
		temp = trav->next;
		trav->next = NULL;
		free(temp);
		len--;
	}
}

void deleteNode()
{
	if(head == NULL)
	{
		printf("-------------------------\n");
		printf("FILE IS EMPTY           |\n");
		printf("-------------------------\n");
	}
	else
	{
		NODE *trav = head;
		NODE *temp;

		int index;
		printf("Enter Product ID : ");
		scanf("%d",&index);
		int cnt = 1;
		
		if(trav->data.id == index)
		{
			delFirst();
			printf("----------------------------------------\n");
			printf("PRODUCT GET DELETED FROM FILE          |\n");
			printf("----------------------------------------\n");
		}
		else
		{
			int flag = 0;
			for(int i=0;i<len-1;i++)
			{
				if(trav->next->data.id == index)
				{
					flag = 1;
					break;
				}
				trav = trav->next;

			}

			if(flag == 1)
			{
				if(trav->next!= NULL)
				{
					temp = trav->next;
					trav->next = temp->next;
					free(temp);
					len--;	
					printf("----------------------------------------\n");
					printf("PRODUCT GET DELETED FROM FILE          |\n");
					printf("----------------------------------------\n");
				}
				else
				{
					delLast();
					printf("----------------------------------------\n");
					printf("PRODUCT GET DELETED FROM FILE          |\n");
					printf("----------------------------------------\n");
				}
			}
			else
			{
				printf("ID NOT FOUND\n");
			}
		}
	
	}
}

//##################### ADDING ORDER TO FILE ##########################

void addData()
{
	// DATA *file_data = malloc(sizeof(DATA));
	DATA *file_data = malloc(sizeof(DATA));

	printf("Enter ID : ");
	scanf("%d",&file_data->id);

	printf("Enter Name : ");
	// fflush(stdin);
	scanf("%s",file_data->name);

	printf("Enter category : ");
	scanf("%s",file_data->category);

	printf("Enter Rate : ");
	scanf("%d",&file_data->rate);

	addLastNode(file_data);
}

// ###################### ADDING ORDER DEATAILS ################

void addOrderDetails()
{
	order_details *file_data = malloc(sizeof(order_details));

	printf("Enter Customer ID : ");
	scanf("%d",&file_data->customer_id);

	printf("\nEnter Product ID : ");
	scanf("%d",&file_data->product_id);

	printf("\nEnter quantity : ");
	scanf("%d",&file_data->quantity);

	printf("\nEnter Date(DD/MM/YY) : ");
	scanf("%d/%d/%d",&file_data->date.dd,&file_data->date.mm,&file_data->date.yy);

	// printf("%d/%d/%d\n",file_data->date.mm,file_data->date.mm,file_data->date.yy);
	// fflush(stdin);
	file_data->status = 'P';

	addLastOrder(file_data);
}

//####################### UPLOAD PRODUCT AND ORDER DETAILS ###############
void uploadData(FILE *fp)
{
	fp = fopen("product.db","wb");

	if(fp == NULL)
	{
		printf("INVALID FILE\n");
		exit(1);
	}
	else
	{
		
			NODE *trav = head;

			for(int i=0;i<len;i++)
			{
				fwrite(&trav->data,sizeof(DATA),1,fp);
				trav = trav->next;
			}
			printf("--------------------------\n");
			printf("PRODUCT FILE SAVED....   |\n");
			printf("--------------------------\n");


	}

	fclose(fp);

	//////////////////////////////////////
	fp = fopen("orders.db","wb");

	if(fp == NULL)
	{
		printf("INVALID FILE\n");
		exit(1);
	}
	else
	{
		
			// order_details data;
			ORD *trav = start;

			for(int i=0;i<order_count;i++)
			{
				fwrite(&trav->data,sizeof(order_details),1,fp);
				trav = trav->next;
			}
			printf("--------------------------\n");
			printf("ORDER FILE SAVED....     |\n");
			printf("--------------------------\n");


	}

	fclose(fp);
}

int cmpfunc(const void* a, const void* b)
{
	return strcmp(((struct DATA*)a)->name,((struct DATA*)b)->name);
}

void product_items_sort_by_name()
{
	DATA product_details[len];
	NODE *trav = head;

	if(trav == NULL)
	{
		printf("==========================\n");
		printf("FILE WAS EMPTY           |\n");
		printf("==========================\n");
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			product_details[i] = trav->data;
			trav = trav->next;
		}
		qsort(product_details,len,sizeof(DATA),cmpfunc);


		for(int i=0;i<len;i++)
		{
			printf("===================================\n");
			printf("ID : %d\n", product_details[i].id);
			printf("NAME : %s\n", product_details[i].name);
			printf("CATEGORY : %s\n", product_details[i].category);
			printf("RATE :%d\n", product_details[i].rate);
			printf("===================================\n");
		}
	}

	
}

int comparator(const void *p, const void *q) 
{ 
    // Get the values at given addresses 
    int l = ((const DATA *)p)->rate; 
    int r = ((const DATA *)q)->rate; 
  
    return l-r; 
} 

void product_items_sort_by_price()
{
	DATA product_details[len];
	NODE *trav = head;

	if(trav == NULL)
	{
		printf("==========================\n");
		printf("FILE WAS EMPTY           |\n");
		printf("==========================\n");
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			product_details[i] = trav->data;
			trav = trav->next;
		}
		
		qsort(product_details,len,sizeof(DATA),comparator); 


		for(int i=0;i<len;i++)
		{
			printf("===================================\n");
			printf("ID : %d\n", product_details[i].id);
			printf("NAME : %s\n", product_details[i].name);
			printf("CATEGORY : %s\n", product_details[i].category);
			printf("RATE :%d\n", product_details[i].rate);
			printf("===================================\n");
		}
	}
}

//###################### DISPATCHING ORDER ##############################

void Dispatch_Order()
{
	int id;

	printf("Enter Product ID to Dispatch : ");
	scanf("%d",&id);

	ORD *trav = start;

	if(order_count == 0)
	{
		printf("----------------------------\n");
		printf("NO ORDER FOR DISPATCH      |\n");
		printf("----------------------------\n");
	}
	else
	{
		int flag = 0;
		for(int i=0;i < order_count;i++)
		{
			if(trav->data.product_id == id)
			{
				trav->data.status = 'D';
				flag = 1;
			}
			trav = trav->next;
		}

		if(flag == 1)
		{
			printf("----------------------------\n");
			printf("ORDER IS DISPATCHED        |\n");
			printf("----------------------------\n");
		}
		else
		{
			printf("----------------------------\n");
			printf("PRODUCT NOT FOUND          |\n");
			printf("----------------------------\n");
		}

	}
}