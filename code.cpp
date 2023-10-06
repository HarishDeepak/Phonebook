#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

struct node {
    char name[30];
    char number[15];
    char address[40];
    char email[40];
    struct node* left, * right, * mid;
};

struct node* searchin(struct node* root, char name[], char number[]);
void modify(struct node* ptr);
void savein(struct node* head, char fn[]);
void gosave();
void insertstackpush(struct node* temp);
void load();
struct node* pop(struct node* stack);
void display();
void print();
void save();
void savein(struct node* head, char fn[]);
struct node* input(struct node*);
void deletestackpush(struct node*);
struct node* deleteNode(struct node* root[], char key[]);
struct node* deleteNodeinside(struct node*, char key[], char number[]);
struct node* findmin(struct node* tree);
void inorder(int i);
void inorderinside(struct node*);
struct node* insertinside(struct node*, struct node*);
struct node* findmin(struct node* tree);

struct node* insertstack = NULL, * deletestack = NULL, * head[26];

int main() {
    struct node* n_node, * ptr;
    char ans;
    char n[30], num[15];
    int hash, k = 0;
    
    for (int i = 0; i < 26; i++) {
        head[i] = NULL;
    }
    
    int option;
    char key[40], keyn[40];
    int temp_status;
    
    cout << "************************************************************" << endl;
    cout << "*********************** PHONEBOOK ***************************" << endl;
    cout << "************************************************************" << endl;
    
    load();
    
    do {
        cout << "\nMENU\n1) INSERT\n2) PRINT\n3) SEARCH AND MODIFY\n4) DELETE A CONTACT\n5) EXIT\nENTER YOUR CHOICE: ";
        cin >> option;
        
        switch (option) {
            case 1:
                do {
                    n_node = input(n_node);
                    hash = int(n_node->name[0]) % 65;
                    insertstackpush(n_node);
                    head[hash] = insertinside(head[hash], n_node);
                    cout << "\nCONTINUE? (y/n): ";
                    cin >> ans;
                } while (ans == 'y' || ans == 'Y');
                break;
                
            case 2:
                print();
                break;
                
            case 3:
                cout << "ENTER THE SUBSCRIBER'S NAME TO BE SEARCHED: ";
                cin.ignore();
                cin.getline(key, 40);
                
                while (strlen(key) == 0) {
                    cout << "ENTER THE SUBSCRIBER'S NAME TO BE SEARCHED: ";
                    cin.getline(key, 40);
                }
                
                cout << "ENTER THE SUBSCRIBER'S NUMBER: ";
                cin >> keyn;
                while (key[k] != '\0') {
                    key[k] = toupper(key[k]);
                    k++;
                }
                hash = int(key[0]) % 65;
                ptr = searchin(head[hash], key, keyn);
                if (ptr != NULL) {
                    cout << "\n\nNAME: " << ptr->name << endl;
                    cout << "NUMBER: " << ptr->number << endl;
                    cout << "ADDRESS: " << ptr->address << endl;
                    cout << "E-MAIL: " << ptr->email << endl;
                    cout << "\n\nDo you want to modify? (y/n)\n\n";
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y') {
                        modify(ptr);
                    }
                }
                k = 0;
                break;
                
            case 4:
                cout << "ENTER THE NAME: ";
                cin.ignore();
                cin.getline(key, 40);
                
                while (strlen(key) == 0) {
                    cout << "ENTER THE NAME: ";
                    cin.getline(key, 40);
                }
                
                cout << "ENTER THE NUMBER: ";
                cin >> num;
                while (key[k] != '\0') {
                    key[k] = toupper(key[k]);
                    k++;
                }
                hash = int(key[0]) % 65;
                head[hash] = deleteNodeinside(head[hash], key, num);
                k = 0;
                break;
                
            case 5:
                break;
                
            default:
                cout << "ENTER A VALID CHOICE\n";
                break;
        }
    } while (option != 5);
    
    gosave();
    
    return 0;
}

struct node* insertinside(struct node* head, struct node* new_node) {
    if (head == NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->mid = NULL;
        head = new_node;
    }
    else {
        if (strcmp(head->name, new_node->name) == 0) {
            if (strcmp(head->number, new_node->number) == 0) {
                cout << "\n\t\tAlready exists!!!!" << endl;
            }
            else {
                head->mid = insertinside(head->mid, new_node);
            }
        }
        else if (strcmp(head->name, new_node->name) > 0) {
            head->left = insertinside(head->left, new_node);
        }
        else {
            head->right = insertinside(head->right, new_node);
        }
    }
    return head;
}

void print() {
    for (int i = 0; i < 26; i++) {
        if (head[i] == NULL) {
            continue;
        }
        if (head[i] != NULL) {
            inorderinside(head[i]);
        }
    }
    cout << "\n";
}

void inorderinside(struct node* head) {
    if (head != NULL) {
        inorderinside(head->left);
        cout << "\n\nNAME: " << head->name;
        cout << "\nNUMBER: " << head->number;
        cout << "\nADDRESS: " << head->address;
        cout << "\nE-MAIL: " << head->email;
        inorderinside(head->mid);
        inorderinside(head->right);
    }
}

void load() {
    struct node* new__node;
    int hash;
    char name[30];
    char number[15];
    char address[40];
    char email[40];
    char c[40];
    cout << "\n\n\n\t\tPlease wait for a moment\n";
    cout << "\t\tRetrieving data from file";
    char fn[] = "Directory_A.txt";
    for (int pp = 0; pp < 4; pp++) {
        Sleep(500);
        cout << ".";
    }
    cout << "\n\n";
    for (char i = 'A'; i <= 'Z'; ++i) {
        fn[10] = i;
        hash = int(i) % 65;
                fstream ob(fn);
        while (!ob.eof()) {
            ob.getline(c, 40);
            if (c[0] != '\0') {
                strcpy(name, c);
                ob.getline(c, 40);
                strcpy(number, c);
                ob.getline(c, 40);
                strcpy(address, c);
                ob.getline(c, 40);
                strcpy(email, c);
                new__node = (struct node*)malloc(sizeof(struct node));
                strcpy(new__node->name, name);
                strcpy(new__node->number, number);
                strcpy(new__node->address, address);
                strcpy(new__node->email, email);
                head[hash] = insertinside(head[hash], new__node);
            }
        }
        ob.close();
        ob.open(fn, ios::trunc);
        ob.close();
    }
}

struct node* input(struct node* ne_node) {
    char name[30];
    char number[15];
    char address[40];
    char email[40];
    int k = 0;
    
    cin.ignore();
    cout << "\nEnter the name of the subscriber: ";
    cin.getline(name, 30);
    
    while ((strlen(name) == 0)) {
        cout << "\nEnter a valid name: ";
        cin.getline(name, 30);
    }
    
    while (name[k] != '\0') {
        name[k] = toupper(name[k]);
        k++;
    }
    
    cout << "\nEnter the phone number (10 digits): ";
    cin.getline(number, 15);
    
    while (strlen(number) != 10) {
        cout << "\nEnter a valid 10-digit phone number: ";
        cin.getline(number, 15);
    }
    
    cout << "\nEnter the address: ";
    cin.getline(address, 40);
    
    cout << "\nEnter the E-mail: ";
    cin.getline(email, 40);
    
    ne_node = (struct node*)malloc(sizeof(struct node));
    strcpy(ne_node->name, name);
    strcpy(ne_node->number, number);
    strcpy(ne_node->address, address);
    strcpy(ne_node->email, email);
    
    return ne_node;
}

struct node* deleteNodeinside(struct node* root, char key[], char number[]) {
    struct node* temp;
    char mob_num[15];
    
    if (root == NULL) {
        return root;
    }

    if (strcmp(root->name, key) > 0) {
        root->left = deleteNodeinside(root->left, key, number);
    }
    else if (strcmp(root->name, key) < 0) {
        root->right = deleteNodeinside(root->right, key, number);
    }
    else {
        if (strcmp(root->number, number) == 0) {
            if (root->mid != NULL) {
                temp = findmin(root->mid);
                strcpy(root->name, temp->mid->name);
                strcpy(root->number, temp->mid->number);
                strcpy(root->address, temp->mid->address);
                strcpy(root->email, temp->mid->email);
                deletestackpush(temp->mid);
                free(temp->mid);
                temp->mid = NULL;
                return root;
            }
        }
        if (strcmp(root->number, number) != 0) {
            temp = root;
            while (strcmp(temp->mid->number, number) != 0) {
                temp = temp->mid;
            }
            deletestackpush(temp->mid);
            free(temp->mid);
            if (temp->mid->mid != NULL) {
                temp->mid = temp->mid->mid;
            }
            else {
                temp->mid = NULL;
            }
            return temp;
        }
        if (root->left == NULL) {
            temp = root->right;
            deletestackpush(root);
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            temp = root->left;
            deletestackpush(root);
            free(root);
            return temp;
        }
        temp = findmin(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->number, temp->number);
        strcpy(root->address, temp->address);
        strcpy(root->email, temp->email);
        root->right = deleteNodeinside(root->right, temp->name, temp->number);
        deletestackpush(root);
    }
    return root;
}

struct node* findmin(struct node* tree) {
    struct node* node1 = tree;
    if (tree->mid == NULL) {
        while (node1 != NULL && node1->left != NULL)
            node1 = node1->left;
        return node1;
    }
    else if (tree->mid != NULL) {
        while (node1 != NULL && node1->mid->mid != NULL)
            node1 = node1->mid;
        return node1;
    }
}

void insertstackpush(struct node* temp) {
    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    strcpy(newnode->name, temp->name);
    strcpy(newnode->number, temp->number);
    strcpy(newnode->address, temp->address);
    strcpy(newnode->email, temp->email);
    newnode->left = insertstack;
    insertstack = newnode;
}

void display() {
    struct node* ptr;
    if (insertstack == NULL)
        cout << "Stack is empty";
    else {
        ptr = insertstack;
        cout << "Stack elements are: ";
        while (ptr != NULL) {
            cout << ptr->name << " ";
            ptr = ptr->left;
        }
    }
}

void deletestackpush(struct node* temp) {
    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    strcpy(newnode->name, temp->name);
    strcpy(newnode->number, temp->number);
    strcpy(newnode->address, temp->address);
    strcpy(newnode->email, temp->email);
    newnode->left = deletestack;
    deletestack = newnode;
}

void gosave() {
    fstream ob;
    char fn[] = "Directory_A.txt", c[40];
    int i = 0, hash, j;
    
    cout << "\nSAVING TO FILE";
    for (int pp = 0; pp < 4; pp++) {
        cout << ".";
        Sleep(500);
    }
    cout << "\n";
    
    while (insertstack != NULL) {
        fn[10] = insertstack->name[0];
        ob.open(fn, ios::app);
        ob << "\n" << insertstack->name << "\n" << insertstack->number << "\n" << insertstack->address << "\n" << insertstack->email;
        ob.close();
        insertstack = pop(insertstack);
    }
    
    while (deletestack != NULL) {
        hash = int(deletestack->name[0]) % 65;
        fn[10] = deletestack->name[0];
                ob.open(fn, ios::out);
        savein(head[hash], fn);
        ob.close();
        deletestack = pop(deletestack);
    }
}

struct node* pop(struct node* stack) {
    struct node* temp;
    if (stack != NULL) {
        temp = stack;
        stack = stack->left;
        free(temp);
        return stack;
    }
    return NULL;
}

void savein(struct node* head, char fn[]) {
    ofstream ob;
    if (head != NULL) {
        ob.open(fn, ios::app);
        ob << "\n" << head->name << "\n" << head->number << "\n" << head->address << "\n" << head->email;
        ob.close();
        savein(head->left, fn);
        savein(head->right, fn);
    }
}

struct node* searchin(struct node* root, char name[], char number[]) {
    if (root == NULL) {
        cout << "\nNO SUCH SUBSCRIPTION FOUND\n";
        return root;
    }
    else if (strcmp(root->name, name) == 0) {
        if (strcmp(root->number, number) == 0)
            return root;
        else
            return searchin(root->mid, name, number);
    }
    else if (strcmp(root->name, name) < 0) {
        return searchin(root->right, name, number);
    }
    else if (strcmp(root->name, name) > 0) {
        return searchin(root->left, name, number);
    }
}

void modify(struct node* ptr) {
    char a;
    int hash1, hash, k = 0;
    struct node* ptr1 = (struct node*)malloc(sizeof(struct node));
    
    do {
        cout << "\nWhich entity has to be modified?\nN - NAME\nA - ADDRESS\nP - PHONE NUMBER\nE - EMAIL ID\n";
        cin >> a;
        
        switch (a) {
            case 'N':
                char name[30];
                cin.ignore();
                cout << "Enter the new name of the subscriber: ";
                cin.getline(name, 30);
                
                while (strlen(name) == 0) {
                    cout << "Enter a valid name: ";
                    cin.getline(name, 30);
                }
                
                while (name[k] != '\0') {
                    name[k] = toupper(name[k]);
                    k++;
                }
                
                hash1 = int(name[0]) % 65;
                hash = int(ptr->name[0]) % 65;
                strcpy(ptr1->name, name);
                strcpy(ptr1->address, ptr->address);
                strcpy(ptr1->number, ptr->number);
                strcpy(ptr1->email, ptr->email);
                head[hash1] = insertinside(head[hash1], ptr1);
                print();
                head[hash] = deleteNodeinside(head[hash], ptr->name, ptr->number);
                print();
                cout << "\n\nNAME: " << ptr1->name << endl;
                deletestackpush(ptr1);
                deletestackpush(ptr);
                break;
                
            case 'A':
                char address[40];
                cin.ignore();
                cout << "Enter the new address of the subscriber: ";
                cin.getline(address, 40);
                
                while (strlen(address) == 0) {
                    cout << "Enter a valid address: ";
                    cin.getline(address, 40);
                }
                
                strcpy(ptr->address, address);
                deletestackpush(ptr);
                break;
                
            case 'P':
                char no[20];
                cin.ignore();
                cout << "Enter the new phone number of the subscriber: ";
                cin.getline(no, 20);
                
                while (strlen(no) != 10) {
                    cout << "Enter a valid 10-digit phone number: ";
                    cin.getline(no, 20);
                }
                
                strcpy(ptr->number, no);
                deletestackpush(ptr);
                break;
                
            case 'E':
                char mail[40];
                cin.ignore();
                cout << "Enter the new E-mail ID of the subscriber: ";
                cin.getline(mail, 40);
                
                while (strlen(mail) == 0) {
                    cout << "Enter a valid E-mail ID: ";
                    cin.getline(mail, 40);
                }
                
                strcpy(ptr->email, mail);
                deletestackpush(ptr);
                break;
                
            default:
                cout << "Unrecognized character entered!\nKindly re-enter a character from the list or press 'M' to cancel the MODIFY process\n";
                cin >> a;
        }
        
        if (a != 'M' && a != 'm') {
            cout << "Modification still working... press 'M' to terminate, and to process press 'Y'\n";
            cin >> a;
        }
    } while (a != 'M' && a != 'm');
}


       
