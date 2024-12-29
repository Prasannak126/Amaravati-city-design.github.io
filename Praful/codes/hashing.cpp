#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Hash map to store energy allocation
    unordered_map<string, vector<string>> energyToFacilities;

    // Adding entries (Energy plants to facilities they power)
    energyToFacilities["EnergyPlant1"] = {"School1", "Library", "EducationCenter1"};
    energyToFacilities["EnergyPlant2"] = {"School2", "School3"};
    energyToFacilities["SolarFarm1"] = {"EducationCenter2", "School4"};

    // Hash map to store educational facility data
    unordered_map<string, string> educationFacilities;
    educationFacilities["School1"] = "Elementary School, Zone A";
    educationFacilities["Library"] = "City Library, Zone B";
    educationFacilities["EducationCenter1"] = "STEM Center, Zone C";
    educationFacilities["School2"] = "High School, Zone D";

    // Query energy plant allocations
    cout << "Facilities powered by EnergyPlant1:\n";
    for (const auto& facility : energyToFacilities["EnergyPlant1"]) {
        cout << " - " << facility << endl;
    }

    // Query information about a specific facility
    string facilityName = "School1";
    if (educationFacilities.find(facilityName) != educationFacilities.end()) {
        cout << "\nDetails for " << facilityName << ":\n";
        cout << educationFacilities[facilityName] << endl;
    } else {
        cout << "\nNo details found for " << facilityName << "." << endl;
    }

    return 0;
}
