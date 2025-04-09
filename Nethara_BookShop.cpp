#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int MAX_BOOKS = 10;
const int MAX_ORDERS = 10;

struct Book {
    std::string title;
    std::string author;
    double price;
};

struct Order {
    Book book;
    int quantity;
};

struct User {
    std::string username;
    bool isLoggedIn;
};

// Function prototypes
bool login(User& currentUser);
void logout(User& currentUser);
void manageBooks(Book books[], int& bookCount);
void manageOrders(Order orders[], const Book books[], int& orderCount, int bookCount);
void readBooksFromFile(Book books[], int& bookCount);
void writeBooksToFile(const Book books[], int bookCount);
void readOrdersFromFile(Order orders[], int& orderCount);
void writeOrdersToFile(const Order orders[], int orderCount);
void displayBooks(const Book books[], int bookCount);
void addBook(Book books[], int& bookCount);
void searchBook(const Book books[], int bookCount);
void displayOrders(const Order orders[], int orderCount);
void addDiscount(Order orders[], int orderCount);
void placeOrder(Order orders[], const Book books[], int& orderCount, int bookCount);
void prepareQuotation(const Order orders[], int orderCount);

// Implementation of functions
bool login(User& currentUser) {
    std::string username;
    std::cout << "Enter your name: ";
    std::cin.ignore();
    std::getline(std::cin, username);

    if (!username.empty()) {
        currentUser.username = username;
        currentUser.isLoggedIn = true;
        std::cout << "Logged in successfully, " << currentUser.username << "!\n";
        return true;
    }
    else {
        std::cerr << "Error: Invalid name.\n";
        return false;
    }
}

void logout(User& currentUser) {
    currentUser.isLoggedIn = false;
    std::cout << "Logged out successfully.\n";
}

void manageBooks(Book books[], int& bookCount) {
    int choice;
    do {
        std::cout << "\nManage Books:\n";
        std::cout << "1. Display Books\n";
        std::cout << "2. Add Book\n";
        std::cout << "3. Search Book\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayBooks(books, bookCount);
            break;
        case 2:
            addBook(books, bookCount);
            break;
        case 3:
            searchBook(books, bookCount);
            break;
        case 4:
            std::cout << "Returning to Main Menu.\n";
            break;
        default:
            std::cerr << "Error: Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void manageOrders(Order orders[], const Book books[], int& orderCount, int bookCount) {
    int choice;
    do {
        std::cout << "\nManage Orders:\n";
        std::cout << "1. Place Order\n";
        std::cout << "2. Display Orders\n";
        std::cout << "3. Add Discount\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            placeOrder(orders, books, orderCount, bookCount);
            break;
        case 2:
            displayOrders(orders, orderCount);
            break;
        case 3:
            addDiscount(orders, orderCount);
            break;
        case 4:
            std::cout << "Returning to Main Menu.\n";
            break;
        default:
            std::cerr << "Error: Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void readBooksFromFile(Book books[], int& bookCount) {
    std::ifstream inFile("books.txt");
    if (inFile.is_open()) {
        while (bookCount < MAX_BOOKS && inFile >> books[bookCount].title >> books[bookCount].author >> books[bookCount].price) {
            bookCount++;
        }
        inFile.close();
    }
}

void writeBooksToFile(const Book books[], int bookCount) {
    std::ofstream outFile("books.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < bookCount; ++i) {
            outFile << books[i].title << " " << books[i].author << " " << books[i].price << "\n";
        }
        outFile.close();
    }
}

void readOrdersFromFile(Order orders[], int& orderCount) {
    std::ifstream inFile("orders.txt");
    if (inFile.is_open()) {
        while (orderCount < MAX_ORDERS && inFile >> orders[orderCount].book.title >> orders[orderCount].book.author >> orders[orderCount].book.price >> orders[orderCount].quantity) {
            orderCount++;
        }
        inFile.close();
    }
}

void writeOrdersToFile(const Order orders[], int orderCount) {
    std::ofstream outFile("orders.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < orderCount; ++i) {
            outFile << orders[i].book.title << " " << orders[i].book.author << " " << orders[i].book.price << " " << orders[i].quantity << "\n";
        }
        outFile.close();
    }
}

void displayBooks(const Book books[], int bookCount) {
    std::cout << "Available Books:\n";
    for (int i = 0; i < bookCount; ++i) {
        std::cout << "Title: " << books[i].title << ", Author: " << books[i].author << ", Price: $" << books[i].price << "\n";
    }
}

void addBook(Book books[], int& bookCount) {
    if (bookCount < MAX_BOOKS) {
        std::cout << "Enter new book details:\n";
        std::cin.ignore();
        std::cout << "Title: ";
        std::getline(std::cin, books[bookCount].title);

        std::cout << "Author: ";
        std::getline(std::cin, books[bookCount].author);

        std::cout << "Price: $";
        std::cin >> books[bookCount].price;

        std::cout << "Book added successfully!\n";
        bookCount++;

        // Write updated books data to file
        writeBooksToFile(books, bookCount);
    }
    else {
        std::cerr << "Error: Maximum books reached.\n";
    }
}

void searchBook(const Book books[], int bookCount) {
    std::string title;
    std::cout << "Enter book title to search: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    bool found = false;
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].title == title) {
            std::cout << "Book found:\n";
            std::cout << "Title: " << books[i].title << ", Author: " << books[i].author << ", Price: $" << books[i].price << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cerr << "Error: Book not found.\n";
    }
}

void displayOrders(const Order orders[], int orderCount) {
    std::cout << "Placed Orders:\n";
    for (int i = 0; i < orderCount; ++i) {
        std::cout << "Book: " << orders[i].book.title << ", Quantity: " << orders[i].quantity
            << ", Total: $" << orders[i].quantity * orders[i].book.price << "\n";
    }
}

void addDiscount(Order orders[], int orderCount) {
    std::string title;
    std::cout << "Enter book title to add discount: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    int orderIndex = -1;
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i].book.title == title) {
            orderIndex = i;
            break;
        }
    }

    if (orderIndex == -1) {
        std::cerr << "Error: Order not found.\n";
    }
    else {
        double discount;
        std::cout << "Enter discount percentage: ";
        std::cin >> discount;

        // Calculate discounted price
        double discountedPrice = orders[orderIndex].book.price * (1 - discount / 100);

        // Update book price in the order
        orders[orderIndex].book.price = discountedPrice;

        std::cout << "Discount added successfully!\n";

        // Write updated orders data to file
        writeOrdersToFile(orders, orderCount);
    }
}

void placeOrder(Order orders[], const Book books[], int& orderCount, int bookCount) {
    std::string title;
    int quantity;

    std::cout << "Enter book title: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    // Convert the entered title and book titles to lowercase for case-insensitive comparison
    std::transform(title.begin(), title.end(), title.begin(), ::tolower);

    int bookIndex = -1;
    for (int i = 0; i < bookCount; ++i) {
        std::string lowercaseBookTitle = books[i].title;
        std::transform(lowercaseBookTitle.begin(), lowercaseBookTitle.end(), lowercaseBookTitle.begin(), ::tolower);

        if (lowercaseBookTitle == title) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        std::cerr << "Error: Book not found.\n";
    }
    else {
        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        if (orderCount < MAX_ORDERS) {
            orders[orderCount].book = books[bookIndex];
            orders[orderCount].quantity = quantity;
            orderCount++;

            std::cout << "Order placed successfully!\n";

            // Write updated orders data to file
            writeOrdersToFile(orders, orderCount);
        }
        else {
            std::cerr << "Error: Maximum orders reached.\n";
        }
    }
}

void prepareQuotation(const Order orders[], int orderCount) {
    std::cout << "Quotations with Discount:\n";
    for (int i = 0; i < orderCount; ++i) {
        std::cout << "Book: " << orders[i].book.title << ", Quantity: " << orders[i].quantity
            << ", Total: $" << orders[i].quantity * orders[i].book.price << "\n";
    }
}

int main() {
    User currentUser;
    currentUser.isLoggedIn = false;

    // Logging in
    while (!currentUser.isLoggedIn) {
        login(currentUser);
    }

    Book books[MAX_BOOKS] = {
        {"Book1", "Author1", 2.0},
        {"Book2", "Author2", 4.0},
        {"Book3", "Author3", 5.0}
    };
    int bookCount = 3;

    Order orders[MAX_ORDERS];
    int orderCount = 0;

    // Read books and orders data from files
    readBooksFromFile(books, bookCount);
    readOrdersFromFile(orders, orderCount);

    int choice;
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Manage Books\n";
        std::cout << "2. Manage Orders\n";
        std::cout << "3. Print Quotations with Discount\n";
        std::cout << "4. Logout\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manageBooks(books, bookCount);
            break;
        case 2:
            manageOrders(orders, books, orderCount, bookCount);
            break;
        case 3:
            prepareQuotation(orders, orderCount);
            break;
        case 4:
            logout(currentUser);
            break;
        case 5:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cerr << "Error: Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}