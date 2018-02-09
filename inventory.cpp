/*File Name: inventory.cpp
 
 Author: Shane Fleming
 Date: 02/02/18
 Bergstein Enterprises, Ltd.
 
 Toner Inventory*/

#include <iostream>
#include <iomanip>

using namespace std;

int x = 0;                    // Counter, had to use to get my addF to work
const int nameWidth = 19;     // Used for print, setting desired size
const char separator = ' ';   // Used for print, setting desired size

struct Product                // Creating template for product
{
    int sku;
    string name;
    string location;
    int quantity;
    int desQuan;
};
Product product[101];

/******************************************************************
 print: Sets up a void function for formatting
 sets width, and setfill
 passes const for correct size
 ******************************************************************/

template<typename T> void print(T t, const int& width)
{
    cout << left << setw(width) << setfill(separator) << t;
}

/******************************************************************
 menuF: Displays the main Menu
 couts the main menu to be called from other functions
 ******************************************************************/

void menuF()
{
    cout << endl << "Manage Inventory Menu" << endl << endl
    << "1. Scan Toner" << endl
    << "2. Display inventory sorted by product name" << endl
    << "5. Add to inventory" << endl
    << "6. Quit the Program" << endl << endl
    << "Enter your choice: ";
}

/******************************************************************
 addF: Allows user to input products with stipulations
 Allows new product to be added to struct "product"
 ******************************************************************/

void addF()
{   cout << endl << "Enter sku number:" << endl;
    cin >> product[x].sku;
    cout << endl << "Enter the new product name:" << endl;
    cin.ignore();
    getline(cin, product[x].name);
    cout << "Enter the locator (no spaces):" << endl;
    cin >> product[x].location;
    cout << "Enter the quantity (0 or more):" << endl;
    cin >> product[x].quantity;
    cout << "Enter the desired quantity (0 or more):" << endl;
    cin >> product[x].desQuan;
    x++;
}

/******************************************************************
 headerF:  Displays a header for the store inventory
 Simple header function, wanted to clean up main()
 Uses fucntion void print, to reduce redundancy
 ******************************************************************/

void headerF()
{
    cout << endl;
    print("Product", nameWidth); print("Location", nameWidth);
    print("Quantity", nameWidth); print("Desired Quantity", nameWidth); 
    print("Order Amount", nameWidth);
    cout <<  endl
    << "________________________________________________________________________________________"
    << endl;
}

/******************************************************************
 displayF:  Displays entire stores inventory
 Calls headerF(), and print(), loops to print each item
 Uses fucntion void print, to reduce redundancy
 passes count into cow, for reference to total inventory
 ******************************************************************/

void displayF(int cow)
{
    int k = 0;  //Counter for comparing vs quanity of items entered
    int des = 0; //Desired amount of toner
    
    headerF();
    
    while (product[k].desQuan > 0 && product[k].quantity > - 1 && k < cow)
    {
        print(product[k].name, nameWidth);
        print(product[k].location, nameWidth);
        print(product[k].quantity, nameWidth);
        cout << setprecision(2) << fixed;
        print(product[k].desQuan, nameWidth);
        des = (product[k].desQuan - product[k].quantity);
        print(des, nameWidth);
        cout << endl;
        k++;
    }
}

/******************************************************************
 sortF: Takes an int as size, number of items in inventory
 Uses buble sort to sort entire inventory by product.name
 passes count into size, for reference to total inventory
 ******************************************************************/

void sortF(int size)
{
    bool swap;   //0/1 if swap happens
    
    do
    {
        swap = false;
        for (int count = 0; count < (size - 1); count++)
        {
            if (product[count].name > product[count + 1].name)
            {
                product[100] = product[count];
                product[count] = product[count + 1];
                product[count + 1] = product[100];
                swap = true;
            }
        }
    } while (swap);
} 

/******************************************************************
 searchF:  Takes a int as size, number of items in inventory
 Takes a string as find, specific product.name to find
 Uses binary search, to search entire inventory by product.name
 passes count into size, for reference to total inventory
 passes findPro into find, for refernce to what item to search for
 ******************************************************************/

int searchF(int size, int find)
{
    int first = 0,         // First array element
    last = size - 1,       // Last array element
    middle,                // Mid point of search
    position = -1;         // Postion of search value
    bool found = false;    // Flag
    
    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if (product[middle].sku == find)
        {
            found = true;
            position = middle;
        }
        else if (product[middle].sku > find)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return position;
}

/******************************************************************
 main:  While loop of menuF, to display choices for switch statment
 Takes in a int choice, and calls desired case 1-6
 Calls desired functions, and couts appropriate messages
 ******************************************************************/

int main()
{
    int choice = 0, count = 0, found = 0, findPro = 0;
                     //choice = users choice
                     //count = number of items entered
                     //found = stores postion of seachF
    
    while (choice != 6)
    {
        menuF();
        cin >> choice;
        
        switch (choice)
        {
            case 1:  // scan inventory
                sortF(count);
                addF();
                  count++;
          
                break;
                
            case 2:  //call to display all inventory
                sortF(count);
                displayF(count);
                
                break;
            
             case 4:  //call to display 1 product from inventory
                cout << endl << "Enter product name of product to find: ";
                cin>> findPro;
                
                sortF(count);
                
                found = searchF(count, findPro);
                
                if (found != -1)
                {
                    headerF();
                    
                    print(product[found].name, nameWidth);
                    cout << endl;
                }
                else
                    cout << endl << "ERROR Item NOT Found Please Try Again"
                    << endl;
                break;
   
            case 5:  // call to add to inventory
                sortF(count);
                addF();
                  count++;

                break;
 
            case 6:  //call to exit program
                cout << endl << "Exiting the program." << endl << endl;
        
                break;
                
            default:  //default error for incorrect input
                cout << endl << "ERROR Please Enter Valid Choice" << endl;
        }
    }
    
    return 0;
}
