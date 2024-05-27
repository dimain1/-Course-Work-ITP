#pragma once
#ifndef BUYAPPLICATION_H
#define BUYAPPLICATION_H
#include<fstream>
#include"Application.h"
#include"BuyProperty.h"

using namespace std;

class BuyApplication : public Project::Application
{

public:
    BuyProperty property;
    BuyApplication() {
        client = Client();
        property = BuyProperty();
    }
    BuyApplication(Client c, BuyProperty p) {
        client = c;
        property = p;
    }
    void saveToFile(const std::string& filename) const {
        // ��������, ���������� �� ����
        std::ifstream inFile(filename, std::ios::binary);
        size_t numObjects = 0;

        if (inFile.is_open()) {
            inFile.read(reinterpret_cast<char*>(&numObjects), sizeof(numObjects));
            inFile.close();
        }

        numObjects++; // ����������� ���������� ��������

        // ������ ��������� ���� ��� ������ � �������������� ���������� ��������
        std::ofstream outFile(filename, std::ios::binary | std::ios::in | std::ios::out);
        if (!outFile.is_open()) {
            // ���� ���� �� ����������, ������� ��� � ���������� ��������� ���������� ��������
            outFile.open(filename, std::ios::binary | std::ios::trunc);
            outFile.write(reinterpret_cast<const char*>(&numObjects), sizeof(numObjects));
        }
        else {
            // �������������� ���������� ��������
            outFile.seekp(0);
            outFile.write(reinterpret_cast<const char*>(&numObjects), sizeof(numObjects));
            outFile.seekp(0, std::ios::end);
        }

        // ���������� ������ ���������� ������ SaleApplication � ����
        property.saveToFile(outFile);
        client.saveToFile(outFile);

        outFile.close();
        std::cout << "������ ������� ���������." << std::endl << std::endl;
    }
    void saveToFile( std::ofstream& outFile) const {
        property.saveToFile(outFile);
        client.saveToFile(outFile);

    }
    void loadFromFile(std::ifstream& inFile) {
        property.loadFromFile(inFile);
        client.loadFromFile(inFile);
    }
    void viewApplications(int i) {
        string result = to_string(i) + ") " + to_string(property.numRooms) + "-�. " + to_string(property.minPrice) + "-" + to_string(property.maxPrice) + "�." + " �������� - " + ((property.amenities) ? "����" : "���") + "\n";
        result += "������������: " + property.address.country + "  �." + property.address.city + "  �-� " + property.address.district + "\n";
        result += "����������: " + client.secondName + " " + client.name;
        cout << result << endl << endl;
    }
};
std::ostream& operator << (std::ostream& outFile, BuyApplication& buyApp) {
    string result = to_string(buyApp.property.numRooms) + "-�. " + to_string(buyApp.property.minPrice) + "-" + to_string(buyApp.property.maxPrice) + "�." + " �������� - " + ((buyApp.property.amenities) ? "����" : "���") + "\n";
    result += "������������: " + buyApp.property.address.country + "  �." + buyApp.property.address.city + "  �-� " + buyApp.property.address.district + "\n";
    result += "����������: " + buyApp.client.secondName + " " + buyApp.client.name;
    cout << result << endl << endl;
    return outFile;
}
    

#endif
