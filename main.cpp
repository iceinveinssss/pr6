#include <iostream>
#include <list>
#include <cmath>
#include <string>

struct Apartment {
    int rooms;
    double area;
    int floor;
    std::string district;

    bool matches(const Apartment& other) const {
        return rooms == other.rooms && floor == other.floor && std::abs(area - other.area) <= 0.1 * area;
    }
};

struct ExchangeRequest {
    Apartment wanted;
    Apartment offered;
};

class ExchangeRegistry {
private:
    std::list<ExchangeRequest> requests;

public:
    void addRequest(const ExchangeRequest& request) {
        requests.push_back(request);
    }

    bool findMatch(const ExchangeRequest& newRequest) {
        for (auto it = requests.begin(); it != requests.end(); ++it) {
            if (it->wanted.matches(newRequest.offered) && newRequest.wanted.matches(it->offered)) {
                std::cout << "������ ���������� ������� ������:\n";
                std::cout << "������� ��������: ������: " << it->wanted.rooms << ", �������: " << it->wanted.area
                    << ", ����: " << it->wanted.floor << ", �����: " << it->wanted.district << '\n';
                std::cout << "������������ ��������: ������: " << it->offered.rooms << ", �������: " << it->offered.area
                    << ", ����: " << it->offered.floor << ", �����: " << it->offered.district << '\n';
                requests.erase(it);
                return true;
            }
        }
        return false;
    }

    void printAllRequests() const {
        for (const auto& request : requests) {
            std::cout << "������� ��������: ������: " << request.wanted.rooms << ", �������: " << request.wanted.area
                << ", ����: " << request.wanted.floor << ", �����: " << request.wanted.district << '\n';
            std::cout << "������������ ��������: ������: " << request.offered.rooms << ", �������: " << request.offered.area
                << ", ����: " << request.offered.floor << ", �����: " << request.offered.district << '\n';
            std::cout << "----------------------------------\n";
        }
    }
};

void printMenu() {
    std::cout << "����:\n";
    std::cout << "1. ���� ������ �� �����\n";
    std::cout << "2. ����� ����������� �������� ������\n";
    std::cout << "3. ����� ���� ���������\n";
    std::cout << "4. �����\n";
    std::cout << "�������� �����: ";
}

Apartment inputApartment(const std::string& type) {
    Apartment apartment;
    std::cout << "������� ������ ��� " << type << " ��������:\n";
    std::cout << "���������� ������: ";
    std::cin >> apartment.rooms;
    std::cout << "�������: ";
    std::cin >> apartment.area;
    std::cout << "����: ";
    std::cin >> apartment.floor;
    std::cin.ignore();  // ������������ ���������� ������ ����� ������
    std::cout << "�����: ";
    std::getline(std::cin, apartment.district);
    return apartment;
}

int main() 
{
    setlocale(0, "rus");
    ExchangeRegistry registry;
    int choice;

    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();  // ������������ ���������� ������ ����� ������

        if (choice == 1) {
            ExchangeRequest request;
            request.wanted = inputApartment("�������");
            request.offered = inputApartment("������������");
            registry.addRequest(request);
        }
        else if (choice == 2) {
            ExchangeRequest newRequest;
            newRequest.wanted = inputApartment("�������");
            newRequest.offered = inputApartment("������������");

            if (!registry.findMatch(newRequest)) {
                registry.addRequest(newRequest);
                std::cout << "���������� ��������� �� �������. ������ ��������� � ���������.\n";
            }
        }
        else if (choice == 3) {
            registry.printAllRequests();
        }
    } while (choice != 4);

    return 0;
}
