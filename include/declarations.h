#ifndef DECLARATIONS 
#define DECLARATIONS 
#define SIZE 50

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// FUNCTION DECLARATIONS

void get_customer_details();
int get_main_menu_choice();
void register_customer();
int get_customer_menu_choice();
int get_admin_menu_choice();
void list_product_categories();
void add_product_categories();
void loadData();
void addLastNode();
void display();
void findByName();
char* getName();
void editData();
void deleteNode();
void delFirst();
void delLast();
void addData();
void uploadData();
void product_items_sort_by_name();
void product_items_sort_by_price();
int cmpfunc();
int is_customer_authorized();
void addLastOrder();
void addOrderDetails();
void display_Pending_Orders();
void display_Delivered_Orders();
void Dispatch_Order();





//++++++++++++++++++++++++++++ STRUCTURES +++++++++++++++++++++++++

typedef struct Customer
{
	int id;
	char name[SIZE];
	char address[SIZE];
}customer_data;

typedef struct Orders
{
	int customer_id;
	int product_id;
	int quantity;
	struct date
	{
		int dd;
		int mm;
		int yy;
	}date;
	char status;

}order_details;

typedef struct ORD
{
	order_details data;
	struct ORD *next;
}ORD;

ORD *start = NULL;

typedef struct DATA
{
		int id;
		char name[SIZE];
		char category[SIZE];
		int rate;
}DATA;

typedef struct NODE
{
	DATA data;
	struct NODE *next;

}NODE;

#endif