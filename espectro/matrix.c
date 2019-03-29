#include "espectro.h"
#include <stdio.h>

MatrixOperation *matrix_head = 0;
double **B, **M, **R;

void
matrix_operation(int operation, double ***matrix, int row, int column, double value)
{
	MatrixOperation *new_operation;
	new_operation = (MatrixOperation *) malloc(sizeof (MatrixOperation));
	new_operation -> operation = operation;
	new_operation -> name.matrix = matrix;
	new_operation -> column = column;
	new_operation -> row = row;
	new_operation -> value = value;
	if (matrix_head)
		new_operation -> next = matrix_head;
	matrix_head = new_operation;
} /* end */

void
vector_operation(int operation, double **vector, int column, double value)
{
	MatrixOperation *new_operation;
	new_operation = (MatrixOperation *) malloc(sizeof (MatrixOperation));
	new_operation -> operation = operation;
	new_operation -> name.vector = vector;
	new_operation -> column = column;
	new_operation -> row = 0;
	new_operation -> value = value;
	if (matrix_head)
		new_operation -> next = matrix_head;
	matrix_head = new_operation;
} /* end */

void
matrix_operation_print()
{
	MatrixOperation *first;
	for (first=matrix_head; first; first = first -> next)
		fprintf(stderr, "operation %d: matrix %x[%d,%d] = %f\n",
			first -> operation,
			first -> name.matrix,
			first -> row,
			first -> column,
			first -> value);
} /* end matrix_operation_print */

double **
matrix_create(int rows, int columns)
{
	int i;
	double **matrix;
	matrix = (double **) malloc(rows * sizeof(double *));
	for (i = 0; i < rows; i++)
		matrix[i] = (double *) malloc(columns * sizeof(double));
	return(matrix);
} /* end matrix_create */

void
matrix_initialize(int nodes, int sources)
{
	M = matrix_create(nodes, nodes);
	R = matrix_create(nodes, nodes);
	B = matrix_create(nodes, sources);
} /* end matrix_create */

void
matrix_fill()
{
	MatrixOperation *first;
	for (first=matrix_head; first; first = first -> next)
		switch(first -> operation) {
		case M_STORE:
			(*first -> name.matrix)[first -> row][first -> column] = first -> value;
			break;
		case M_ADD:
			(*first -> name.matrix)[first -> row][first -> column] += first -> value;
			break;
		default:
			fatal("unknown operation in matrix_fill");
		} /* end switch */
} /* end matrix_fill */

void
matrix_print(double **matrix, int rows, int columns)
{
	int i,j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++)
			fprintf(stderr, "%f ", matrix[i][j]);
		fprintf(stderr, "\n");
	} /* end for i */
} /* end matrix_print */

void
matrix_output(int nodes, int sources)
{
	fprintf(stderr, "B:\n");
	matrix_print(B, nodes, sources);
	fprintf(stderr, "M:\n");
	matrix_print(M, nodes, nodes);
	fprintf(stderr, "R:\n");
	matrix_print(R, nodes, nodes);
} /* end matrix_output */
