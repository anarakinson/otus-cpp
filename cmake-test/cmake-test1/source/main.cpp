#include <iostream>
#include "version.h"

using namespace std;

int main() {
    cout << "Hello" << endl;
    cout << "Version: " << examples::getVersion() << endl;
}