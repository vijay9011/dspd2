#include <stdio.h>
#include <string.h>


typedef struct {
    char student_name[50];
    int student_roll_no;
    float total_marks;
} Student;


void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}


int partition(Student arr[], int low, int high, int* swap_count) {
    int pivot = arr[high].student_roll_no; 
    int i = (low - 1), j; 
    for (j = low; j <= high - 1; j++) {
        if (arr[j].student_roll_no < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            (*swap_count)++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*swap_count)++;
    return (i + 1);
}


void quickSort(Student arr[], int low, int high, int* swap_count) {
    if (low < high) {
        int pi = partition(arr, low, high, swap_count);

        quickSort(arr, low, pi - 1, swap_count);
        quickSort(arr, pi + 1, high, swap_count);
    }
}


void printArray(Student arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("Name: %s, Roll No: %d, Total Marks: %.2f\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}


int main() {
    
    Student arr[] = {
        {"Alice", 5, 85.5},
        {"Bob", 2, 90.0},
        {"Charlie", 1, 95.0},
        {"David", 4, 88.5},
        {"Eve", 3, 92.0}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    int swap_count = 0; 

    printf("Unsorted array of students:\n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1, &swap_count);

    printf("\nSorted array of students by roll number:\n");
    printArray(arr, n);

    printf("\nNumber of swaps performed: %d\n", swap_count);

    return 0;
}