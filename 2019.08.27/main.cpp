#include <cstdio>

int main() {
    int length = 4;
    int arr[4] = {3, 15, 10, 7};
    int key = 17;

    int left_index = 0;
    int right_index = 1;

    while(left_index < length-1 && key - arr[left_index] != arr[right_index]) {
        if(right_index == length - 1){
            left_index++;
            right_index = left_index + 1; 
            continue;
        }

        right_index++;
    }

    if(left_index == length-1){
        fprintf(stderr, "Could not found pair to make %d in given array\n", key);
        return 1;       
    }

    printf("%d + %d = %d\n", arr[left_index], arr[right_index], key);

    return 0;
}