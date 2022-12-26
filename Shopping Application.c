#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "functions.c"
#include "include/declarations.h"


#define SIZE 50

// Declaration of file pointer globally
FILE *file;

// ++++++++++++++++++++++++++MENU OPERATIONS+++++++++++++++++++++++

// Main menu of shopping application
enum main_menu{EXIT,REGISTER_CUSTOMER,CUSTOMER,ADMIN};
enum customer_menu{LIST_PRODUCT_CATEGORIES=1,PRODUCT_ITEMS_BY_NAME,PRODUCT_ITEMS_BY_PRICE,ORDER_AN_ITEM,LIST_PENDING_ORDER,LIST_DELIVERED_ORDER};
enum admin_menu{ADD_PRODUCT_CATEGORY=2,LIST_ALL_PRODUCT,FIND_PRODUCT_BY_NAME,EDIT_PRODUCT,DELETE_PRODUCT,LIST_PENDING_ORDERS,LIST_DELIVERED_ORDERS,DISPATCH_ORDER,ADD_PRODUCT};










int main()
{
	int main_menu_choice;
	int customer_menu_choice;
	int admin_menu_choice;

	loadData(file);

	while(main_menu_choice = get_main_menu_choice())
	{
		switch(main_menu_choice)
		{
			case REGISTER_CUSTOMER:
					// printf("Register Customer\n");
					// Registraing customer by taking username and password from customer
					register_customer(file);
					break;
			case CUSTOMER:
					// printf("Customer\n");
					// if(is_customer_authorized())
				if(1)
					{
						while(customer_menu_choice = get_customer_menu_choice())
						{
							switch(customer_menu_choice)
							{
								case LIST_PRODUCT_CATEGORIES:
												list_product_categories(file);
												break;
								case PRODUCT_ITEMS_BY_NAME:
												product_items_sort_by_name();
												// printf("PRODUCT ITEMS BY NAME\n");

												break;
								case PRODUCT_ITEMS_BY_PRICE:
												product_items_sort_by_price();
												break;
								case ORDER_AN_ITEM:
												// printf("ORDER_AN_ITEM\n");
												addOrderDetails();
												break;
								case LIST_PENDING_ORDER:
												// printf("LIST_PENDING_ORDER\n");
												display_Pending_Orders();
												break;
								case LIST_DELIVERED_ORDER:
												// printf("LIST_DELIVERED_ORDER\n");
												display_Delivered_Orders();
												break;
								default:
										printf("```````````````````\n");
										printf("INVALID CHOICE\n");
										printf("```````````````````\n");
										break;
							}
						}
					}
					break;
			case ADMIN:
					// printf("Admin\n");
					while(admin_menu_choice = get_admin_menu_choice())
					{
						switch(admin_menu_choice)
						{
							case LIST_PRODUCT_CATEGORIES:
											// printf("LIST_PRODUCT_CATEGORIES\n");
											list_product_categories(file);
											break;

							case ADD_PRODUCT_CATEGORY:
											// printf("ADD_PRODUCT_CATEGORY\n");
											add_product_categories(file);
											break;

							case LIST_ALL_PRODUCT:
											// printf("LIST_ALL_PRODUCT\n");
											display();
											break;

							case FIND_PRODUCT_BY_NAME:
											// printf("FIND_PRODUCT_BY_NAME\n");
											findByName(getName());
											break;

							case EDIT_PRODUCT:
											// printf("EDIT_PRODUCT\n");
											editData();
											break;

							case DELETE_PRODUCT:
											// printf("DELETE_PRODUCT\n");
											deleteNode();
											break;

							case LIST_PENDING_ORDERS:
											// printf("LIST_PENDING_ORDER\n");
											display_Pending_Orders();
											break;

							case LIST_DELIVERED_ORDERS:
											// printf("LIST_DELIVERED_ORDER\n");
											display_Delivered_Orders();
											break;


							case DISPATCH_ORDER:
											// printf("DISPATCH_ORDER\n");
											Dispatch_Order();
											break;
							case ADD_PRODUCT:
											// printf("ADD PRODCUT\n");
												addData();
											break;
							default:
									printf("INVALID CHOICE\n");
									break;
						}
					}
					break;
			default:
				printf("--------------------------\n");
				printf("Invalid Menu Option      |\n");
				printf("--------------------------\n");
				break;
		}
	}
	uploadData(file);
}

