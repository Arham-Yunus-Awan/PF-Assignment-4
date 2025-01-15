// all libraries included which are needed

// basic library for input & output
#include <iostream>

// for convert string into an object for better string handling and specific operations poosible like the comma handling
#include <sstream>

// for working with files in the code
#include<fstream>

// for basic string functions
#include<string>

// for better setw function for better display
#include <iomanip>

using namespace std;

// structure book for custom data type of book
struct Book 
{
    int book_id;
    int quantity;
    string book_name;
    string author;
};

// global variables
string filename = "booksdata.txt";
const int MAX_BOOKS = 100;
int book_count = 0;
Book books[MAX_BOOKS] = {};

// a function which cuts off if string has more than width length to ensure proper display
string truncateString(const string& str, int width)
{
    if (str.length() > width) 
    {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

// used to display all the books from array
void display_books()
{
    if (book_count == 0) 
    {
        cout << "There are no books to display..." << endl;
    }

    else {
        cout << string(80, '-') << endl;
        cout << left << setw(10)  << "Book ID"
            << setw(30) << "Book Name"
            << setw(25)  << "Author"
            << setw(10)  << "Quantity" << endl;
        cout << string(80, '-') << endl;

        for (int i = 0; i < book_count; i++) 
        {
            cout << left << setw(10)  << books[i].book_id
                << setw(25) << truncateString(books[i].book_name, 24)
                << setw(25) << truncateString(books[i].author, 24)
                << setw(10)  << books[i].quantity << endl;
        }
    }
}

// used to read data from file at start of code and store in array
void read_books_from_file() 
{
    ifstream file(filename);
    if (!file) 
    {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line) && book_count < MAX_BOOKS) 
    {
        stringstream ss(line);
        Book newBook;

        ss >> newBook.book_id;
        ss.ignore();
        getline(ss, newBook.book_name, ',');
        getline(ss, newBook.author, ',');
        ss >> newBook.quantity;

        books[book_count] = newBook;
        book_count++;
    }
    file.close();
}

// function to add data to file
void add_book_to_file(string data)
{
    ofstream file(filename, ios::app);
    
    if (file.is_open()) 
    {
        file << data << endl;
        file.close();
    } 
    else 
    {
        cout << "Error: Unable to open the file " << filename << endl;
    }
}

// function to add data in array at run time, also (add_to_file is called inside it)
void add_book()
{
    string book_data = "";
    books[book_count].book_id = book_count + 1;

    cout << "Enter the title of book: ";
    getline(cin, books[book_count].book_name);

    cout << "Enter the author of book: ";
    getline(cin, books[book_count].author);

    cout << "Enter the quantity of book: ";
    cin >> books[book_count].quantity;
    cin.ignore();
    book_data += to_string(books[book_count].book_id);
    book_data += ",";
    book_data += books[book_count].book_name;
    book_data += ",";
    book_data += books[book_count].author;
    book_data += ",";
    book_data += to_string(books[book_count].quantity);
    
    add_book_to_file(book_data);

    book_count++;
}

// used to search a book by 2 options
// 1. Book Id
// 2. Book Title
void search_book() 
{
    int choice;
    int found_index = -1;
    cout << "Do you want to search by Id or Title?\n"
         << "1. By Book Id\n"
         << "2. By Book Title\n"
         << "Your choice: ";
    cin >> choice;

    switch (choice) 
    {
    case 1: {
        bool id_found = false;
        int id_to_search;

        cout << "Enter the Book Id to search: ";
        cin >> id_to_search;
        for (int i = 0; i < book_count; i++) 
        {
            if (books[i].book_id == id_to_search) 
            {
                id_found = true;
                found_index = i;
                break;
            }
        }
        if (id_found) 
        {
            cout << string(80, '-') << endl;
            cout << left << setw(10) << "Book ID"
                 << setw(30) << "Book Name"
                 << setw(25) << "Author"
                 << setw(10) << "Quantity" << endl;
            cout << string(80, '-') << endl;

            cout << left << setw(10) << books[found_index].book_id
                 << setw(30) << truncateString(books[found_index].book_name, 29)
                 << setw(25) << truncateString(books[found_index].author, 24)
                 << setw(10) << books[found_index].quantity << endl;
        } 
        else 
        {
            cout << "No book was found with the given Id." << endl;
        }
        break;
    }
    case 2: 
    {
        bool title_found = false;
        string title_to_search;

        cin.ignore();
        cout << "Enter the Book Title to search: ";
        getline(cin, title_to_search);

        for (int i = 0; i < book_count; i++) 
        {
            if (books[i].book_name == title_to_search) 
            {
                title_found = true;
                found_index = i;
                break;
            }
        }
        if (title_found) 
        {
            cout << string(80, '-') << endl;
            cout << left << setw(10) << "Book ID"
                 << setw(30) << "Book Name"
                 << setw(25) << "Author"
                 << setw(10) << "Quantity" << endl;
            cout << string(80, '-') << endl;

            cout << left << setw(10) << books[found_index].book_id
                 << setw(30) << truncateString(books[found_index].book_name, 29)
                 << setw(25) << truncateString(books[found_index].author, 24)
                 << setw(10) << books[found_index].quantity << endl;
        } 
        else 
        {
            cout << "No book was found with the given title." << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice." << endl;
        break;
    }
}


// main function
int main() 
{

    int choice;

    read_books_from_file();

    while (true) 
    {
        cout << "\nBook Management System\n";
        cout << "1. Display Books\n";
        cout << "2. Add a New Book\n";
        cout << "3. Search a book\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                display_books();
                break;
            case 2:
                add_book();
                break;
            case 3:
                search_book();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                
        }

    }
    

    return 0;
}
