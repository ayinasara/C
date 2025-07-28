#include <stdio.h>

#define MAX 100

void readSparse(int mat[MAX][3], int *num) {
    printf("Enter the number of non-zero elements: ");
    scanf("%d", num);
    printf("Enter the elements as row column value:\n");
    for (int i = 0; i < *num; i++) {
        scanf("%d %d %d", &mat[i][0], &mat[i][1], &mat[i][2]);
    }
}

void printSparse(int mat[MAX][3], int num) {
    printf("Row\tCol\tVal\n");
    for (int i = 0; i < num; i++) {
        printf("%d\t%d\t%d\n", mat[i][0], mat[i][1], mat[i][2]);
    }
}

int addSparse(int a[MAX][3], int na, int b[MAX][3], int nb, int res[MAX][3]) {
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb) {
        if (a[i][0] < b[j][0] || (a[i][0] == b[j][0] && a[i][1] < b[j][1])) {
            res[k][0] = a[i][0];
            res[k][1] = a[i][1];
            res[k][2] = a[i][2];
            i++;
            k++;
        } else if (b[j][0] < a[i][0] || (a[i][0] == b[j][0] && b[j][1] < a[i][1])) {
            res[k][0] = b[j][0];
            res[k][1] = b[j][1];
            res[k][2] = b[j][2];
            j++;
            k++;
        } else {
            int sum = a[i][2] + b[j][2];
            if (sum != 0) {
                res[k][0] = a[i][0];
                res[k][1] = a[i][1];
                res[k][2] = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    while (i < na) {
        res[k][0] = a[i][0];
        res[k][1] = a[i][1];
        res[k][2] = a[i][2];
        i++;
        k++;
    }

    while (j < nb) {
        res[k][0] = b[j][0];
        res[k][1] = b[j][1];
        res[k][2] = b[j][2];
        j++;
        k++;
    }

    return k;
}

int main() {
    int a[MAX][3], b[MAX][3], res[MAX][3];
    int na, nb, nr;

    printf("Enter first sparse matrix:\n");
    readSparse(a, &na);

    printf("\nEnter second sparse matrix:\n");
    readSparse(b, &nb);

    nr = addSparse(a, na, b, nb, res);

    printf("\nFirst Matrix:\n");
    printSparse(a, na);

    printf("\nSecond Matrix:\n");
    printSparse(b, nb);

    printf("\nSum Matrix:\n");
    printSparse(res, nr);

    return 0;
}
