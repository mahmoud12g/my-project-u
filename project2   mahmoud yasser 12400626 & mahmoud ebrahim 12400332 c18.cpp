#include <iostream>
#include <string>
using namespace std;

struct Branch {
    int id;
    string name;
    string location;
    Branch* next;
};


struct AccountHolder {
    int id;
    string name;
    double balance;
    int branchId;
    AccountHolder* next;
};

class Bank {
public:
    Branch* branchHead;
    AccountHolder* holderHead;

public:
    Bank() {
        branchHead = nullptr;
        holderHead = nullptr;
    }

    
    void addBranch(int id, string name, string location) {
        Branch* newBranch = new Branch{id, name, location, branchHead};
        branchHead = newBranch;
        cout << "Branch added successfully.\n";
    }

    void displayBranches() {
        Branch* temp = branchHead;
        if (!temp) {
            cout << "No branches available.\n";
            return;
        }
        while (temp) {
            cout << "ID: " << temp->id << ", Name: " << temp->name << ", Location: " << temp->location << endl;
            temp = temp->next;
        }
    }

    
    void searchBranchById(int id) {
        Branch* temp = branchHead;
        while (temp) {
            if (temp->id == id) {
                cout << "Branch found: " << temp->name << " located at " << temp->location << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Branch not found.\n";
    }

    
    void addHolder(int id, string name, double balance, int branchId) {
        AccountHolder* newHolder = new AccountHolder{id, name, balance, branchId, holderHead};
        holderHead = newHolder;
        cout << "Account holder added successfully.\n";
    }

    
    void removeHolder(int id) {
        AccountHolder* temp = holderHead;
        AccountHolder* prev = nullptr;
        while (temp) {
            if (temp->id == id) {
                if (prev)
                    prev->next = temp->next;
                else
                    holderHead = temp->next;

                delete temp;
                cout << "Holder removed successfully.\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Holder not found.\n";
    }

    
    void displayHolderById(int id) {
        AccountHolder* temp = holderHead;
        while (temp) {
            if (temp->id == id) {
                cout << "ID: " << temp->id << ", Name: " << temp->name
                    << ", Balance: " << temp->balance << ", Branch ID: " << temp->branchId << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Holder not found.\n";
    }

    
    void searchHolderByName(string name) {
        AccountHolder* temp = holderHead;
        while (temp) {
            if (temp->name == name) {
                cout << "Holder found: ID: " << temp->id << ", Balance: " << temp->balance << ", Branch ID: " << temp->branchId << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Holder not found.\n";
    }

    
    void displayHoldersByBranch(int branchId) {
        AccountHolder* temp = holderHead;
        bool found = false;
        cout << "Holders in Branch ID " << branchId << " sorted by balance:\n";

        
        for (AccountHolder* i = holderHead; i != nullptr; i = i->next) {
            for (AccountHolder* j = i->next; j != nullptr; j = j->next) {
                if (i->balance < j->balance) {
                    swap(i->id, j->id);
                    swap(i->name, j->name);
                    swap(i->balance, j->balance);
                    swap(i->branchId, j->branchId);
                }
            }
        }

        while (temp) {
            if (temp->branchId == branchId) {
                found = true;
                cout << "ID: " << temp->id << ", Name: " << temp->name << ", Balance: " << temp->balance << endl;
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "No holders in this branch.\n";
        }
    }

    
    void updateHolder(int id, string newName, double newBalance) {
        AccountHolder* temp = holderHead;
        while (temp) {
            if (temp->id == id) {
                temp->name = newName;
                temp->balance = newBalance;
                cout << "Holder information updated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Holder not found.\n";
    }
};

int main() {
    Bank bank;
    int choice, id, branchId;
    string name, location;
    double balance;

    do {
        cout << "\n1. Add Branch\n2. Display Branches\n3. Search Branch by ID\n";
        cout << "4. Add Holder\n5. Remove Holder\n6. Display Holder by ID\n";
        cout << "7. Search Holder by Name\n8. Display Holders by Branch\n";
        cout << "9. Update Holder\n10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Branch ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Branch Name: ";
                getline(cin, name);
                cout << "Enter Branch Location: ";
                getline(cin, location);
                bank.addBranch(id, name, location);
                break;
            case 2:
                bank.displayBranches();
                break;
            case 3:
                cout << "Enter Branch ID: ";
                cin >> id;
                bank.searchBranchById(id);
                break;
            case 4:
                cout << "Enter Holder ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Holder Name: ";
                getline(cin, name);
                cout << "Enter Holder Balance: ";
                cin >> balance;
                cout << "Enter Branch ID: ";
                cin >> branchId;
                bank.addHolder(id, name, balance, branchId);
                break;
            case 5:
                cout << "Enter Holder ID to Remove: ";
                cin >> id;
                bank.removeHolder(id);
                break;
            case 6:
                cout << "Enter Holder ID: ";
                cin >> id;
                bank.displayHolderById(id);
                break;
            case 7:
                cin.ignore();
                cout << "Enter Holder Name: ";
                getline(cin, name);
                bank.searchHolderByName(name);
                break;
            case 8:
                cout << "Enter Branch ID: ";
                cin >> branchId;
                bank.displayHoldersByBranch(branchId);
                break;
            case 9:
                cout << "Enter Holder ID to Update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Balance: ";
                cin >> balance;
                bank.updateHolder(id, name, balance);
                break;
            case 10:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);

    return 0;
}
