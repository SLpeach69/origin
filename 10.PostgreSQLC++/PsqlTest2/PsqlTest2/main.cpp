#include <iostream>
#include <pqxx/pqxx>
#include <string>

class ClientManager {
private:
    pqxx::connection& conn;

public:
    ClientManager(pqxx::connection& connection) : conn(connection) {}

    void createTables() {
        pqxx::work txn(conn);
        txn.exec(
            "CREATE TABLE IF NOT EXISTS clients ("
            "id SERIAL PRIMARY KEY,"
            "first_name TEXT NOT NULL,"
            "last_name TEXT NOT NULL,"
            "email TEXT UNIQUE"
            ");"
            "CREATE TABLE IF NOT EXISTS phones ("
            "id SERIAL PRIMARY KEY,"
            "client_id INTEGER REFERENCES clients(id),"
            "phone_number TEXT"
            ");"
        );
        txn.commit();
        std::cout << "Tables created successfully." << std::endl;
    }

    void addClient(const std::string& firstName, const std::string& lastName, const std::string& email) {
        pqxx::work txn(conn);
        txn.exec(
            "INSERT INTO clients (first_name, last_name, email) "
            "VALUES (" + txn.quote(firstName) + ", " + txn.quote(lastName) + ", " + txn.quote(email) + ");"
        );
        txn.commit();
        std::cout << "Client added successfully." << std::endl;
    }

    void addPhone(int clientId, const std::string& phoneNumber) {
        pqxx::work txn(conn);
        txn.exec(
            "INSERT INTO phones (client_id, phone_number) "
            "VALUES (" + txn.quote(clientId) + ", " + txn.quote(phoneNumber) + ");"
        );
        txn.commit();
        std::cout << "Phone added successfully." << std::endl;
    }

    void updateClient(int clientId, const std::string& firstName, const std::string& lastName, const std::string& email) {
        pqxx::work txn(conn);
        txn.exec(
            "UPDATE clients SET "
            "first_name = " + txn.quote(firstName) + ", "
            "last_name = " + txn.quote(lastName) + ", "
            "email = " + txn.quote(email) + " "
            "WHERE id = " + txn.quote(clientId) + ";"
        );
        txn.commit();
        std::cout << "Client updated successfully." << std::endl;
    }

    void deletePhone(int phoneId) {
        pqxx::work txn(conn);
        txn.exec("DELETE FROM phones WHERE id = " + txn.quote(phoneId) + ";");
        txn.commit();
        std::cout << "Phone deleted successfully." << std::endl;
    }

    void deleteClient(int clientId) {
        pqxx::work txn(conn);
        txn.exec("DELETE FROM phones WHERE client_id = " + txn.quote(clientId) + ";");
        txn.exec("DELETE FROM clients WHERE id = " + txn.quote(clientId) + ";");
        txn.commit();
        std::cout << "Client deleted successfully." << std::endl;
    }

    void findClient(const std::string& searchTerm) {
        pqxx::work txn(conn);
        std::string query =
            "SELECT c.id, c.first_name, c.last_name, c.email, p.phone_number "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE c.first_name LIKE " + txn.quote("%" + searchTerm + "%") + " "
            "OR c.last_name LIKE " + txn.quote("%" + searchTerm + "%") + " "
            "OR c.email LIKE " + txn.quote("%" + searchTerm + "%") + " "
            "OR p.phone_number LIKE " + txn.quote("%" + searchTerm + "%") + ";";

        pqxx::result result = txn.exec(query);

        for (const auto& row : result) {
            std::cout << "ID: " << row[0].as<int>()
                << ", Name: " << row[1].as<std::string>() << " " << row[2].as<std::string>()
                << ", Email: " << row[3].as<std::string>()
                << ", Phone: " << (row[4].is_null() ? "N/A" : row[4].as<std::string>()) << std::endl;
        }
    }
};

void printMenu() {
    std::cout << "\nMenu:\n"
        << "1. Add Client\n"
        << "2. Add Phone\n"
        << "3. Update Client\n"
        << "4. Delete Phone\n"
        << "5. Delete Client\n"
        << "6. Find Client\n"
        << "7. Exit\n"
        << "Choose an option: ";
}

int main() {
    try {
        pqxx::connection conn(
            "hostaddr=127.0.0.1 "
            "port=5432 "
            "dbname=test2 "
            "user=postgres "
            "password=SLmimes123 ");
        if (conn.is_open()) {
            std::cout << "Connected to database successfully." << std::endl;
        }
        else {
            std::cerr << "Can't open database." << std::endl;
            return 1;
        }

        ClientManager manager(conn);
        manager.createTables();

        int choice;
        std::string firstName, lastName, email, phoneNumber, searchTerm;
        int clientId, phoneId;

        while (true) {
            printMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1:
                std::cout << "Enter first name: ";
                std::getline(std::cin, firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                manager.addClient(firstName, lastName, email);
                break;

            case 2:
                std::cout << "Enter client ID: ";
                std::cin >> clientId;
                std::cin.ignore();
                std::cout << "Enter phone number: ";
                std::getline(std::cin, phoneNumber);
                manager.addPhone(clientId, phoneNumber);
                break;

            case 3:
                std::cout << "Enter client ID: ";
                std::cin >> clientId;
                std::cin.ignore();
                std::cout << "Enter new first name: ";
                std::getline(std::cin, firstName);
                std::cout << "Enter new last name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter new email: ";
                std::getline(std::cin, email);
                manager.updateClient(clientId, firstName, lastName, email);
                break;

            case 4:
                std::cout << "Enter phone ID: ";
                std::cin >> phoneId;
                manager.deletePhone(phoneId);
                break;

            case 5:
                std::cout << "Enter client ID: ";
                std::cin >> clientId;
                manager.deleteClient(clientId);
                break;

            case 6:
                std::cout << "Enter search term: ";
                std::getline(std::cin, searchTerm);
                manager.findClient(searchTerm);
                break;

            case 7:
                std::cout << "Exiting..." << std::endl;
                return 0;

            default:
                std::cout << "Invalid option. Please try again." << std::endl;
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}