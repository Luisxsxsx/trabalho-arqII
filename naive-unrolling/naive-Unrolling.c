#include <stdio.h>
#include <stdlib.h>

#define M_SIZE 1000

double **multiplyMatrixes(double **matrixA, double **matrixB, int m_size);
void fillMatrixZero(double **matrix, int m_size); 
void fillMatrix(double **matrix, int m_size);     
double **allocate(int m_size);
void deAllocate(double **matrix, int m_size);
void printMatrix(double **matrix, int m_size);

// Naive - unrolling
double **multiplyMatrixes(double **matrixA, double **matrixB, int m_size)
{
    int idxRow, idxColumn, idxAux;
    double **matrixC = allocate(m_size);

    for (idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            for (idxAux = 0; idxAux < m_size; idxAux += 4)
            {
                matrixC[idxRow][idxColumn] += matrixA[idxRow][idxAux] * matrixB[idxAux][idxColumn];
                matrixC[idxRow][idxColumn] += matrixA[idxRow][idxAux + 1] * matrixB[idxAux + 1][idxColumn];
                matrixC[idxRow][idxColumn] += matrixA[idxRow][idxAux + 2] * matrixB[idxAux + 2][idxColumn];
                matrixC[idxRow][idxColumn] += matrixA[idxRow][idxAux + 3] * matrixB[idxAux + 3][idxColumn];
            }
        }
    }

    return matrixC;
}

void fillMatrixZero(double **matrix, int m_size)
{
    for (int idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (int idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            matrix[idxRow][idxColumn] = 0.0;
        }
    }
}

// AGORA é void (não retorna nada)
void fillMatrix(double **matrix, int m_size)
{
    for (int idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (int idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            matrix[idxRow][idxColumn] = (double)(idxRow + idxColumn);
        }
    }
}

double **allocate(int m_size)
{
    double **temp = (double **)malloc(sizeof(double *) * m_size);

    if (temp == NULL)
    {
        printf("ERRO: Falha na alocação de memória!\n");
        exit(1);
    }

    for (int idx = 0; idx < m_size; idx++)
    {
        temp[idx] = (double *)malloc(sizeof(double) * m_size);
        if (temp[idx] == NULL)
        {
            printf("ERRO: Falha na alocação de memória!\n");
            exit(1);
        }
    }

    return temp;
}

void deAllocate(double **matrix, int m_size)
{
    if (matrix == NULL)
        return;

    for (int idx = 0; idx < m_size; idx++)
    {
        if (matrix[idx] != NULL)
        {
            free(matrix[idx]);
        }
    }
    free(matrix);
}

void printMatrix(double **matrix, int m_size)
{
    printf("\n");
    for (int idxRow = 0; idxRow < m_size; idxRow++)
    {
        for (int idxColumn = 0; idxColumn < m_size; idxColumn++)
        {
            printf("%.0f ", matrix[idxRow][idxColumn]); // ← %f para double!
        }
        printf("\n");
    }
}

int main()
{
    printf("Multiplicando matrizes %dx%d com Naive-Unrolling\n", M_SIZE, M_SIZE);

    double **matrixA = allocate(M_SIZE);
    double **matrixB = allocate(M_SIZE);
    double **matrixC = NULL;

    fillMatrix(matrixA, M_SIZE);
    fillMatrix(matrixB, M_SIZE);

    // Só imprime se a matriz for pequena (evita poluir a tela)
    if (M_SIZE <= 10)
    {
        printf("Matriz A:");
        printMatrix(matrixA, M_SIZE);
        printf("Matriz B:");
        printMatrix(matrixB, M_SIZE);
    }

    matrixC = multiplyMatrixes(matrixA, matrixB, M_SIZE);

    if (M_SIZE <= 10)
    {
        printf("Matriz C (resultado):");
        printMatrix(matrixC, M_SIZE);
    }
    else
    {
        printf("Multiplicação concluída! (matriz muito grande para imprimir)\n");
    }

    deAllocate(matrixA, M_SIZE);
    deAllocate(matrixB, M_SIZE);
    deAllocate(matrixC, M_SIZE);

    printf("Programa finalizado com sucesso!\n");
    return 0;
}