#include <iostream>
#include <string>
#include "SaleApplication.h"
#include "BuyApplication.h"
#include "TradeApplication.h"
#include"Windows.h"
#include"Requirements.h"

using namespace std;

void SwitchUser(Client& client) {
    std::string name, secondName;
    std::cout << "Введите имя пользователя: ";
    std::cin >> name;
    std::cout << "Введите фамилию пользователя: ";
    std::cin >> secondName;
    client = Client(name, secondName);
    std::cout << "Пользователь успешно сменён." << std::endl;
}

void createSaleApplication( Client& client) {
    SaleApplication saleApp = SaleApplication();
    std::string country, city, district ,amen;
    int area, numRooms, price;
    bool amenities;
    std::getline(std::cin, district);
    std::cout << "Введите страну: ";
    std::getline(std::cin, country);
    std::cout << "Введите город: ";
    std::getline(std::cin, city);
    std::cout << "Введите район: ";
    std::getline(std::cin, district);
    std::cout << "Введите площадь помещения: ";
    std::cin >> area;
    std::cout << "Введите количество комнат: ";
    std::cin >> numRooms;
    std::cout << "Введите цену: ";
    std::cin >> price;
    std::cout << "Наличие удобств(Да,Нет) ?: ";
    std::cin >> amen;
    if (amen == "Да" || amen == "да" || amen == "дА" || amen == "ДА") {
        amenities = true;
    }
    else {
        amenities = false;
    }
    saleApp.client = client;
    saleApp.property = SaleProperty(Address(country, city, district) , area, numRooms, price, amenities);
    saleApp.saveToFile("sale.bin");
}
bool CheckOnSale(SaleApplication& saleApp, SaleRequirements& saleReq) 
{
    if ((saleApp.property.address.country == saleReq.SaleCountry) || (saleReq.SaleCountry == "-")) 
    {
        if ((saleApp.property.address.city == saleReq.SaleCity) || (saleReq.SaleCity == "-")) 
        {
            if ((saleApp.property.address.district == saleReq.SaleDistrict) || (saleReq.SaleDistrict == "-")) 
            {
                if (saleApp.property.amenities == saleReq.SaleAmenities) 
                {
                    if ((saleReq.saleMinArea <= saleApp.property.area) && (saleReq.saleMaxArea >= saleApp.property.area)) 
                    {
                        if ((saleReq.saleMinPrice <= saleApp.property.price) && (saleReq.saleMaxPrice >= saleApp.property.price)) 
                        {
                            if (saleReq.saleNumRooms == saleApp.property.numRooms){
                                return true;
                            }
                            else {
                                return false;
                            }
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
void GetSaleRequirements(SaleRequirements& saleReq) {
    string amen;
    std::getline(std::cin, saleReq.SaleDistrict);
    std::cout << "Введите страну: ";
    std::getline(std::cin, saleReq.SaleCountry);
    std::cout << "Введите город: ";
    std::getline(std::cin, saleReq.SaleCity);
    std::cout << "Введите район: ";
    std::getline(std::cin, saleReq.SaleDistrict);
    std::cout << "Введите количество комнат: ";
    std::cin >> saleReq.saleNumRooms;
    std::cout << "Введите минимальную площадь: ";
    std::cin >> saleReq.saleMinArea;
    std::cout << "Введите максимальную площадь: ";
    std::cin >> saleReq.saleMaxArea;
    std::cout << "Введите минимальную цену: ";
    std::cin >> saleReq.saleMinPrice;
    std::cout << "Введите максимальную цену: ";
    std::cin >> saleReq.saleMaxPrice;
    std::cout << "Наличие удобств(Да,Нет) ?: ";
    std::cin >> amen;
    if (amen == "Да" || amen == "да" || amen == "дА" || amen == "ДА") {
        saleReq.SaleAmenities = true;
    }
    else {
        saleReq.SaleAmenities = false;
    }
    cout << endl;
}

void createBuyApplication(Client& client) {
    BuyApplication buyApp = BuyApplication();
    std::string country, city, district, amen;
    int numRooms, minPrice,maxPrice;
    bool amenities;
    std::getline(std::cin, district);
    std::cout << "Введите страну: ";
    std::getline(std::cin, country);
    std::cout << "Введите город: ";
    std::getline(std::cin, city);
    std::cout << "Введите район: ";
    std::getline(std::cin, district);
    std::cout << "Введите количество комнат: ";
    std::cin >> numRooms;
    std::cout << "Введите минимальную цену: ";
    std::cin >> minPrice;
    std::cout << "Введите максимальную цену: ";
    std::cin >> maxPrice;
    std::cout << "Наличие удобств(Да,Нет) ?: ";
    std::cin >> amen;
    if (amen == "Да" || amen == "да" || amen == "дА" || amen == "ДА") {
        amenities = true;
    }
    else {
        amenities = false;
    }
    buyApp.client = client;
    buyApp.property = BuyProperty(Address(country, city, district), numRooms, amenities,minPrice, maxPrice);


    buyApp.saveToFile("buy.bin");
}
bool CheckOnBuy(BuyApplication& buyApp, BuyRequirements& buyReq) {

if ((buyApp.property.address.country == buyReq.buyCountry) || (buyReq.buyCountry == "-")) {
    if ((buyApp.property.address.city == buyReq.buyCity) || (buyReq.buyCity == "-")) {
        if ((buyApp.property.address.district == buyReq.buyDistrict) || (buyReq.buyDistrict == "-")) {
            if (buyApp.property.amenities == buyReq.buyAmenities) {
                if (buyApp.property.numRooms == buyReq.buyNumRooms) {
                    if ((buyApp.property.minPrice <= buyReq.buyPrice) && (buyApp.property.maxPrice >= buyReq.buyPrice)) {
                        return true;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
else
    return false;
}
void GetBuyRequirements(BuyRequirements& buyReq) {
    string amen;
    bool ameníties;
    std::getline(std::cin, buyReq.buyDistrict);
    std::cout << "Введите страну: ";
    std::getline(std::cin, buyReq.buyCountry);
    std::cout << "Введите город: ";
    std::getline(std::cin, buyReq.buyCity);
    std::cout << "Введите район: ";
    std::getline(std::cin, buyReq.buyDistrict);
    std::cout << "Введите количество комнат: ";
    std::cin >> buyReq.buyNumRooms;
    std::cout << "Введите цену: ";
    std::cin >> buyReq.buyPrice;
    std::cout << "Наличие удобств(Да,Нет) ?: ";
    std::cin >> amen;
    if (amen == "Да" || amen == "да" || amen == "дА" || amen == "ДА") {
        buyReq.buyAmenities = true;
    }
    else {
        buyReq.buyAmenities = false;
    }
    cout << endl;
}


void createTradeApplication(Client& client) {
    TradeApplication tradeApp = TradeApplication();
    std::string country, city, district, amen;
    int area, numRooms, minPrice, maxPrice, price;
    bool amenities;
    cout << " Предлагаете  " << endl;
    std::getline(std::cin, district);
    std::cout << "Введите страну: ";
    std::getline(std::cin, country);
    std::cout << "Введите город: ";
    std::getline(std::cin, city);
    std::cout << "Введите район: ";
    std::getline(std::cin, district);
    std::cout << "Введите площадь помещения: ";
    std::cin >> area;
    std::cout << "Введите количество комнат: ";
    std::cin >> numRooms;
    std::cout << "Введите цену: ";
    std::cin >> price;
    std::cout << "Наличие удобств(Да,Нет) ?: ";
    std::cin >> amen;
    if (amen == "Да" || amen == "да" || amen == "дА" || amen == "ДА") {
        amenities = true;
    }
    else {
        amenities = false;
    }
    tradeApp.client = client;
    tradeApp.have.client = client;
    tradeApp.have.property = SaleProperty(Address(country, city, district), area, numRooms, price, amenities);
    cout << endl << " Желаете " << endl;
    std::getline(std::cin, district);
    std::cout << "Введите страну: ";
    std::getline(std::cin, country);
    std::cout << "Введите город: ";
    std::getline(std::cin, city);
    std::cout << "Введите район: ";
    std::getline(std::cin, district);
    std::cout << "Введите количество комнат: ";
    std::cin >> numRooms;
    std::cout << "Введите минимальную цену: ";
    std::cin >> minPrice;
    std::cout << "Введите максимальную цену: ";
    std::cin >> maxPrice;
    std::cout << "Наличие удобств(Да,Нет) ?: ";
    std::cin >> amen;
    if (amen == "Да" || amen == "да" || amen == "дА" || amen == "ДА") {
        amenities = true;
    }
    else {
        amenities = false;
    }
    tradeApp.need.client = Client("", "");
    tradeApp.need.property = BuyProperty(Address(country, city, district), numRooms, amenities, minPrice, maxPrice);
    tradeApp.saveToFile("trade.bin");
}
bool CheckOnTrade(TradeApplication& tradeApp, TradeRequirements& tradeReq) {
    if ( (!CheckOnSale(tradeApp.have, tradeReq.offer)) || (!CheckOnBuy(tradeApp.need, tradeReq.feature))) {
        return false;
    }
    return true;
}
void GetTradeRequirements(TradeRequirements& tradeReq) {
    cout << "   Желаешь  " << endl;
    GetBuyRequirements(tradeReq.feature);
    cout << " Предлагаешь  " << endl;
    GetSaleRequirements(tradeReq.offer);
    cout << endl;
}

void viewSaleApplications(bool checker) {
    SaleRequirements saleReq;
    SaleApplication saleApp = SaleApplication();
    std::ifstream inFile("sale.bin", std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Недоступный для открытия файл: " << "sale.bin" << std::endl;
        return;
    }
    if (checker) {
        GetSaleRequirements(saleReq);
    }
    size_t numObjects = 0;
    inFile.read(reinterpret_cast<char*>(&numObjects), sizeof(numObjects));
    for (int i = 1; i <= numObjects; i++) {
        saleApp.loadFromFile(inFile);
        if (checker) {
            if (!CheckOnSale(saleApp, saleReq)) {
                continue;
            }
        }
        /*saleApp.viewApplications(i);*/
        cout << saleApp;
    }
    inFile.close();
}
void viewBuyApplications(bool checker) {
    BuyApplication buyApp;
    BuyRequirements buyReq;
    std::ifstream inFile("buy.bin", std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Недоступный для открытия файл: " << "buy.bin" << std::endl;
        return;
    }
    if (checker) {
        GetBuyRequirements(buyReq);
    }
    size_t numObjects = 0;
    inFile.read(reinterpret_cast<char*>(&numObjects), sizeof(numObjects));
    for (int i = 1; i <= numObjects; i++) {
        buyApp.loadFromFile(inFile);
        if (checker) {
            if (!CheckOnBuy(buyApp, buyReq)) {
                continue;
            }
        }
        /*buyApp.viewApplications(i);*/
        cout << buyApp;
    }
    inFile.close();
}
void viewTradeApplications(bool checker) {
    TradeApplication tradeApp;
    TradeRequirements tradeReq;
    std::ifstream inFile("trade.bin", std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Недоступный для открытия файл: " << "trade.bin" << std::endl;
        return;
    }
    if (checker) {
        GetTradeRequirements(tradeReq);
    }
    size_t numObjects = 0;
    inFile.read(reinterpret_cast<char*>(&numObjects), sizeof(numObjects));
    for (int i = 1; i <= numObjects; i++) {
        tradeApp.loadFromFile(inFile);
        if (checker) {
            if (!CheckOnTrade(tradeApp, tradeReq)) {
                continue;
            }
        }
        /*tradeApp.ViewApplications(i);*/
        cout << tradeApp;
    }
    inFile.close();
}

int Menu() {
    bool flag;
    Client client;
    cout << "    Авторизация    " << endl;
    cout << "Введите имя пользователя: ";
    std::getline(std::cin, client.name);
    cout << "Введите фамилию пользователя: ";
    std::getline(std::cin, client.secondName);
    while (true) {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Сменить пользователя" << std::endl;
        std::cout << "2. Создать заявление на продажу" << std::endl;
        std::cout << "3. Создать заявление на покупку" << std::endl;
        std::cout << "4. Создать заявление на обмен" << std::endl;
        std::cout << "5. Посмотреть заявления" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << "Выберите опцию: ";

        int option;
        std::cin >> option;
        cout << endl;

        switch (option) {
        case 1:
            SwitchUser(client);
            break;
        case 2:
            createSaleApplication( client);
            break;
        case 3:
            createBuyApplication( client);
            break;
        case 4:
            createTradeApplication( client);
            break;
        case 5:
            flag = false;
            while (true) {
                if (flag) {
                    break;
                }
                int option2;
                std::cout << "1. Посмотреть заявление на продажу" << std::endl;
                std::cout << "2. Посмотреть заявление на продажу соответствующих требованиям" << std::endl;
                std::cout << "3. Посмотреть заявление на покупку" << std::endl;
                std::cout << "4. Посмотреть заявление на покупку соответствующих требованиям" << std::endl;
                std::cout << "5. Посмотреть заявления на обмен" << std::endl;
                std::cout << "6. Посмотреть заявления на обмен соответствующих требованиям" << std::endl;
                std::cout << "7. Назад" << std::endl;
                std::cout << "Выберите опцию: ";
                 std::cin >> option2;
                cout << endl;

                switch (option2)
                {
                case 1:

                    viewSaleApplications(false);
                    break;
                case 2:
                    cout << endl;
                    cout << "    Требования к заявлению    " << endl;
                    viewSaleApplications(true);
                    break;
                case 3:
                    viewBuyApplications(false);
                    break;
                case 4:
                    cout << endl;
                    cout << "    Требования к заявлению    " << endl;
                    viewBuyApplications(true);
                    break;
                case 5:
                    viewTradeApplications(false);
                    break;
                case 6:
                    cout << endl;
                    cout << "    Требования к заявлению    " << endl;
                    viewTradeApplications(true);
                    break;
                case 7:
                    flag = true;
                    break;
                default:
                    break;
                }
            }
            break;
        case 6:
            std::cout << "Закрытие..." << std::endl;
            return 0;
        default:
            std::cout << "Неправлиьная опция. Пожалуйста попробуйте снова." << std::endl;
        }
    }
    return 0;

}

int main() {
    system("color 70");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Menu();
}
