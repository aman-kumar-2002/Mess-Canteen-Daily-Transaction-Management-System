#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <ctime>

using namespace std;

struct MenuItem
{
    int id;
    string name;
    double price;
};

vector<MenuItem> menu;
vector<string> transactions;

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ostringstream date;
    date << 1900 + ltm->tm_year << "-"
         << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
         << setw(2) << setfill('0') << ltm->tm_mday;
    return date.str();
}

// 🛠️ Load Menu from File
void loadMenu()
{
    ifstream file("menu.txt");
    if (!file)
    {
        cout << "No menu file found. Initializing empty menu.\n";
        return;
    }
    menu.clear();
    MenuItem item;
    while (file >> item.id >> item.price)
    {
        file.ignore();
        getline(file, item.name);
        menu.push_back(item);
    }
    file.close();
}

// 💾 Save Menu to File
void saveMenu()
{
    ofstream file("menu.txt");
    for (const auto &item : menu)
    {
        file << item.id << " " << item.price << " " << item.name << endl;
    }
    file.close();
}

// 📑 Load Transactions from File
void loadTransactions()
{
    ifstream file("transactions.txt");
    if (!file)
        return;
    transactions.clear();
    string line;
    while (getline(file, line))
    {
        transactions.push_back(line);
    }
    file.close();
}

// 💾 Save Transactions to File
void saveTransactions()
{
    ofstream file("transactions.txt");
    for (const auto &trans : transactions)
    {
        file << trans << endl;
    }
    file.close();
}

// 🧾 Display Menu
void displayMenu()
{
    cout << "\n================= MENU =================\n";
    cout << left << setw(10) << "ID" << setw(25) << "Item" << setw(10) << "Price" << endl;
    cout << "----------------------------------------\n";
    for (const auto &item : menu)
    {
        cout << left << setw(10) << item.id << setw(25) << item.name << setw(10) << item.price << endl;
    }
    cout << "----------------------------------------\n";
}

// 🛒 Purchase Item
void purchaseItem(const string &studentName)
{
    displayMenu();

    int id;
    cout << "Enter Item ID to purchase: ";
    cin >> id;

    auto it = find_if(menu.begin(), menu.end(), [id](const MenuItem &item)
                      { return item.id == id; });

    if (it != menu.end())
    {
        string date = getCurrentDate();
        ostringstream trans;
        trans << studentName << " purchased " << it->name << " for Rs."
              << fixed << setprecision(2) << it->price << " on " << date;

        transactions.push_back(trans.str());
        saveTransactions();
        cout << "Purchase successful!\n";
    }
    else
    {
        cout << "Item ID not found!\n";
    }
}

// 🧾 View Transaction History
void viewTransactions()
{
    cout << "\n============= TRANSACTIONS =============\n";
    if (transactions.empty())
    {
        cout << "No transactions found.\n";
        return;
    }
    for (const auto &trans : transactions)
    {
        cout << trans << endl;
    }
    cout << "========================================\n";
}

// 📊 Monthly Bill by Student and Month
void viewMonthlyBill(const string &studentName, const string &month)
{
    double total = 0.0;
    bool found = false;

    cout << "\n====== Monthly Bill for " << studentName << " (" << month << ") ======\n";

    for (const auto &trans : transactions)
    {
        size_t pos1 = trans.find(" purchased ");
        size_t pos2 = trans.find(" for Rs.");
        size_t pos3 = trans.find(" on ");

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos)
        {
            string name = trans.substr(0, pos1);
            string item = trans.substr(pos1 + 11, pos2 - (pos1 + 11));
            string priceStr = trans.substr(pos2 + 8, pos3 - (pos2 + 8));
            string date = trans.substr(pos3 + 4);

            double price = stod(priceStr);

            if (name == studentName && date.substr(0, 7) == month)
            {
                cout << item << " - Rs. " << price << " on " << date << endl;
                total += price;
                found = true;
            }
        }
    }

    if (!found)
    {
        cout << "No transactions found for " << studentName << " in " << month << ".\n";
    }
    else
    {
        cout << "----------------------------------------\n";
        cout << "Total Bill: Rs. " << fixed << setprecision(2) << total << endl;
    }
}

// 👩‍🏫 Admin Menu
void adminMenu()
{
    int choice;
    do
    {
        cout << "\n======= ADMIN MENU =======\n";
        cout << "1. Add Item\n2. Remove Item\n3. View Menu\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            MenuItem newItem;
            cout << "Enter Item ID: ";
            cin >> newItem.id;
            cout << "Enter Price: ";
            cin >> newItem.price;
            cin.ignore();
            cout << "Enter Item Name: ";
            getline(cin, newItem.name);

            menu.push_back(newItem);
            saveMenu();
            cout << "Item added successfully!\n";
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter Item ID to remove: ";
            cin >> id;

            auto it = remove_if(menu.begin(), menu.end(), [id](const MenuItem &item)
                                { return item.id == id; });

            if (it != menu.end())
            {
                menu.erase(it, menu.end());
                saveMenu();
                cout << "Item removed successfully.\n";
            }
            else
            {
                cout << "Item ID not found!\n";
            }
        }
        else if (choice == 3)
        {
            displayMenu();
        }
    } while (choice != 4);
}

// 👨‍🎓 Student Menu
void studentMenu(const string &studentName)
{
    int choice;
    do
    {
        cout << "\n======= STUDENT MENU =======\n";
        cout << "1. View Menu\n2. Purchase Item\n3. View Transactions\n4. View Monthly Bill\n5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            displayMenu();
        }
        else if (choice == 2)
        {
            purchaseItem(studentName);
        }
        else if (choice == 3)
        {
            viewTransactions();
        }
        else if (choice == 4)
        {
            string month;
            cout << "Enter month (YYYY-MM): ";
            cin >> month;
            viewMonthlyBill(studentName, month);
        }
    } while (choice != 5);
}

// 🌟 Main Function
int main()
{
    loadMenu();
    loadTransactions();

    string studentName;
    cout << "Enter your name: ";
    cin >> studentName;

    int choice;
    cout << "\n1. Admin Login\n2. Student Login\nChoose: ";
    cin >> choice;

    if (choice == 1)
    {
        adminMenu();
    }
    else if (choice == 2)
    {
        studentMenu(studentName);
    }

    return 0;
}
