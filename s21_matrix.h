#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define s21_EPS 1e-07

#define CORRECT_MATRIX 0
#define INCORRECT_MATRIX 1
#define ERROR 2

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
matrix_t minor_matrix(matrix_t *matrix, int columns, int rows);
int s21_calc_complements(matrix_t *A, matrix_t *result);  // !
int s21_determinant(matrix_t *A, double *result); // !
int s21_transpose(matrix_t *A, matrix_t *result);  
int s21_inverse_matrix(matrix_t *A, matrix_t *result);  // !

void fill_matrix_2(matrix_t *A);
void fill_matrix_3(matrix_t *A);
void fill_matrix_4(matrix_t *A);
void fill_matrix_5(matrix_t *A);
void print_matrix(matrix_t *A);
int s21_mult22(matrix_t *A, double number, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_

