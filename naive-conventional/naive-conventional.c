#include <stdio.h>
#include <stdlib.h>

int **allocate(int rows, int columns);
int **multiplyMatrixes(int **matrixA, int **matrixB, int rows, int columns);
void printMatrix(int **matrix, int rows, int columns);
void deallocate(int **matrix, int rows);


// Naive - conventional
int **multiplyMatrixes(int **matrixA, int **matrixB, int rows, int columns)
{
    int idxRow, idxColumn, idxAux;
    int **matrixC = allocate(rows, columns);

    for (idxRow = 0; idxRow < rows; idxRow++)
    {
        for (idxColumn = 0; idxColumn < columns; idxColumn++)
        {
            for (idxAux = 0; idxAux < rows; idxAux++)
                matrixC[idxRow][idxColumn] = matrixA[idxRow][idxAux] * matrixB[idxAux][idxColumn];
        }
    }

    return matrixC;
}

int **fillMatrix(int **matrix, int rows, int columns)
{
    int idxRow, idxColumn;
    for (idxRow = 0; idxRow < rows; idxRow++)
    {
        for (idxColumn = 0; idxColumn < columns; idxColumn++)
        {
            // *matrix[idxRow * rows + idxColumn] = idxRow + idxColumn;
            matrix[idxRow][idxColumn] = idxRow + idxColumn;
        }
    }

    return matrix;
}

int **allocate(int rows, int columns)
{
    int idx;
    int **temp = (int **)malloc(sizeof(int *) * rows);

    for (idx = 0; idx < columns; idx++)
    {
        temp[idx] = (int *)malloc(sizeof(int) * columns);
    }

    return temp;
}

void deallocate(int **matrix, int rows)
{
    int idx;
    for (idx = 0; idx < rows; idx++)
        free(matrix[idx]);
}

void printMatrix(int **matrix, int rows, int columns)
{
    printf("\n");
    int idxRow, idxColumn;
    for (idxRow = 0; idxRow < rows; idxRow++)
    {
        for (idxColumn = 0; idxColumn < columns; idxColumn++)
        {
            printf("%d ", matrix[idxRow][idxColumn]);
        }
        printf("\n");
    }
}

int main()
{
    int rows = 4,
        columns = 4;

    int **matrixA = allocate(rows, columns),
        **matrixB = allocate(rows, columns),
        **matrixC;

    matrixA = fillMatrix(matrixA, rows, columns);
    printMatrix(matrixA, rows, columns);

    matrixB = fillMatrix(matrixB, rows, columns);
    printMatrix(matrixB, rows, columns);

    matrixC = multiplyMatrixes(matrixA, matrixB, rows, columns);
    printMatrix(matrixC, rows, columns);

    deallocate(matrixA, rows);
    deallocate(matrixB, rows);
    deallocate(matrixC, rows);

    return 0;
}