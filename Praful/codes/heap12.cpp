#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Rooftop {
    int id;
    int energyPotential;  // Energy generation potential

    bool operator<(const Rooftop& other) const {
        return energyPotential < other.energyPotential;  // Max-heap based on energy potential
    }
};

void prioritizeSolarPanelInstallation(const vector<Rooftop>& rooftops) {
    priority_queue<Rooftop> pq;

    // Push all rooftops into the max-heap
    for (const auto& rooftop : rooftops) {
        pq.push(rooftop);
    }

    cout << "Prioritized Rooftop Installations (Highest Energy Potential First):\n";
    while (!pq.empty()) {
        Rooftop topRooftop = pq.top();
        cout << "Rooftop ID: " << topRooftop.id << ", Energy Potential: " << topRooftop.energyPotential << endl;
        pq.pop();
    }
}

int main() {
    vector<Rooftop> rooftops = {
        {1, 500}, {2, 1200}, {3, 800}, {4, 600}, {5, 1500}
    };

    prioritizeSolarPanelInstallation(rooftops);

    return 0;
}
