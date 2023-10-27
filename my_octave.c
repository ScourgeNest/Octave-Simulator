#include <stdio.h>
#include <stdlib.h>

#define INCR 1
#define MODULO 10007

//I use structs to stock matrices and the dimensions of it
typedef struct {
	int **mat;
	int rows;
	int columns;
} matrix;

//Here I allocate the array of matrices
void alloc_array_of_matrix(matrix **array, int *capacity)
{
	//I use a temporary pointer to allocate the array of matrices
	matrix *tmp = (matrix *)calloc(*capacity, sizeof(matrix));

	//Defensive programming
	if (!tmp) {
		printf("Failed to dynamically allocate tmp (alloc_array)");
		free(tmp);
		exit(-1);
	}

	*array = tmp;
}

//This function copy a matrix into another matrix
void mat_cp(int **source, int rows, int columns, int **dest)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			dest[i][j] = source[i][j];
}

//This function free each matrix in the array
void free_matrix (matrix *array, int index_array)
{
	for (int i = 0; i < index_array; i++)
		for (int j = 0; j < array[i].rows; j++)
			free(array[i].mat[j]);
	for (int i = 0; i < index_array; i++)
		free(array[i].mat);
}

//This function free a matrix
void free_mat(int **mat, int rows)
{
	for (int i = 0; i < rows; i++)
		free(mat[i]);
	free(mat);
}

//This function reallocate the array of matrices
void realloc_array(matrix **array, int *capacity)
{
	//I increase the capacity by INCR
	*capacity += INCR;

	//I use a temporary pointer to reallocate the array of matrices
	matrix *tmp;
	tmp = (matrix *)realloc(*array, *capacity * sizeof(matrix));

	//Defensive programming
	if (!tmp) {
		printf("Failed to dynamically allocate tmp (realloc_array)");
		free(tmp);
		exit(-1);
	}
	*array = tmp;
}

//This function allocate an array
void alloc_array(int rows, int **array)
{
	//I use a temporary pointer to allocate an array
	int *tmp = (int *)malloc(rows * sizeof(int));

	//Defensive programming
	if (!tmp) {
		printf("Failed to dynamically allocate tmp (matrix_alloc)");
		free(tmp);
		exit(-1);
	}

	*array = tmp;
}

void matrix_alloc(int rows, int columns, int ***mat)
{
	//I use a temporary pointer of pointers to allocate a matrix
	int **tmp = (int **)malloc(rows * sizeof(int *));

	//Defensive programming
	if (!tmp) {
		printf("Failed to dynamically allocate tmp (matrix_alloc)");
		free(tmp);
		exit(-1);
	}
	//Here I allocate each pointer
	for (int i = 0; i < rows; i++) {
		tmp[i] = (int *)malloc(columns * sizeof(int));

		//Defensive programming
		if (!tmp[i]) {
			printf("Failed to dynamically allocate tmp[i] (matrix_alloc)");
			for (int j = 0; j <= i; j++)
				free(tmp[j]);
			free(tmp);
			exit(-1);
		}
	}

	*mat = tmp;
}

//This function allocate a matrix with all elements equal to 0
void matrix_calloc(int rows, int columns, int ***mat)
{
	//I use a temporary pointer of pointers to allocate a matrix
	int **tmp = (int **)calloc(rows, sizeof(int *));

	//Defensive programming
	if (!tmp) {
		printf("Failed to dynamically allocate tmp (matrix_alloc)");
		free(tmp);
		exit(-1);
	}

	//Here I allocate each pointer
	for (int i = 0; i < rows; i++) {
		tmp[i] = (int *)calloc(columns, sizeof(int));

		//Defensive programming
		if (!tmp[i]) {
			printf("Failed to dynamically allocate tmp[i] (matrix_alloc)");
			for (int j = 0; j <= i; j++)
				free(tmp[j]);
			free(tmp);
			exit(-1);
		}
	}

	*mat = tmp;
}

//This function allocates and reads a matrix
void alloc_matrix(matrix *array, int *index)
{
	scanf("%d", &array[*index].rows);
	scanf("%d", &array[*index].columns);

	matrix_alloc(array[*index].rows, array[*index].columns, &array[*index].mat);

	for (int i = 0; i < array[*index].rows; i++)
		for (int j = 0; j < array[*index].columns; j++)
			scanf("%d", &array[*index].mat[i][j]);

	*index += 1;
}

//This function prints the dimensions of a matrix
void dim_matrix(matrix *array, int index_array)
{
	int index;
	scanf("%d", &index);

	if (index_array <= index || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	printf("%d %d\n", array[index].rows, array[index].columns);
}

//This function prints a matrix
void print_matrix(matrix *array, int index_array)
{
	int index;
	scanf("%d", &index);

	if (index_array <= index || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	for (int i = 0; i < array[index].rows; i++) {
		for (int j = 0; j < array[index].columns; j++)
			printf("%d ", array[index].mat[i][j]);
		printf("\n");
	}
}

//This function redimensions a matrix
void redim_matrix(matrix *array, int index_array)
{
	int index;
	scanf("%d", &index);

	int rows;
	scanf("%d", &rows);

	//I use a temporary array to stock the index of rows
	int *array_rows;
	alloc_array(rows, &array_rows);
	for (int i = 0; i < rows; i++)
		scanf("%d", &array_rows[i]);

	int columns;
	scanf("%d", &columns);

	//I use a temporary array to stock the index of columns
	int *array_columns;
	alloc_array(columns, &array_columns);
	for (int i = 0; i < columns; i++)
		scanf("%d", &array_columns[i]);

	//I verify if the matrix with the given index exists
	//If no I free the temporary arrays
	if (index_array <= index || index_array == 0 || index < 0) {
		printf("No matrix with the given index\n");
		free(array_columns);
		free(array_rows);
		return;
	}

	//I use a temporary matrix to store the elements that I need
	int **mat_redim;

	matrix_alloc(rows, columns, &mat_redim);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			mat_redim[i][j] = array[index].mat[array_rows[i]][array_columns[j]];

	//I free the initial matrix
	for (int i = 0; i < array[index].rows; i++)
		free(array[index].mat[i]);
	free(array[index].mat);

	//I allocate it again with different dimensions
	matrix_alloc(rows, columns, &array[index].mat);

	//I copy the temporary matrix into the initial matrix
	mat_cp(mat_redim, rows, columns, array[index].mat);

	//I change the dimensions
	array[index].rows = rows;
	array[index].columns = columns;

	//I free the temporary arrays and matrix
	free(array_rows);
	free(array_columns);
	free_mat(mat_redim, rows);
}

void multiplication_matrix(matrix *arr, int *ind)
{
	int ind1, ind2;
	scanf("%d %d", &ind1, &ind2);

	//I verify if the matrices exist
	if (*ind <= ind1 || *ind <= ind2 || ind1 < 0 || ind2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	//I verify if the number of columns of the first matrix is equal
	//to the number the number of rows of the second matrix
	if (arr[ind1].columns != arr[ind2].rows) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	//I set the dimensions according to the multiplication rules
	arr[*ind].rows = arr[ind1].rows;
	arr[*ind].columns = arr[ind2].columns;

	//I allocate the matrix using 'calloc' to make all the elements equal to 0
	arr[*ind].mat = (int **)calloc(arr[*ind].rows, sizeof(int *));
	if (!arr[*ind].mat) {
		printf("Failed to dynamically allocate arr[*ind].mat");
		free(arr[*ind].mat);
		exit(-1);
	}

	for (int i = 0; i < arr[*ind].rows; i++) {
		arr[*ind].mat[i] = (int *)calloc(arr[*ind].columns, sizeof(int));
		if (!arr[*ind].mat[i]) {
			printf("Failed to dynamically allocate arr[*ind].mat[i]");
			for (int j = 0; j <= i; j++)
				free(arr[*ind].mat[j]);
			free(arr[*ind].mat);
			exit(-1);
		}
	}

	//Here I do the multiplication
	for (int i = 0; i < arr[ind1].rows; i++) {
		for (int j = 0; j < arr[ind2].columns; j++) {
			for (int k = 0; k < arr[ind2].rows; k++) {
				int prod = arr[ind1].mat[i][k] * arr[ind2].mat[k][j];
				arr[*ind].mat[i][j] += prod;
				arr[*ind].mat[i][j] %= MODULO;
				if (arr[*ind].mat[i][j] < 0)
					arr[*ind].mat[i][j] += MODULO;
			}
		}
	}
	//I increase de index of matrices because the result
	//of the multiplication will be placed in the array of matrices
	*ind += 1;
}

//This function calculates the sum of all elements of the matrix given
int sum_mat(int **mat, int rows, int columns)
{
	int sum = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			sum += mat[i][j];
			sum %= MODULO;
			if (sum < 0)
				sum += MODULO;
		}
	}
	return sum;
}

//This function sorts the matrices of the array
//by the sum of elements
void sort_matrix(matrix *arr, int index_arr)
{
	for (int i = 0; i < index_arr; i++) {
		for (int j = i + 1; j < index_arr; j++) {
			//Here I calculate the sum of the matrix with index i and
			//the sum of the matrix with index j
			int sum_matrix_i = sum_mat(arr[i].mat, arr[i].rows, arr[i].columns);
			int sum_matrix_j = sum_mat(arr[j].mat, arr[j].rows, arr[j].columns);

			//I compare the sums
			if (sum_matrix_i > sum_matrix_j) {
				//I use a temporary matrix to make the swap
				int **aux;
				matrix_alloc(arr[i].rows, arr[i].columns, &aux);

				// I copy the matrix 'i' into the matrix 'aux'
				mat_cp(arr[i].mat, arr[i].rows, arr[i].columns, aux);

				//I free and allocate the matrix 'i' with the dimensions
				//of the matrix 'j' and then copy the matrix 'j' into it.
				free_mat(arr[i].mat, arr[i].rows);
				matrix_alloc(arr[j].rows, arr[j].columns, &arr[i].mat);
				mat_cp(arr[j].mat, arr[j].rows, arr[j].columns, arr[i].mat);

				//I free and allocate the matrix 'j' with the dimensions
				//of the matrix 'i' and then copy the matrix 'aux' into it.
				free_mat(arr[j].mat, arr[j].rows);
				matrix_alloc(arr[i].rows, arr[i].columns, &arr[j].mat);
				mat_cp(aux, arr[i].rows, arr[i].columns, arr[j].mat);

				//I free the temporary matrix
				free_mat(aux, arr[i].rows);

				//I change the dimensions of the 2 matrices
				int aux_rows = arr[i].rows;
				arr[i].rows = arr[j].rows;
				arr[j].rows = aux_rows;

				int aux_columns = arr[i].columns;
				arr[i].columns = arr[j].columns;
				arr[j].columns = aux_columns;
			}
		}
	}
}

//This function transposes a matrix
void transpose_matrix(matrix *array, int index_array)
{
	int index;
	scanf("%d", &index);
	if (index_array <= index || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	//I use a temporary matrix to transpose
	int **aux;
	int aux_rows = array[index].columns, aux_columns = array[index].rows;

	//I allocate the matrix with the dimensions that
	//the transposed matrix should have
	matrix_alloc(aux_rows, aux_columns, &aux);

	//I use the matrix to copy the trasposed matrix into aux
	for (int i = 0; i < aux_rows; i++)
		for (int j = 0; j < aux_columns; j++)
			aux[i][j] = array[index].mat[j][i];

	//I free the initial matrix
	free_mat(array[index].mat, array[index].rows);

	//I allocate the matrix with transposed matrix dimensions
	array[index].mat = (int **)calloc(aux_rows, sizeof(int *));
	if (!array[index].mat) {
		printf("Failed to dynamically allocate array[index].mat");
		free(array[index].mat);
		exit(-1);
	}

	for (int i = 0; i < aux_rows; i++) {
		array[index].mat[i] = (int *)calloc(aux_columns, sizeof(int));

		if (!array[index].mat[i]) {
			printf("Failed to dynamically allocate array[index].mat[i]");
			for (int j = 0; j <= i; j++)
				free(array[index].mat[j]);
			free(array[index].mat);
			exit(-1);
		}
	}
	//I copy into the matrix, the temporary one that has
	//the transpose of the initial matrix
	mat_cp(aux, aux_rows, aux_columns, array[index].mat);

	//I free the temporary matrix
	free_mat(aux, aux_rows);

	//I change the dimensions
	array[index].rows = aux_rows;
	array[index].columns = aux_columns;
}

void elim_matrix(matrix *arr, int *index_arr)
{
	int index;
	scanf("%d", &index);
	if (*index_arr <= index || *index_arr == 0 || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	//I free the matrix that i want to eliminate
	for (int i = index; i < *index_arr - 1; i++) {
		for (int j = 0; j < arr[i].rows; j++)
			free(arr[i].mat[j]);
		free(arr[i].mat);

		//I alloc the matrix 'i + 1' in the place of matrix 'i' and then
		//copy the matrix 'i + 1' there
		matrix_alloc(arr[i + 1].rows, arr[i + 1].columns, &arr[i].mat);
		mat_cp(arr[i + 1].mat, arr[i + 1].rows, arr[i + 1].columns, arr[i].mat);

		//I change the matrix dimensions
		arr[i].rows = arr[i + 1].rows;
		arr[i].columns = arr[i + 1].columns;
	}
	//I free the memory of the last matrix because
	//it is no longer used
	for (int i = 0; i < arr[*index_arr - 1].rows; i++)
		free(arr[*index_arr - 1].mat[i]);

	free(arr[*index_arr - 1].mat);
	*index_arr -= 1;
}

void matrix_x_matrix(int **mat1, int **mat2, int ***rez, int ind, matrix *array)
{
	int **aux;
	//I use a temporary matrix to make the multiplication
	matrix_calloc(array[ind].rows, array[ind].columns, &aux);
	for (int i = 0; i < array[ind].rows; i++) {
		for (int j = 0; j < array[ind].columns; j++) {
			for (int k = 0; k < array[ind].rows; k++) {
				aux[i][j] += mat1[i][k] * mat2[k][j];
				aux[i][j] %= MODULO;
				if (aux[i][j] < 0)
					aux[i][j] += MODULO;
			}
		}
	}
	//I free the first matrix because it will be
	//replaced with the result
	free_mat(mat1, array[ind].rows);
	*rez = aux;
}

void power_matrix(matrix *arr, int index_arr)
{
	int index, power;
	scanf("%d %d", &index, &power);
	if (index_arr <= index || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	//I verify if the power is positive
	if (power < 0) {
		printf("Power should be positive\n");
		return;
	}
	//I verify if the dimensions of the matrix are equal
	//so that the multiplications can perform
	if (arr[index].rows != arr[index].columns) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	//If the power is 0, I return the unit matrix
	if (power == 0) {
		for (int i = 0; i < arr[index].rows; i++) {
			for (int j = 0; j < arr[index].columns; j++) {
				if (i == j)
					arr[index].mat[i][j] = 1;
				else
					arr[index].mat[i][j] = 0;
			}
		}
	}
	//If the power is 1, No changes are needed
	if (power == 1)
		return;
	if (power >= 2) {
		//To raise a matrix to a power, I need 2 temporary matrices
		int **aux_1;
		//In the first one I put the unit matrix
		matrix_calloc(arr[index].rows, arr[index].columns, &aux_1);
		for (int i = 0; i < arr[index].rows; i++) {
			for (int j = 0; j < arr[index].columns; j++) {
				if (i == j)
					aux_1[i][j] = 1;
				else
					aux_1[i][j] = 0;
			}
		}
		int **aux_2;
		//In the second one I put the matrix
		matrix_calloc(arr[index].rows, arr[index].columns, &aux_2);
		mat_cp(arr[index].mat, arr[index].rows, arr[index].columns, aux_2);
		//I adapted the algorithm of raising a number to a power
		//to raising a matrix to a power
		while (power) {
			if (power % 2 == 1)
				matrix_x_matrix(aux_1, aux_2, &aux_1, index, arr);

			matrix_x_matrix(aux_2, aux_2, &aux_2, index, arr);
			power /= 2;
		}
		//I free the initial matrix;
		free_mat(arr[index].mat, arr[index].rows);
		//I give the initial matrix the pointer of the first temporary matrix
		arr[index].mat = aux_1;
		//and I free the second matrix
		free_mat(aux_2, arr[index].rows);
	}
}

int main(void)
{
	//Array of matrices
	matrix *array;

	int index_array = 0;
	int capacity = INCR;
	char command;
	//I allocate the array of matrices
	alloc_array_of_matrix(&array, &capacity);
	//I read commands until I read 'Q' to quit the program
	while (1) {
		scanf("%c", &command);
		if (command == ' ' || command == 10) {
			continue;
		} else if (command == 'L') {
			//If I have the maximum amount of matrices,
			//I increase the capacity and reallocate
			if (index_array == capacity) {
				capacity += INCR;
				matrix *tmp;
				tmp = (matrix *)realloc(array, capacity * sizeof(matrix));
				if (!tmp) {
					printf("Failed to dynamically allocate tmp");
					free(tmp);
					exit(-1);
				}
				array = tmp;
			}
			alloc_matrix(array, &index_array);
			continue;
		} else if (command == 'D') {
			dim_matrix(array, index_array);
			continue;
		} else if (command == 'P') {
			print_matrix(array, index_array);
			continue;
		} else if (command == 'C') {
			redim_matrix(array, index_array);
			continue;
		} else if (command == 'M') {
			//If I have the maximum amount of matrices,
			//I increase the capacity and reallocate
			if (index_array == capacity) {
				capacity += INCR;
				matrix *tmp;
				tmp = (matrix *)realloc(array, capacity * sizeof(matrix));
				if (!tmp) {
					printf("Failed to dynamically allocate tmp");
					free(tmp);
					exit(-1);
				}
				array = tmp;
			}
			multiplication_matrix(array, &index_array);
			continue;
		} else if (command == 'O') {
			sort_matrix(array, index_array);
			continue;
		} else if (command == 'T') {
			transpose_matrix(array, index_array);
			continue;
		} else if (command == 'R') {
			power_matrix(array, index_array);
			continue;
		} else if (command == 'F') {
			elim_matrix(array, &index_array);
			continue;
		} else if (command == 'Q') {
			free_matrix(array, index_array);
			free(array);
			break;
		}
		printf("Unrecognized command\n");
	}
	return 0;
}
