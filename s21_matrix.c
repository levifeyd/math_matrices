#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int res_value = CORRECT_MATRIX;
    if (rows > 0 && columns > 0) {
        result -> rows = rows;
        result -> columns = columns;
        result -> matrix = calloc(rows, sizeof(double *));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = calloc(columns, sizeof(double));
        }
    } else {
        res_value = INCORRECT_MATRIX;
    }
    return res_value;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res_value = FAILURE;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL
        && B->columns > 0 && B->rows > 0 && B->matrix != NULL) {
        if (A->rows == B->rows && A->columns == B->columns) {
            res_value = SUCCESS;
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (fabs(A->matrix[i][j] - B->matrix[i][j]) > s21_EPS) {
                        res_value = FAILURE;
                    }
                }
            }
        }
    }
    return res_value;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++)
        if (A->rows > 0 && A->columns > 0 && A->matrix[i] != NULL)
            free(A->matrix[i]);
    if (A->matrix != NULL && A-> rows > 0 && A->columns)
        free(A->matrix);
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL
     && B->rows > 0 && B->matrix != NULL && result) {
        if (A->rows == B->rows && A->columns == B->columns) {
            res_value = CORRECT_MATRIX;
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < A->rows ; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        } else {
            res_value = ERROR;
        }
    }
    return res_value;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL
        && B->columns > 0 && B->rows > 0 && B->matrix != NULL && result) {
        if (A->columns == B->columns && A->rows == B->rows) {
                res_value = CORRECT_MATRIX;
                s21_create_matrix(A->rows, A->columns, result);
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++)
                        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
        } else {
            res_value = ERROR;
        }
    }
    return res_value;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int res_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL && result) {
        s21_create_matrix(A->rows, A->columns, result);
        res_value = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++)
                result->matrix[i][j] = A->matrix[i][j] * number;
        }
    }
    return res_value;
}
int s21_mult22(matrix_t *A, double number, matrix_t *result) {
    int res_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL && result) {
        s21_create_matrix(A->rows, A->columns, result);
        res_value = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++)
                if (A->matrix[i][j] != 0) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    return res_value;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL
        && B->columns > 0 && B->rows > 0 && B->matrix != NULL && result) {
        res_value = CORRECT_MATRIX;
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++)
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
           }
        }
    }
    return res_value;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int res_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL && result) {
            res_value = CORRECT_MATRIX;
            s21_create_matrix(A->columns, A->rows, result);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++)
                    result->matrix[j][i] = A->matrix[i][j];
            }
    }
    return res_value;
}

matrix_t minor_matrix(matrix_t *A, int rows, int columns) {
    matrix_t minor_matrix;
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix);
    for (int i = 0, x = 0; i < A->rows; i++) {
        if (rows != i) {
            for (int j = 0, y = 0; j < A->columns; j++) {
                if (columns != j) {
                    minor_matrix.matrix[x][y] = A->matrix[i][j];
                    y++;
                }
            }
            x++;
        }
    }
    return minor_matrix;
}

int s21_determinant(matrix_t *A, double *result) {
    int return_value = INCORRECT_MATRIX;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL && result) {
        if (A->columns == A->rows) {
            if (A->rows == 1 && A->columns == 1) {
                return_value = CORRECT_MATRIX;
                *result = A->matrix[0][0];
            }
            if (A->rows == 2 && A->columns == 2) {
                return_value = CORRECT_MATRIX;
                *result = (A->matrix[0][0] * A->matrix[1][1]) - (A->matrix[0][1] * A->matrix[1][0]);
            }
            if (A->rows > 2 && A->columns > 2) {
                return_value = CORRECT_MATRIX;
                *result = 0;
                for (int i = 0; i < A->columns; i++) {
                    matrix_t minor = minor_matrix(A, 0, i);  // чтобы не брать первый ряд и i-ую столбец
                    double tmp_determinant;
                    s21_determinant(&minor, &tmp_determinant);
                    s21_remove_matrix(&minor);
                    double tmp_res = pow(-1, 2 + i) * A->matrix[0][i] * tmp_determinant;
                    *result += tmp_res;
                }
            }
        } else {
            return_value = ERROR;
        }
    }
    return return_value;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {  // det * (-1)^(i+j)
    int res_value = INCORRECT_MATRIX;
    double temp = 0.0;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL && result) {
        if (A->columns == A->rows) {
            matrix_t tmp;
            res_value = CORRECT_MATRIX;
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < result->rows; i++) {
                for (int j = 0; j < result->columns; j++) {
                    tmp = minor_matrix(A, i, j);
                    s21_determinant(&tmp, &temp);
                    result->matrix[i][j] = temp * pow(-1, 2 + i + j);
                    s21_remove_matrix(&tmp);
                }
            }
        } else {
            res_value = ERROR;
        }
    }
    return res_value;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int return_value = INCORRECT_MATRIX;
    double determ = 0.0;
    if (A->columns > 0 && A->rows > 0 && A->matrix != NULL && result) {
        s21_determinant(A, &determ);
        if (fabs(determ) > s21_EPS) {
            return_value = CORRECT_MATRIX;
            matrix_t minor_matrix, transp_matrix;
            s21_calc_complements(A, &minor_matrix);
            if (s21_transpose(&minor_matrix, &transp_matrix) != 0)
                return_value = ERROR;
            s21_remove_matrix(&minor_matrix);
            s21_mult22(&transp_matrix, 1.0 / determ, result);
            s21_remove_matrix(&transp_matrix);
        } else {
                return_value = ERROR;
        }
    }
    return return_value;
}
