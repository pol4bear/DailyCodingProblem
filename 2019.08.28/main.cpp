#include <iostream>
#include <string>

using namespace std;

void MakeProductArray(int* array_in, int* array_out, int count) {
    int temp = 1;

    // Make array_out[index] have value of all numbers before index multiplied
    // temp value has value number[0]... * number[index - 1]
    for (int number_index = 0; number_index < count; ++number_index) {
        array_out[number_index] = temp;
        temp *= array_in[number_index];
    }

    temp = 1;
    
    // Multiply value that array_out haven't multiplied to array_out[index]
    // temp value has number[index + 1]... * number[count - 1]
    for (int number_index = count - 1; number_index >= 0; --number_index) {
        array_out[number_index] *= temp;
        temp *= array_in[number_index];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << "[number] [number] [number]...\n";
        exit(1);
    }

    int count = argc - 1;
    int *array_in = new int[count];
    int *array_out = new int[count];

    try{
        for (int number_index = 0; number_index < count; ++number_index) {
            array_in[number_index] = stoi(argv[number_index + 1]);
        }
    }
    catch(invalid_argument e) {
        cerr << "Non integer value has entered in argument\n";
        exit(1);
    }

    MakeProductArray(array_in, array_out, count);

    for (int number_index = 0; number_index < count; ++number_index) {
        cout << array_out[number_index] << " ";
    }
    cout << "\n";

    delete array_in;
    delete array_out;

    exit(0);
}