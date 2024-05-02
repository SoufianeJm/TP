#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

class Article {
public:
    Article(int Id, double price, int qte_stock)
            : Id(Id), price(price), qte_stock(qte_stock) {}

    int getId() const { return Id; }
    double getPrice() const { return price; }
    int getqte_stock() const { return qte_stock; }

    void setqte_stock(int quantity) { qte_stock = quantity; }

private:
    int Id;
    double price;
    int qte_stock;
};

class Panier {
public:
    void addItem(const Article& article, int quantity) {
        items.push_back(std::make_pair(article, quantity));
    }

    void removeItem(int articleId) {
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [articleId](const std::pair<Article, int>& item) {
                                       return item.first.getId() == articleId;
                                   }), items.end());
    }

    void modifyQuantity(int articleId, int newQuantity) {
        for (auto& item : items) {
            if (item.first.getId() == articleId) {
                item.second = newQuantity;
                break;
            }
        }
    }

    void clear() {
        items.clear();
    }

    const std::vector<std::pair<Article, int>>& getItems() const {
        return items;
    }

private:
    std::vector<std::pair<Article, int>> items;
};

class Client {
public:
    Client(const std::string& name, const std::string& email)
            : name_(name), email_(email) {}

    const std::string& name() const { return name_; }
    const std::string& email() const { return email_; }

private:
    std::string name_;
    std::string email_;
};

class Commande : public Client {
public:
    Commande(const std::string& name, const std::string& email)
            : Client(name, email), cart_() {}

    Panier& cart() { return cart_; }

private:
    Panier cart_;
};

// Function to calculate the total order amount with discounts
double calculateTotal(const Panier& cart) {
    double total = 0;
    for (const auto& item : cart.getItems()) {
        const Article& article = item.first;
        int quantity = item.second;
        double price = article.getPrice();
        // Apply discount if quantity exceeds 10 units
        if (quantity > 10) {
            price *= 0.8; // 20% discount
        }
        total += price * quantity;
    }
    return total;
}

// Function to display the contents of the shopping cart
void displayCart(const Panier& cart) {
    std::cout << "  ID   QTE   PRICE      NAME\n";
    std::cout << "-------------------------------\n";
    for (const auto& item : cart.getItems()) {
        const Article& article = item.first;
        int quantity = item.second;
        std::cout << std::setw(4) << article.getId() << std::setw(6) << quantity << std::setw(9) << article.getPrice() << "$"
                  << std::setw(10) << "Article Name" << "\n";
    }
    std::cout << "-------------------------------\n";
}

// Main function
int main() {
    std::string name, email;
    std::cout << "Bonjour to Emsi store!" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your email: ";
    std::getline(std::cin, email);

    Commande order(name, email);

    char choice;
    do {
        std::cout << "Voici votre panier virtuel:\n";
        displayCart(order.cart());
        std::cout << "[A] Ajouter un article\n"
                     "[B] Supprimer un article\n"
                     "[C] Modifier quantite\n"
                     "[D] Afficher tous les articles en ordre croissant\n"
                     "[E] Montant total du commande avec remises\n"
                     "[F] Article plus cher du panier\n"
                     "[G] Articles compris entre prix (min - max)\n"
                     "[H] Article commandé (details)\n"
                     "[I] Vider panier\n"
                     "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore the newline character
        // Perform actions based on choice
        switch (choice) {
            case 'A':
                // Add item to cart
                // Implement this functionality
                break;
            case 'B':
                // Remove item from cart
                // Implement this functionality
                break;
            case 'C':
                // Modify quantity of item in cart
                // Implement this functionality
                break;
            case 'D':
                // Display all items in ascending order by price
                // Implement this functionality
                break;
            case 'E':
                // Display total order amount with discounts
                std::cout << "Total order amount with discounts: $" << calculateTotal(order.cart()) << std::endl;
                break;
            case 'F':
                // Display the most expensive item in the cart
                // Implement this functionality
                break;
            case 'G':
                // Display items priced between a given min and max value
                // Implement this functionality
                break;
            case 'H':
                // Display information on an item ordered
                // Implement this functionality
                break;
            case 'I':
                // Empty the cart
                order.cart().clear();
                std::cout << "Cart emptied.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 'Q'); // Loop until 'Q' is entered to quit

    return 0;
}
