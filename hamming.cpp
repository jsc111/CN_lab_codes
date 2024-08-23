#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class IPAddress {
private:
    string ip;
    char ipClass;
    string defaultSubnetMask;
    string newSubnetMask;

public:
    IPAddress(string ip) : ip(ip) {}

    void calculateIPClass() {
        int firstOctet;
        stringstream ss(ip.substr(0, ip.find('.')));
        ss >> firstOctet;

        if (firstOctet >= 1 && firstOctet <= 126) {
            ipClass = 'A';
            defaultSubnetMask = "255.0.0.0";
        } else if (firstOctet >= 128 && firstOctet <= 191) {
            ipClass = 'B';
            defaultSubnetMask = "255.255.0.0";
        } else if (firstOctet >= 192 && firstOctet <= 223) {
            ipClass = 'C';
            defaultSubnetMask = "255.255.255.0";
        } else {
            ipClass = 'D'; // For multicast addresses
            defaultSubnetMask = "N/A";
        }
    }

    string getSubnetMask(int numSubnets) {
        int bitsToBorrow = 0;
        while ((1 << bitsToBorrow) < numSubnets)
            bitsToBorrow++;

        int subnetMask = 32 - bitsToBorrow;
        stringstream ss;
        ss << "255.255.255." << (256 - (1 << (8 - bitsToBorrow)));
        newSubnetMask = ss.str();
        return newSubnetMask;
    }

    void printSubnetRanges(int numSubnets) {
        int startRange = 0;
        int endRange = 0;
        int hostBits = 0;
        while ((1 << hostBits) < numSubnets)
            hostBits++;

        int increment = 1 << (8 - hostBits);
        for (int i = 0; i < numSubnets; i++) {
            startRange = endRange;
            endRange = startRange + increment - 1;
            cout << i + 1 << ":" << ip.substr(0, ip.rfind('.')) << "." << startRange << " to " << ip.substr(0, ip.rfind('.')) << "." << endRange << endl;
            endRange++;
        }
    }

    void displayDetails() {
        cout << "IP Address: " << ip << endl;
        cout << "Class of IP Address: " << ipClass << endl;
        cout << "Default Subnet Mask: " << defaultSubnetMask << endl;
    }
};

int main() {
    string ipAddress;
    int numSubnets;

    cout << "Enter IP Address: ";
    cin >> ipAddress;

    IPAddress ip(ipAddress);
    ip.calculateIPClass();
    ip.displayDetails();

    cout << "Enter number of Subnets to be created: ";
    cin >> numSubnets;

    ip.getSubnetMask(numSubnets);
    cout << "New Subnet Mask is: " << ip.getSubnetMask(numSubnets) << endl;

    cout << "Subnet Ranges:" << endl;
    ip.printSubnetRanges(numSubnets);

    return 0;
}