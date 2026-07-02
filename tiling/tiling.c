#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 64
#define M_SIZE 1000

double **multiplyMatrixes(double **matrixA, double **matrixB, int m_size);
void fillMatrixZero(double **matrix, int m_size); 
void fillMatrix(double **matrix, int m_size);     
double **allocate(int m_size);
void deAllocate(double **matrix, int m_size);
void printMatrix(double **matrix, int m_size);

double **multiplyMatrixes(double **matrixA, double **matrixB, int m_size)
{
    int idxTRow, // indice do bloco
        idxTColumn, // indice do bloco
        idxTAux, // indice do bloco
        idxRow, // indice dentro do bloco
        idxColumn, //indice dentro do bloco
        idxAux, // indice dentro do bloco
        row_max, // limite interno do bloco
        col_max, // limite interno do bloco
        aux_max; // limite interno do bloco

    double **matrixC = allocate(m_size);

    // Inicializa com zeros
    fillMatrixZero(matrixC, m_size); // Agora é void

    // 3 'for' para mover entre os blocos
    for (idxTRow = 0; idxTRow < m_size; idxTRow += TILE_SIZE)
    {
        for (idxTColumn = 0; idxTColumn < m_size; idxTColumn += TILE_SIZE)
        {
            for (idxTAux = 0; idxTAux < m_size; idxTAux += TILE_SIZE)
            {
                row_max = (idxTRow + TILE_SIZE < m_size) ? idxTRow + TILE_SIZE : m_size;
                col_max = (idxTColumn + TILE_SIZE < m_size) ? idxTColumn + TILE_SIZE : m_size;
                aux_max = (idxTAux + TILE_SIZE < m_size) ? idxTAux + TILE_SIZE : m_size;

                // 3 'for' para se mover dentro dos blocos
                for (idxRow = idxTRow; idxRow < row_max; idxRow++)
                {
                    for (idxAux = idxTAux; idxAux < aux_max; idxAux++)
                    {
                        for (idxColumn = idxTColumn; idxColumn < col_max; idxColumn++)
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
    printf("Multiplicando matrizes %dx%d com TILE_SIZE=%d\n", M_SIZE, M_SIZE, TILE_SIZE);

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