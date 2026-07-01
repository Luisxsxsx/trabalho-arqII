#include <stdio.h>
#include <stdlib.h>
#define TILE_SIZE 64
#define M_SIZE 1000

int **allocate(int m_size);
int **multiplyMatrixes(int **matrixA, int **matrixB, int m_size);
int **fillMatrix(int **matrix, int m_size);
int **fillMatrixZero(int **matrix, int m_size);
void printMatrix(int **matrix, int m_size);
void deallocate(int **matrix, int rows);

// Tiling
int **multiplyMatrixes(int **matrixA, int **matrixB, int m_size)
{
    int idxTRow, idxTColumn, idxTAux, idxRow, idxColumn, idxAux;
    int **matrixC = allocate(m_size);
    matrixC = fillMatrixZero(matrixC, m_size);

    // 3 'for' para mover entre os blocos
    for (idxTRow = 0; idxTRow < m_size; idxTRow += TILE_SIZE)
    {
        for (idxTColumn = 0; idxTColumn < m_size; idxTColumn += TILE_SIZE)
        {
            for (idxTAux = 0; idxTAux < m_size; idxTAux += TILE_SIZE)
            {
                // 3 'for' para se mover dentro dos blocos
                for (idxRow = idxTRow; idxRow < m_size && idxRow < idxTRow + TILE_SIZE; idxRow++)
                {
                    for (idxAux = idxTAux; idxAux < m_size && idxAux < idxTAux + TILE_SIZE; idxAux++)
                    {
                        for (idxColumn = idxTColumn; idxColumn < idxTColumn + TILE_SIZE && idxColumn < m_size; idxColumn++)
                        {
                            matrixC[idxRow][idxColumn] += matrixA[idxRow][idxAux] * matrixB[idxAux][idxColumn];
                        }
                    }
                }
            }
        }
    }

    return matrixC;
}

int **fillMatrixZero(int **matrix, int m_size)
{
    int idxRow, idxColumn;
    for (idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            matrix[idxRow][idxColumn] = 0;
        }
    }

    return matrix;
}

int **fillMatrix(int **matrix, int m_size)
{
    int idxRow, idxColumn;
    for (idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            // *matrix[idxRow * rows + idxColumn] = idxRow + idxColumn;
            matrix[idxRow][idxColumn] = idxRow + idxColumn;
        }
    }

    return matrix;
}

int **allocate(int m_size)
{
    int idx;
    int **temp = (int **)malloc(sizeof(int *) * m_size);

    for (idx = 0; idx < m_size; idx++)
    {
        temp[idx] = (int *)malloc(sizeof(int) * m_size);
    }

    return temp;
}

void deallocate(int **matrix, int m_size)
{
    int idx;
    for (idx = 0; idx < m_size; idx++)
        free(matrix[idx]);
}

void printMatrix(int **matrix, int m_size)
{
    printf("\n");
    int idxRow, idxColumn;
    for (idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            printf("%d ", matrix[idxRow][idxColumn]);
        }
        printf("\n");
    }
}

int main()
{
    int **matrixA = allocate(M_SIZE),
        **matrixB = allocate(M_SIZE),
        **matrixC;

    matrixA = fillMatrix(matrixA, M_SIZE);
    printMatrix(matrixA, M_SIZE);

    matrixB = fillMatrix(matrixB, M_SIZE);
    printMatrix(matrixB, M_SIZE);

    matrixC = multiplyMatrixes(matrixA, matrixB, M_SIZE);
    printMatrix(matrixC, M_SIZE);

    deallocate(matrixA, M_SIZE);
    deallocate(matrixB, M_SIZE);
    deallocate(matrixC, M_SIZE);

    return 0;
}