#include <stdio.h>


void convertToSparse(int matrix[10][10], int rows, int cols, int sparse[50][3]) {
    int k = 1; // Start from index 1 (index 0 is metadata)

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    sparse[0][0] = rows;
    sparse[0][1] = cols;
    sparse[0][2] = k - 1; 
}


void printSparse(int sparse[50][3]) {
    int n = sparse[0][2]; 

    printf("Row\tCol\tValue\n");
    for (int i = 0; i <= n; i++) {
        printf("%d\t%d\t%d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
    }
}
void addSparseMatrices(int sp1[50][3], int sp2[50][3], int result[50][3]) {
    if (sp1[0][0] != sp2[0][0] || sp1[0][1] != sp2[0][1]) {
        printf("matrix not possible.\n");
        return;
    }

    int i = 1, j = 1, k = 1;
    result[0][0] = sp1[0][0];
    result[0][1] = sp1[0][1];

    while (i <= sp1[0][2] && j <= sp2[0][2]) {
        if (sp1[i][0] < sp2[j][0] || 
           (sp1[i][0] == sp2[j][0] && sp1[i][1] < sp2[j][1])) {
            result[k][0] = sp1[i][0];
            result[k][1] = sp1[i][1];
            result[k][2] = sp1[i][2];
            i++;
            k++;
        } else if (sp2[j][0] < sp1[i][0] || 
                 (sp2[j][0] == sp1[i][0] && sp2[j][1] < sp1[i][1])) {
            result[k][0] = sp2[j][0];
            result[k][1] = sp2[j][1];
            result[k][2] = sp2[j][2];
            j++;
            k++;
        } else {
            int sum = sp1[i][2] + sp2[j][2];
            if (sum != 0) {
                result[k][0] = sp1[i][0];
                result[k][1] = sp1[i][1];
                result[k][2] = sum;
                k++;
            }
            i++;
            j++;
        }
    }


    while (i <= sp1[0][2]) {
        result[k][0] = sp1[i][0];
        result[k][1] = sp1[i][1];
        result[k][2] = sp1[i][2];
        i++;
        k++;
    }

    while (j <= sp2[0][2]) {
        result[k][0] = sp2[j][0];
        result[k][1] = sp2[j][1];
        result[k][2] = sp2[j][2];
        j++;
        k++;
    }

    result[0][2] = k - 1; 
}


void transposeSparse(int sparse[50][3], int trans[50][3]) {
    int k = 1;
    trans[0][0] = sparse[0][1]; 
    trans[0][1] = sparse[0][0]; 
    trans[0][2] = sparse[0][2]; 

    for (int col = 0; col < sparse[0][1]; col++) {
        for (int i = 1; i <= sparse[0][2]; i++) {
            if (sparse[i][1] == col) {
                trans[k][0] = sparse[i][1];
                trans[k][1] = sparse[i][0];
                trans[k][2] = sparse[i][2];
                k++;
            }
        }
    }
}


int main() {
    int mat1[10][10], mat2[10][10];
    int sparse1[50][3], sparse2[50][3], sparseSum[50][3], transposed[50][3];
    int rows, cols;

    printf("Enter number of rows and columns (max 10): ");
    scanf("%d %d", &rows, &cols);

    printf("Enter Matrix 1:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat1[i][j]);

    printf("Enter Matrix 2:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat2[i][j]);

  
    convertToSparse(mat1, rows, cols, sparse1);
    convertToSparse(mat2, rows, cols, sparse2);

    
    printf("\nSparse Matrix 1:\n");
    printSparse(sparse1);

    printf("\nSparse Matrix 2:\n");
    printSparse(sparse2);

    
    addSparseMatrices(sparse1, sparse2, sparseSum);
    printf("\nSum of Sparse Matrices:\n");
    printSparse(sparseSum);

    transposeSparse(sparseSum, transposed);
    printf("\nTranspose of Sum Matrix:\n");
    printSparse(transposed);

    return 0;
}
