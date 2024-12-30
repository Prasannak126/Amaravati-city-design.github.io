#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class EducationResource {
public:
    void addResource(const string& resourceID, const string& resourceName) {
        resources[resourceID] = resourceName;
    }

    string getResource(const string& resourceID) {
        if (resources.find(resourceID) != resources.end()) {
            return resources[resourceID];
        } else {
            return "Resource not found!";
        }
    }

private:
    unordered_map<string, string> resources;
};

int main() {
    EducationResource library;

    // Adding resources
    library.addResource("CS101", "Introduction to Computer Science");
    library.addResource("MATH201", "Advanced Mathematics");
    library.addResource("BIO102", "Basic Biology");

    // Accessing resources
    cout << "Fetching resource for CS101: " << library.getResource("CS101") << endl;
    cout << "Fetching resource for MATH201: " << library.getResource("MATH201") << endl;
    cout << "Fetching resource for BIO102: " << library.getResource("BIO102") << endl;
    cout << "Fetching resource for CHEM303: " << library.getResource("CHEM303") << endl;

    return 0;
}
