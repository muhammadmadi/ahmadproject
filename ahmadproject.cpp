#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <limits>

const double DOLLAR_TO_SHEKEL = 3.5;
const double DISCOUNT_THRESHOLD = 500.0;
const double TAX_RATE = 0.16;

void printMenu();
double calculateTotal(const std::vector<double>& prices);
double calculateDiscount(double total);
double calculateTax(double total);
void printReceipt(const std::vector<double>& prices, char currency);
double getMax(const std::vector<double>& prices);
double getMin(const std::vector<double>& prices);
void processPayment(double total);

int main() {
    std::map<char, double> pricePerUnit = {{'a', 2.0}, {'b', 4.0}, {'c', 6.0}, {'d', 8.0}, {'e', 10.0}};
    std::vector<double> itemPrices;
    char itemCode;
    int quantity;
    double total, discount, tax;

    while (true) {
        std::cout << "Please enter the item code (a, b, c, d, e) or x to finish: ";
        std::cin >> itemCode;
        if (itemCode == 'x') {
            break;
        }
        if (pricePerUnit.find(itemCode) == pricePerUnit.end()) {
            std::cout << "Invalid item code. Please try again.\n";
            continue;
        }
        std::cout << "Please enter the number of item units: ";
        std::cin >> quantity;
        itemPrices.push_back(pricePerUnit[itemCode] * quantity);
    }

    total = calculateTotal(itemPrices);
    discount = calculateDiscount(total);
    tax = calculateTax(total);

    char option;
    do {
        printMenu();
        std::cin >> option;
        switch (option) {
            case '1':
                printReceipt(itemPrices, 's'); // Receipt in shekel
                break;
            case '2':
                printReceipt(itemPrices, 'd'); // Receipt in dollar
                break;
            case '3':
                std::cout << "Total discount is " << discount << " shekel\n";
                break;
            case '4':
                processPayment(total - discount + tax);
                break;
            case '5':
                std::cout << "The max cost is " << getMax(itemPrices) << " shekel\n";
                std::cout << "The min cost is " << getMin(itemPrices) << " shekel\n";
                break;
            case '6':
                itemPrices.clear();
                std::cout << "Current transaction cancelled.\n";
                break;
            case '7':
                itemPrices.clear();
                std::cout << "Next customer.\n";
                break;
            case '8':
                std::cout << "Exit.\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    } while (option != '8');

    return 0;
}

void printMenu() {
    std::cout << "1- Receipt in shekel\n";
    std::cout << "2- Receipt in dollar\n";
    std::cout << "3- Total discount in shekel\n";
    std::cout << "4- Pay\n";
    std::cout << "5- Find max and min\n";
    std::cout << "6- Cancel current\n";
    std::cout << "7- Next customer\n";
    std::cout << "8- Exit\n";
}

double calculateTotal(const std::vector<double>& prices) {
double sum = 0.0;
for (double price : prices) {
sum += price;
}
return sum;
}

double calculateDiscount(double total) {
if (total > DISCOUNT_THRESHOLD) {
return total * 0.10; // Applying a 10% discount for totals over the threshold
}
return 0.0;
}

double calculateTax(double total) {
return total * TAX_RATE;
}

void printReceipt(const std::vector<double>& prices, char currency) {
double total = calculateTotal(prices);
double discount = calculateDiscount(total);
double tax = calculateTax(total);
double finalTotal = total - discount + tax;
std::cout << "Item costs: ";
for (double price : prices) {
    std::cout << price << " ";
}
std::cout << "\nTotal before discount: " << total << " shekel\n";
std::cout << "Discount: " << discount << " shekel\n";
std::cout << "Tax: " << tax << " shekel\n";
std::cout << "Total after discount and tax: " << finalTotal << " shekel\n";

if (currency == 'd') {
    std::cout << "Total in dollars: " << std::fixed << std::setprecision(2) << finalTotal / DOLLAR_TO_SHEKEL << std::endl;
}
}

double getMax(const std::vector<double>& prices) {
double maxPrice = 0.0;
for (double price : prices) {
if (price > maxPrice) maxPrice = price;
}
return maxPrice;
}

double getMin(const std::vector<double>& prices) {
if (prices.empty()) return 0.0;
double minPrice = prices[0];
for (double price : prices) {
if (price < minPrice) minPrice = price;
}
return minPrice;
}

void processPayment(double total) {
double amountPaid;
std::cout << "Total to pay: " << total << " shekel\n";
std::cout << "Enter amount paid in shekel: ";
std::cin >> amountPaid;
std::cout << "Change: " << amountPaid - total << " shekel\n";
}


