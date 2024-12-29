#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an area
struct Area {
    int id;        // Unique ID for the area
    int demand;    // Demand score based on factors like traffic, population, etc.
    int cost;      // Cost to construct the pathway/bike lane in this area

    Area(int id, int demand, int cost) : id(id), demand(demand), cost(cost) {}
};

// Function to implement the Greedy Algorithm
vector<Area> selectAreasForDevelopment(vector<Area>& areas, int budget) {
    // Sort areas based on demand (highest first) and if demand is the same, by cost (lowest first)
    sort(areas.begin(), areas.end(), [](const Area& a, const Area& b) {
        if (a.demand == b.demand) return a.cost < b.cost;
        return a.demand > b.demand;
    });

    vector<Area> selectedAreas;
    int totalCost = 0;

    // Greedily select areas within the budget
    for (const Area& area : areas) {
        if (totalCost + area.cost <= budget) {
            selectedAreas.push_back(area);
            totalCost += area.cost;
        } else {
            break;
        }
    }

    return selectedAreas;
}

int main() {
    // Sample data: id, demand, cost to build
    vector<Area> areas = {
        Area(1, 80, 500),
        Area(2, 70, 400),
        Area(3, 90, 600),
        Area(4, 60, 300),
        Area(5, 75, 550)
    };

    int budget = 1000;  // Total available budget for construction

    // Call the Greedy Algorithm function
    vector<Area> selectedAreas = selectAreasForDevelopment(areas, budget);

    // Output selected areas for development
    cout << "Selected areas for construction within the budget: " << endl;
    for (const Area& area : selectedAreas) {
        cout << "Area ID: " << area.id << ", Demand: " << area.demand << ", Cost: " << area.cost << endl;
    }

    return 0;
}
