#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib> 
#include<sstream> 
using namespace std;

struct customer
{
    int id;
    string name;
    string contact;
};
struct Game
{
    int id;
    string name;
    int price;
};
struct transaction
{
    int custid;
    string custname;
    int gameid;
    string gamename;
    int turns;
    int totalamount;
    string paymentmethod;
};


void add_customer()
{
    customer cust;
    ofstream file("customers.txt", ios::app);
    cout << "Enter Customer ID: ";
    cin >> cust.id;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, cust.name);
    cout << "Enter Contact Number: ";
    getline(cin, cust.contact);
    file << "id : " << cust.id << "\nname : " << cust.name << "\ncontact : "  << cust.contact << endl;
    file.close();
    cout << "Customer added successfully!\n";
}

void view_menu()
{
    ifstream file("games.txt");
    Game game;
    cout << "\n--- Game Menu ---\n";
    cout << left << setw(10) << "Game ID" << setw(25) << "Game Name" << "Price\n";
    cout << "------------------------------------------\n";
    while (file >> game.id >> ws && getline(file, game.name, '|') && file >> game.price) {
        cout << left << setw(10) << game.id << setw(25) << game.name << game.price << endl;
    }
    file.close();
}

void generate_bill() {
    int custId, gameId, turns, gamePrice = 0;
    string custName, gameName, paymentMethod;

    // Open game file for reading
    ifstream gameFile("games.txt");
    if (!gameFile) {
        cout << "Error opening games.txt\n";
        return;
    }

    // Open transaction file for writing
    ofstream transFile("transactions.txt", ios::app);
    if (!transFile) {
        cout << "Error opening transactions.txt\n";
        return;
    }

    // Input customer info
    cout << "Enter Customer ID: ";
    cin >> custId;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, custName);

    // Show games
    view_menu();

    // Game selection
    cout << "Enter Game ID to play: ";
    cin >> gameId;
    cout << "Enter Number of Turns: ";
    cin >> turns;

    // Search game
    bool found = false;
    int id;
    while (gameFile >> id) {
        gameFile.ignore(); // skip whitespace
        getline(gameFile, gameName, '|');
        gameFile >> gamePrice;
        if (id == gameId) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Game not found!\n";
        return;
    }

    int totalAmount = gamePrice * turns;

    cin.ignore();
    cout << "Select Payment Method (Cash / Card / UPI): ";
    getline(cin, paymentMethod);

    // Show bill
    cout << "\n--- Bill ---\n";
    cout << "Customer: " << custName << " (ID: " << custId << ")\n";
    cout << "Game: " << gameName << " | Turns: " << turns << " | Total: " << totalAmount << endl;
    cout << "Payment Method: " << paymentMethod << endl;

    // Save bill to file
    transFile << custId << "|" << custName << "|" << gameId << "|"
              << gameName << "|" << turns << "|" << totalAmount << "|"
              << paymentMethod << endl;

    gameFile.close();
    transFile.close();
}

// Function to view customer transactions
void view_transactions() {
    ifstream file("transactions.txt");

    if (!file) {
        cout << "Error opening transactions file.\n";
        return;
    }

    cout << "\n========== Customer Transaction Records ==========\n\n";
    cout << "Cust ID  | Name             | Game ID | Game Name        | Turns | Total   | Payment Method\n";
    cout << "-------------------------------------------------------------------------------------------\n";

    string line;

    while (getline(file, line)) {
        string custId, custName, gameId, gameName, turnsStr, totalAmountStr, paymentMethod;

        istringstream iss(line);
        getline(iss, custId, '|');
        getline(iss, custName, '|');
        getline(iss, gameId, '|');
        getline(iss, gameName, '|');
        getline(iss, turnsStr, '|');
        getline(iss, totalAmountStr, '|');
        getline(iss, paymentMethod, '|');

        // Print the transaction in a neat row format
        cout << setw(8) << custId << " | "
             << setw(15) << custName << " | "
             << setw(7) << gameId << " | "
             << setw(17) << gameName << " | "
             << setw(5) << turnsStr << " | "
             << setw(7) << totalAmountStr << " | "
             << paymentMethod << endl;
    }

    file.close();
}



int main()
{
    int ch;
    while(1)
    {
        cout<<"\n******PLAYZONE BILLING SYSTEM******\n";
        cout<<"1. Add Customer\n";
        cout<<"2. View Game Menu\n";
        cout<<"3. Generate Bill\n";
        cout<<"4. View Customer Transaction\n";
        cout<<"5. Exit \n";
        cout<<"enter your choice:";
        cin>>ch;
        switch(ch)
        {
            case 1:
                {
                    add_customer();
                    break;
                    
                }
            case 2:
                {
                    view_menu();
                    break;
                }
            case 3:
                {
                    generate_bill();
                    break;
                }
            case 4:
                {
                    view_transactions();
                    break;
                }
            case 5:
                {
                    cout<<"****Exiting Program****\n";
                    cout<<"****Thank You****";
                    exit(0);
                }
            default:
                {
                    cout<<"**Invalid Choice**";
                }
        }
        
    }
}
