#include <stdio.h>
#include <stdlib.h>

struct Item {
    char name[50];
    int quantity;
    float price;
    float total;
};

int main() {
    struct Item cart[100];
    int n = 0, choice, i;
    float grandTotal = 0.0, taxRate = 0.1, finalAmount;
    
    FILE *fptr;

    do {
        printf("\n----- Billing System -----\n");
        printf("1. Add Item\n");
        printf("2. View Cart\n");
        printf("3. Generate and Save Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nEnter item name: ");
                scanf("%s", cart[n].name);
                printf("Enter quantity: ");
                scanf("%d", &cart[n].quantity);
                printf("Enter price per item: ");
                scanf("%f", &cart[n].price);
                cart[n].total = cart[n].quantity * cart[n].price;
                n++;
                printf("Item added successfully!\n");
                break;

            case 2:
                printf("\n---- Items in Cart ----\n");
                if (n == 0) {
                    printf("Cart is empty.\n");
                } else {
                    printf("%-20s %-10s %-10s %-10s\n", "Item Name", "Quantity", "Price", "Total");
                    for (i = 0; i < n; i++) {
                        printf("%-20s %-10d %-10.2f %-10.2f\n", cart[i].name, cart[i].quantity, cart[i].price, cart[i].total);
                    }
                }
                break;

            case 3:
                if (n == 0) {
                    printf("Cart is empty. Add items first!\n");
                } else {
                    fptr = fopen("receipt.txt", "w");
                    if (fptr == NULL) {
                        printf("Error opening file!\n");
                        exit(1);
                    }
                    grandTotal = 0.0;
                    printf("\n-------- BILL RECEIPT --------\n");
                    fprintf(fptr, "-------- BILL RECEIPT --------\n");
                    printf("%-20s %-10s %-10s %-10s\n", "Item Name", "Quantity", "Price", "Total");
                    fprintf(fptr, "%-20s %-10s %-10s %-10s\n", "Item Name", "Quantity", "Price", "Total");
                    
                    for (i = 0; i < n; i++) {
                        printf("%-20s %-10d %-10.2f %-10.2f\n", cart[i].name, cart[i].quantity, cart[i].price, cart[i].total);
                        fprintf(fptr, "%-20s %-10d %-10.2f %-10.2f\n", cart[i].name, cart[i].quantity, cart[i].price, cart[i].total);
                        grandTotal += cart[i].total;
                    }

                    finalAmount = grandTotal + (grandTotal * taxRate);

                    printf("\nSubtotal: %.2f", grandTotal);
                    printf("\nTax (10%%): %.2f", grandTotal * taxRate);
                    printf("\nGrand Total: %.2f\n", finalAmount);

                    fprintf(fptr, "\nSubtotal: %.2f", grandTotal);
                    fprintf(fptr, "\nTax (10%%): %.2f", grandTotal * taxRate);
                    fprintf(fptr, "\nGrand Total: %.2f\n", finalAmount);

                    fclose(fptr);
                    printf("\nReceipt saved to 'receipt.txt'\n");
                }
                break;

            case 4:
                printf("Exiting program. Thank you!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);

    return 0;
}

