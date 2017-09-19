#include<iostream>
#include<iomanip>
#include<cstring>
#include"AidApp.h"
#include"AmaProduct.h"
#include"AmaPerishable.h"
using namespace std;
namespace sict {
    //default constructor
    AidApp::AidApp(const char* filename)
    {
        
        strcpy(filename_, filename);
        for (int i = 0; i < MAX_NO_RECS; i++)
        {
            product_[i] = nullptr;
        }
        noOfProducts_ = 0;
        loadRecs();
    }
    //pause the program until you press<enter>

    void AidApp::pause()const {
        cout << "Press Enter to continue..." << endl;
        while (getchar() != '\n');
    }
    //dispalys menu
    int AidApp::menu() {
        int option;
        cout << "Disaster Aid Supply Management Program" << endl
            << "1- List products" << endl
            << "2- Display product" << endl
            << "3- Add non-perishable product" << endl
            << "4- Add perishable product" << endl
            << "5- Add to quantity of purchased products" << endl
            << "0- Exit program" << endl
            << "> ";
        cin >> option;
        cin.clear();
        if (option >= 0 && option <= 5) {
            return option;
        }
        else return -1;
    }
    //loads data from file to array pointer of product
    void AidApp::loadRecs() {
        char type;
        int data_read = 0;
        datafile_.open(filename_, ios::in);
        if (datafile_.fail())
        {

            datafile_.clear();
            datafile_.close();
            datafile_.open(filename_, ios::out);
            datafile_.close();
        }
        else 
        {
            while (!datafile_.fail())
            {
                delete product_[data_read];
                datafile_ >> type;
                if (!datafile_.fail()) 
                {
                    datafile_.ignore(10, ',');
                    if (type == 'N')//create new dynamic memory of that index in pointer as product type
                    {
                        product_[data_read] = new AmaProduct();
                        product_[data_read]->load(datafile_);
                        data_read++;
                    }

                    if (type == 'P')//create new dynamic memory of that index in pointer as perishable product type
                    {
                        product_[data_read] = new AmaPerishable();
                        product_[data_read]->load(datafile_);
                        data_read++;
                    }
                }
               
            }

            noOfProducts_ = data_read;
            datafile_.close();
        }
    }
    //saves record to file
    void  AidApp::saveRecs() {
        datafile_.open(filename_, ios::out);
        if (!datafile_.fail()) {
            for (int i = 0; i < noOfProducts_; i++) {
              
                product_[i]->store(datafile_);
            }
            datafile_.close();
        }
    }
    //lists the product
    void AidApp::listProducts()const {
        double total = 0;
        cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry" << endl;
        cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

        for (int i = 0; i < noOfProducts_; i++) {
            cout << setfill(' ') << setw(4) << right << i + 1 << " | ";
            
            product_[i]->write(cout, true);
            cout << endl;
     //       total += ((product_[i]->cost) * (product_[i]->qtyNeeded));
             total += product_[i]->cost() * product_[i]->quantity();
            if (i % 10 == 0&& i!=0) {
                pause();
            }
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Total cost of support: $" << setprecision(2) << total;
    }

    //serches the product from file
    int  AidApp::SearchProducts(const char* sku)const {
        int id = -2;
        for (int i = 0; i < noOfProducts_; i++)
        {
            if (*product_[i] == sku)
            {
                id = i;
            }
        }
        return id;
        

    }
    void  AidApp::addQty(const char* sku) {
        int found = SearchProducts(sku);
        int quantity;
        if (found == -2)
        {
            cout << "Not found!" << endl;
        }
        else
        {
            cout << "Please enter the number of purchased items: ";
            cin >> quantity;
            if (cin.fail())
            {
                cout << "Invalid quantity value!" << endl;
            }
            else
            {
                int qtyNeeded = product_[found]->qtyNeeded();
                int qty = product_[found]->quantity();
                int required = (qtyNeeded - qty);

                if (quantity <= required)
                {
                    product_[found]->operator+=(quantity);
                    cin.ignore(1000, '\n');

                }
                else
                {
                    cout << "Too many items; only " << required << " is needed, please return the extra " << quantity - required << " items." << endl;
                }
                cout << endl << "Updated!" << endl << endl;
            }
        }cin.clear();
    }
    void  AidApp::addProduct(bool isPerishable) {
        if (isPerishable)
        {
            product_[noOfProducts_] = new AmaPerishable();
            product_[noOfProducts_]->read(cin);
            noOfProducts_++;
        }
        else
        {
            product_[noOfProducts_] = new AmaProduct();
            product_[noOfProducts_]->read(cin);
            noOfProducts_++;
        }
        saveRecs();
        cout << endl << "Product added" << endl << endl;
    

    }
    int  AidApp::run() {
       
        char sku[MAX_SKU_LEN];
        int option;
        int found;
        while ((option = menu()) != 0) {
            switch (option)
            {
            case 1:
                listProducts();
                cout << endl;
                cout << endl;
                pause();
                break;

            case 2:
                cout << endl << "Please enter the SKU: ";
                cin >> sku;
                cout << endl;
                found = SearchProducts(sku);
                if (found != -1)
                {
                    product_[found]->write(cout, false);
                }
                else
                {
                    cout << "Not found!" << endl;
                }
                cout << endl;
                cout << endl;
                pause();
                
                break;

            case 3:
                cout << endl;
                addProduct(false);
                break;

            case 4:
                cout << endl;
                addProduct(true);
                break;

            case 5:
                cout << endl;
                cout << "Please enter the SKU: ";
                cin >> sku;
                cout << endl;
                found = SearchProducts(sku);
                if (found != -1)
                {
                    product_[found]->write(cout, false);
                }
                else
                {
                    cout << "Not found!" << endl;
                }
                cout << endl;
                cout << endl;
                addQty(sku);
                break;
                ;

            default:
                cout << "===Invalid Selection, try again.===" << endl;;
                pause();
                break;
            }
        }cout << endl << "Goodbye!!" << endl;
       
        return 0;
    }
}