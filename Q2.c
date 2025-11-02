#include <stdio.h>
#include <string.h>

void customerDetails(char customerName[], char cnic[])
{
    printf("\nEnter customer Name: ");
    fgets(customerName, 50, stdin);
    int length = strlen(customerName);
    if (length > 0 && customerName[length - 1] == '\n')
        {
            customerName[length - 1] = '\0';
        }
    // char ch;
    // int i = 0;

    // for (i = 0; i < 50 - 1; i++)
    // {
    //     ch = getchar();
    //     if (ch == '\n')
    //         break;
    //     customerName[i] = ch;
    // }
    // customerName[i] = '\0';

    printf("\nEnter Customer CNIC: ");
    scanf("%s", cnic);
    // fgets(cnic, 15, stdin);
    // int cnicLength = strlen(cnic);
    // if (cnicLength > 0 && cnic[cnicLength - 1] == '\n')
    // {
    //     cnic[cnicLength - 1] = '\0';
    // }
    printf("\nCustomer %s added successfully!\n", customerName);
}

void displayInventory(int productCodes[], int quantities[], int prices[], int numOfProducts)
{
    printf("\n===================== INVENTORY =====================\n");
    printf("\nProduct Code \t Quantity in Stock \t Price per Item\n");
    for (int i = 0; i < numOfProducts; i++)
    {
        printf("|%-16.3d|%-23d|%-10d |\n", productCodes[i], quantities[i], prices[i]);
    }
}

void addItemTocart(int productCodes[], int quantities[], int *numOfProducts, int cartIndexes[], int cartQuantities[], int *cartCount)
{
    if (*cartCount >= 50) {
    printf("\nCart is full! Cannot add more items.\n");
    return;
}

    int requiredItemCode, requiredQuantity;
    printf("\nEnter product code of product you want to add to cart: ");
    scanf("%d", &requiredItemCode);

    int found = 0;
    for (int i = 0; i < *numOfProducts; i++)
    {
        if (productCodes[i] == requiredItemCode)
        {
            found = 1;
            printf("\nEnter Quantity: ");
            scanf("%d", &requiredQuantity);
            if (quantities[i] >= requiredQuantity)
            {
                quantities[i] -= requiredQuantity;
                cartIndexes[*cartCount] = i;
                cartQuantities[*cartCount] = requiredQuantity;
                (*cartCount)++;
                printf("\nItem added to cart successfully!");
                // updateInventory(productCodes, quantities, &numOfProducts, cartIndexes, cartQuantities, &cartCount);
                break;
            }
            else
            {
                printf("\nRequired quantity not available!");
            }
            break;
        }
    }
    if (!found)
    {
        printf("\nItem not found!");
    }
}
// void updateInventory(int productCodes[], int quantities[], int *numOfProducts, int cartIndexes[], int cartQuantities[], int *cartCount){

//     for (int i = 0; i < *numOfProducts; i++)
//     {
//         if (cartIndexes[i] == productCodes[i])
//         {
//             quantities[i] -= cartQuantities[i];
//             printf("\nInventory updated!");
//         }
//     }
// }

void displayCart(int cartIndexes[], int cartQuantities[], int *cartCount, int productCodes[], int prices[])
{
    printf("\n============== Items in your CART ===============\n");
    if (*cartCount == 0)
    {
        printf("\nYou haven't added any items to your cart yet!\n");
    }
    else
    {
        for (int i = 0; i < *cartCount; i++)
        {
            int index = cartIndexes[i];
            int itemTotal = prices[index] * cartQuantities[i];
            printf("\nProduct Code: %d\nQuantity: %d\nItem total: %d\n", productCodes[index], cartQuantities[i], itemTotal);
        }
    }
}

float calculateBill(int productCodes[], int prices[], int *numOfProducts, int cartIndexes[], int cartQuantities[], int *cartCount, float *totalBill)
{
    *totalBill = 0;
    for (int i = 0; i < *cartCount; i++)
    {
        int index = cartIndexes[i];
        *totalBill += prices[index] * cartQuantities[i];
    }
    return *totalBill;
}
float applyPromo(float *totalBill, float *discount)
{

    *discount = 0;
    char voucherCode[10];
    printf("\nWe are offering a promocode of Eid2025.");
    printf("\nDo you have the voucher? (Enter 'Eid2025' if yes): ");
    scanf("%s", voucherCode);
    if (strcmp(voucherCode, "Eid2025") == 0 || strcmp(voucherCode, "eid2025") == 0)
    {
        *discount = *totalBill * 0.25;
        *totalBill = *totalBill - *discount;
    }
    else
    {
        *discount = 0;
        *totalBill = *totalBill;
        printf("\nNo discount applied.");
    }
    printf("\nTotal Bill before discount: %.2f\nDiscount was: %.2f\nYour total Bill After discount: %.2f\n", *totalBill + *discount, *discount, *totalBill);
    return *totalBill;
}

void showInvoice(char customerName[], char cnic[], int cartIndexes[], int cartQuantities[], int productCodes[], int prices[], int *cartCount, float *discount, float *totalBill)
{
    printf("\nCustomer Name: %s\nCNIC: %s\n", customerName, cnic);
    printf("\nProduct Code \t Quantity \t Price per Item \t Item Total\n");
    for (int i = 0; i < *cartCount; i++)
    {
        int index = cartIndexes[i];
        int itemTotal = prices[index] * cartQuantities[i];
        printf("|%-16.3d|%-15d|%-23d|%-8d|\n", productCodes[index], cartQuantities[i], prices[index], itemTotal);
    }
    printf("\nTotal Bill before discount: %.2f", *totalBill);
    printf("\nDiscount: %.2f", *discount);
    printf("\nTotal Bill after discount: %.2f\n", *totalBill - *discount);
}

int main()
{
    char customerName[100];
    char cnic[20];
    int productCodes[4] = {1, 2, 3, 4};
    int quantities[4] = {50, 10, 20, 8};
    int prices[4] = {100, 200, 300, 150};
    int numOfProducts = 4;
    int cartIndexes[50], cartQuantities[50], cartCount = 0;
    float totalBill = 0;
    float discount = 0;
    int choice;

    do
    {
        printf("\n========= Talha's Supermarket Management System =========\n");
        printf("Select an option:\n");
        printf("1. Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Items in cart\n");
        printf("5. Display Total Bill\n");
        printf("6. Show Invoice\n");
        printf("7. Exit\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
            customerDetails(customerName, cnic);
            break;
        case 2:
            displayInventory(productCodes, quantities, prices, numOfProducts);
            break;
        case 3:
            char addItem;
            do
            {
                addItemTocart(productCodes, quantities, &numOfProducts, cartIndexes, cartQuantities, &cartCount);

                discount = 0;
                printf("\nDo you want to add another item to your cart? (Y/N): ");
                scanf(" %c", &addItem);
            } while (addItem == 'Y' || addItem == 'y');
            break;
        case 4:
            displayCart(cartIndexes, cartQuantities, &cartCount, productCodes, prices);
            break;
        case 5:
        {
            if (cartCount == 0)
            {
                printf("\nPick items first! You cart is Empty!\n");
            }
            else
            {
                totalBill = calculateBill(productCodes, prices, &numOfProducts, cartIndexes, cartQuantities, &cartCount, &totalBill);
                totalBill = applyPromo(&totalBill, &discount);
            }
            break;
        }
        case 6:
        {
            {
                if (cartCount == 0)
                {
                    printf("\nPick items first! Your cart is Empty!\n");
                }
                else
                {
                    totalBill = calculateBill(productCodes, prices, &numOfProducts, cartIndexes, cartQuantities, &cartCount, &totalBill);

                    if (discount == 0)
                    {
                        char applyNow;
                        printf("\nNo discount has been applied yet. Do you want to apply a promo code now? (Y/N): ");
                        scanf(" %c", &applyNow);
                        if (applyNow == 'Y' || applyNow == 'y')
                        {
                            totalBill = applyPromo(&totalBill, &discount);
                        }
                    }

                    showInvoice(customerName, cnic, cartIndexes, cartQuantities, productCodes, prices, &cartCount, &discount, &totalBill);
                }

                break;
            }
        case 7:
            printf("Exiting system. Thank you!\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
        }
    } while (choice != 7);

    return 0;
}