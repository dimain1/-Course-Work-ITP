#pragma once
#ifndef TRADEAPPLICATION_H
#define TRADEAPPLICATION_H

#include"SaleApplication.h"
#include"BuyApplication.h"

class TradeApplication : public Project::Application {
public:
	SaleApplication have;
	BuyApplication need;
    TradeApplication() {
        client = Client();
        have = SaleApplication();
        need = BuyApplication();
    }
	TradeApplication(Client cl, SaleApplication SA, BuyApplication BA) {
		client = cl;
		have = SA;
		need = BA;
	}
    void saveToFile(const std::string& filename) const {
        std::ifstream inFile(filename, std::ios::binary);
        size_t numObjects = 0;

        if (inFile.is_open()) {
            inFile.read(reinterpret_cast<char*>(&numObjects), sizeof(numObjects));
            inFile.close();
        }

        numObjects++;

        std::ofstream outFile(filename, std::ios::binary | std::ios::in | std::ios::out);
        if (!outFile.is_open()) {
            outFile.open(filename, std::ios::binary | std::ios::trunc);
            outFile.write(reinterpret_cast<const char*>(&numObjects), sizeof(numObjects));
        }
        else {
            outFile.seekp(0);
            outFile.write(reinterpret_cast<const char*>(&numObjects), sizeof(numObjects));
            outFile.seekp(0, std::ios::end);
        }

        have.saveToFile(outFile);
        need.saveToFile(outFile);
        client.saveToFile(outFile);

        outFile.close();
        std::cout << "������ ������� ���������." << std::endl << std::endl;
    }
    void loadFromFile(std::ifstream& inFile) {
        have.loadFromFile(inFile);
        need.loadFromFile(inFile);
        client.loadFromFile(inFile);
    }
    void ViewApplications(int i) {
        std::string result = "          �����                            \n";
        result += to_string(i) + ") " + to_string(have.property.numRooms) + "-���������. " + to_string(have.property.area) + " �^2." + " �������� - " + ((have.property.amenities) ? "����" : "���") + "\n";
        result += "������������: ������ - " + have.property.address.country + "  �." + have.property.address.city + "  �-� " + have.property.address.district + "\n";
        result += "��������: " + have.client.secondName + " " + have.client.name + " ���� " + to_string(have.property.price) + "�.";
        cout << result << endl << endl;
        result = "";
        result += "             ��                            \n";
        result += to_string(i) + ") " + to_string(need.property.numRooms) + "-����������. " + to_string(need.property.minPrice) + "-" + to_string(need.property.maxPrice) + "�. �������� - " + ((need.property.amenities) ? "����" : "���") + "\n";
        result += "������������: ������ - " + need.property.address.country + "  �." + need.property.address.city + "  �-� " + need.property.address.district + "\n";
        cout << result << endl << endl;
    }
};
ostream& operator << (ostream& os, TradeApplication tradeApp) {
    std::string result = "          �����                            \n";
    result += to_string(tradeApp.have.property.numRooms) + "-���������. " + to_string(tradeApp.have.property.area) + " �^2." + " �������� - " + ((tradeApp.have.property.amenities) ? "����" : "���") + "\n";
    result += "������������: ������ - " + tradeApp.have.property.address.country + "  �." + tradeApp.have.property.address.city + "  �-� " + tradeApp.have.property.address.district + "\n";
    result += "��������: " + tradeApp.have.client.secondName + " " + tradeApp.have.client.name + " ���� " + to_string(tradeApp.have.property.price) + "�.";
    cout << result << endl << endl;
    result = "";
    result += "             ��                            \n";
    result += to_string(tradeApp.need.property.numRooms) + "-����������. " + to_string(tradeApp.need.property.minPrice) + "-" + to_string(tradeApp.need.property.maxPrice) + "�. �������� - " + ((tradeApp.need.property.amenities) ? "����" : "���") + "\n";
    result += "������������: ������ - " + tradeApp.need.property.address.country + "  �." + tradeApp.need.property.address.city + "  �-� " + tradeApp.need.property.address.district + "\n";
    cout << result << endl << endl;

    return os;
}

#endif