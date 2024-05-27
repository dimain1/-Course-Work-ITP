#pragma once
#ifndef SALEAPPLICATION_H
#define SALEAPPLICATION_H

#include"Application.h"
#include"SaleProperty.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SaleApplication : public Project::Application
{

public:
    SaleProperty property;
    SaleApplication() {
        client = Client();
        property = SaleProperty();
    }
    SaleApplication(Client c, SaleProperty p) {
        client = c;
        property = p;
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

        property.saveToFile(outFile);
        client.saveToFile(outFile);

        outFile.close();
        std::cout << "������ ������� ���������." << std::endl << std::endl;
    }
    void saveToFile(std::ofstream& outFile)const {
        property.saveToFile(outFile);
        client.saveToFile(outFile);
    }
    void loadFromFile(std::ifstream& inFile) {
        property.loadFromFile(inFile);
        client.loadFromFile(inFile);
    }
    void viewApplications(int i) {
        string result = to_string(i) + ") " + to_string(property.numRooms) + "-�. " + to_string(property.area) + " �^2." + " �������� - " + ((property.amenities) ? "����" : "���") + "\n";
        result += "������������: " + property.address.country + "  �." + property.address.city + "  �-� " + property.address.district + "\n";
        result += "��������: " + client.secondName + " " + client.name + " ���� " + to_string(property.price) + "�.";
        cout << result << endl << endl;
    }
   

private:
    size_t getNumObjects(const std::string& filename) const {
        std::ifstream inFile(filename, std::ios::binary);
        if (inFile.is_open()) {
            size_t numObjects = 0;
            inFile.read(reinterpret_cast<char*>(&numObjects), sizeof(numObjects));
            inFile.close();
            return numObjects;
        }
        else {
            std::cerr << "������������ ��� �������� ����: " << filename << std::endl;
            return 0;
        }
    }

};
#endif

std::ostream& operator << (std::ostream& os, SaleApplication saleApp) {
    string result = to_string(saleApp.property.numRooms) + "-�. " + to_string(saleApp.property.area) + " �^2." + " �������� - " + ((saleApp.property.amenities) ? "����" : "���") + "\n";
    result += "������������: " + saleApp.property.address.country + "  �." + saleApp.property.address.city + "  �-� " + saleApp.property.address.district + "\n";
    result += "��������: " + saleApp.client.secondName + " " + saleApp.client.name + " ���� " + to_string(saleApp.property.price) + "�.";
    os << result << endl << endl;
    return os;
}
