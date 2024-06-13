#include <stdio.h>
#include <string.h>

typedef struct {
    char employee_name[50];
    int emp_no;
    float emp_salary;
} Employee;


int compareEmployees(const void *a, const void *b) {
    Employee *empA = (Employee *)a;
    Employee *empB = (Employee *)b;
    return empA->emp_no - empB->emp_no;
}


int binarySearch(Employee arr[], int l, int r, int x, int *comp_count) {
    while (l <= r) {
        (*comp_count)++;
        int mid = l + (r - l) / 2;

        if (arr[mid].emp_no == x)
            return mid;

        if (arr[mid].emp_no < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}


void printArray(Employee arr[], int size) {
	int i;
    for (i = 0; i < size; i++) {
        printf("Name: %s, Emp No: %d, Salary: %.2f\n", arr[i].employee_name, arr[i].emp_no, arr[i].emp_salary);
    }
}


int main() {
    // Example array of Employees
    Employee arr[] = {
        {"Alice", 105, 85000.5},
        {"Bob", 102, 90000.0},
        {"Charlie", 101, 95000.0},
        {"David", 104, 88500.5},
        {"Eve", 103, 92000.0}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    
    qsort(arr, n, sizeof(Employee), compareEmployees);

    printf("Sorted array of employees by emp_no:\n");
    printArray(arr, n);

    int x = 104; 
    int comp_count = 0; 

    int result = binarySearch(arr, 0, n - 1, x, &comp_count);

    if (result != -1) {
        printf("\nEmployee found at index %d:\n", result);
        printf("Name: %s, Emp No: %d, Salary: %.2f\n", arr[result].employee_name, arr[result].emp_no, arr[result].emp_salary);
    } else {
        printf("\nEmployee with emp_no %d not found.\n", x);
    }

    printf("\nNumber of comparisons made: %d\n", comp_count);

    return 0;
}