#include <iostream>
#include <string>
#include <locale>

using namespace std;

int lengthString ( char* c) {
	int len = 0;
	while ( c[len] != '\0' ) {
		++len;
	}
	return len;
}

class matrix {
	double** matr;
	int rowsnum;
	int columnsnum;
public:
	matrix ( int n, int m ) {
		rowsnum = n;
		columnsnum = m;
		matr = new double*[n];
		for ( int i = 0 ; i < n ; ++i ) {
			matr[i] = new double[m];
			for ( int j = 0 ; j < m ; ++j ) {
				matr[i][j] = 0.0;
			}
		}
	}
	matrix ( double num ) {
		rowsnum = 1;
		columnsnum = 1;
		matr = new double*[1];
		matr[0] = new double[1];
		matr[0][0] = num;
	}
	matrix ( double* nums, int m ) {
		rowsnum = 1;
		columnsnum = m;
		matr = new double*[1];
		matr[0] = new double[m];
		for ( int i = 0 ; i < m ; ++i ) {
			matr[0][i] = nums[i];
		}
	}
	matrix ( int n, double* nums ) {
		rowsnum = n;
		columnsnum = 1;
		matr = new double*[n];
		for ( int i = 0 ; i < n ; ++i ) {
			matr[i] = new double(nums[i]);
		}
	}
	matrix ( string c ) {
		int state = 0, rn, cn, signmul = 1, emultnum = 0;
		double mult = 1.0, emult = 1.0, sign = 1.0;
		rowsnum = 1;
		columnsnum = 1;
		for ( int i = 0 ; i < c.size() ; ++i ) {
			if ( c[i] == '{' ) {
				state = 1;
			}
			if ( c[i] == '}' ) {
				state = 0;
			}
			if ( c[i] == ',' ) {
				if ( state == 0 ) {
					rowsnum++;
				}
				columnsnum++;
			}
		}
		matr = new double*[rowsnum];
		columnsnum /= rowsnum;
		for ( int i = 0 ; i < rowsnum ; ++i ) {
			matr[i] = new double[columnsnum];
			for ( int j = 0 ; j < columnsnum ; ++j ) {
				matr[i][j] = 0.0;
			}
		}
		rn = 0;
		cn = 0;
		for ( int i = 0 ; i < c.size() ; ++i ) {
			if ( c[i] == '{' ) {
				state = 1;
			}
			if ( c[i] == '}' ) {
				if ( ( state == 2 || state == 3 ) || state == 4 ) {
					if ( state = 4 ) {
						for ( int j = 0 ; j < emultnum ; ++j ) {
							emult *= 10;
						}
					}
					if ( signmul == -1 ) {
						mult *= emult;
					} else {
						mult /= emult;
					}
					matr[rn][cn] /= mult;
					matr[rn][cn] *= sign;
					emult = 1.0;
					mult = 1.0;
					sign = 1.0;
					signmul = 1;
					emultnum = 0;
				}
				state = 0;
				cn = 0;
			}
			if ( c[i] == ',' ) {
				if ( state == 0 ) {
					++rn;
				} else {
					if ( ( state == 2 || state == 3 ) || state == 4 ) {
						if ( state = 4 ) {
							for ( int j = 0 ; j < emultnum ; ++j ) {
								emult *= 10;
							}
						}
						if ( signmul == -1 ) {
							mult *= emult;
						} else {
							mult /= emult;
						}
						matr[rn][cn] /= mult;
						matr[rn][cn] *= sign;
						mult = 1.0;
						emult = 1.0;
						sign = 1.0;
						signmul = 1;
						state = 1;
						emultnum = 0;
					}
					++cn;
				}
			}
			if ( c[i] == ' ' && ( ( state == 2 || state == 3 ) || state == 4 ) ) {
				if ( state = 4 ) {
					for ( int j = 0 ; j < emultnum ; ++j ) {
						emult *= 10;
					}
				}
				if ( signmul == -1 ) {
					mult *= emult;
				} else {
					mult /= emult;
				}
				matr[rn][cn] /= mult;
				matr[rn][cn] *= sign;
				sign = 1.0;
				emult = 1.0;
				signmul = 1;
				mult = 1.0;
				state = 1;
				emultnum = 0;
			}
			if ( c[i] == '-' && state == 1 ) {
				sign = -1.0;
			}
			if ( isdigit(c[i]) && ( state == 1 || state == 2 ) ) {
				state = 2;
				matr[rn][cn] = matr[rn][cn] * 10 + ( c[i] - '0' );
			}
			if ( c[i] == '.' && ( state == 1 || state == 2 ) ) {
				state = 3;
			}
			if ( isdigit(c[i]) && state == 3 ) {
				matr[rn][cn] = matr[rn][cn] * 10 + ( c[i] - '0' );
				mult *= 10;
			}
			if ( c[i] == 'e' ) {
				state = 4;
			}
			if ( c[i] == '-' && state == 4 ) {
				signmul = -1;
			}
			if ( isdigit(c[i]) && state == 4 ) {
				emultnum = emultnum * 10 + ( c[i] - '0' );
			}
		}
	}
	/*~matrix() {
		if ( matr != NULL ) {
			for ( int i = 0 ; i < rows() ; ++i ) {
				delete[] matr[i];
			}
			delete[] matr;
		}
		rowsnum = 0;
		columnsnum = 0;
		matr = NULL;
	}*/
	matrix row ( int n ) {
		try {
			if ( n - 1 >= rowsnum )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": incopatible number of row for this matrix" << endl;
		}
		matrix mat( 1, columnsnum );
		for ( int i = 0 ; i < columnsnum ; ++i ) {
			mat.matr[0][i] = matr[n - 1][i];
		}
		return mat;
	}
	matrix column ( int n ) {
		try {
			if ( n - 1 >= columnsnum )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": incopatible number of column for this matrix" << endl;
		}
		matrix mat( rowsnum, 1 );
		for ( int i = 0 ; i < rowsnum ; ++i ) {
			mat.matr[i][0] = matr[i][n-1];
		}
		return mat;
	}
	matrix identity ( int n ) {
		matrix mat(n, n);
		for ( int i = 0 ; i < n ; ++i ) {
			mat.matr[i][i] = 1.0;
		}
		return mat;
	}
	matrix diagonal ( double* vals, int n ) {
		matrix mat(n, n);
		for ( int i = 0 ; i < n ; ++i ) {
			mat.matr[i][i] = vals[i];
		}
		return mat;
	}
	int rows () {
		return rowsnum;
	}
	int columns () {
		return columnsnum;
	}
	void set ( int i, int j, double val ) {
		try {
			if ( i - 1 >= rowsnum )
				throw( (int)1 );
			if ( j - 1 >= columnsnum )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": incopatible number of row for this matrix" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": incopatible number of column for this matrix" << endl;
		}
		matr[i-1][j-1] = val;
	}
	friend matrix operator+ ( matrix& left, matrix& right ) {
		try {
			if ( left.rows() != right.rows() )
				throw( (int)1 );
			if ( left.columns() != right.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		matrix mat = matrix( right.rows(), right.columns() );
		for ( int i = 0 ; i < right.rows() ; ++i ) {
			for ( int j = 0 ; j < right.columns() ; ++j ) {
				mat.matr[i][j] = left.matr[i][j] + right.matr[i][j];
			}
		}
		mat.rowsnum = left.rows();
		mat.columnsnum = left.columns();
		return (mat);
	}
	matrix& operator+= ( matrix& right ) {
		try {
			if ( rows() != right.rows() )
				throw( (int)1 );
			if ( columns() != right.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < columns() ; ++j ) {
				matr[i][j] += right.matr[i][j];
			}
		}
		rowsnum = rows();
		columnsnum = columns();
		return (*this);
	}
	friend matrix operator- ( matrix& left, matrix& right ) {
		try {
			if ( left.rows() != right.rows() )
				throw( (int)1 );
			if ( left.columns() != right.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		matrix mat = matrix( right.rows(), right.columns() );
		for ( int i = 0 ; i < right.rows() ; ++i ) {
			for ( int j = 0 ; j < right.columns() ; ++j ) {
				mat.matr[i][j] = left.matr[i][j] - right.matr[i][j];
			}
		}
		mat.rowsnum = left.rows();
		mat.columnsnum = left.columns();
		return (mat);
	}
	matrix& operator-= ( matrix& right ) {
		try {
			if ( rows() != right.rows() )
				throw( (int)1 );
			if ( columns() != right.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < columns() ; ++j ) {
				matr[i][j] -= right.matr[i][j];
			}
		}
		rowsnum = rows();
		columnsnum = columns();
		return (*this);
	}
	friend matrix operator- ( matrix& right) {
		matrix mat(right.rows(), right.columns());
		for ( int i = 0 ; i < right.rows() ; ++i ) {
			for ( int j = 0 ; j < right.columns() ; ++j ) {
				mat.matr[i][j] = - right.matr[i][j];
			}
		}
		return (mat);
	}
	friend matrix& operator* ( matrix& left, matrix& right ) {
		try {
			if ( left.columns() != right.rows() )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": matrixes' sizes don't fill in the criteria" << endl;
		}
		matrix *mat = new matrix( left.rows(), right.columns() );
		for ( int i = 0 ; i < left.rows() ; ++i ) {
			for ( int j = 0 ; j < right.columns() ; ++j ) {
				for ( int k = 0 ; k < left.columns() ; ++k ) {
					mat->matr[i][j] += left.matr[i][k]*right.matr[k][j];
				}
			}
		}
		return *mat;
	}
	friend matrix& operator*= ( matrix& left, matrix& right ) {
		try {
			if ( left.columns() != left.rows() )
				throw( (int)1 );
			if ( left.columns() != right.rows() )
				throw( (int)2 );
			if ( right.columns() != right.rows() )
				throw( (int)3 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes have to be type NxN for this operation" << endl;
			if ( x == 3 )
				cout << "Error " << x << ": matrixes have to be type NxN for this operation" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' sizes don't fill in the criteria" << endl;
		}
		matrix mat(left.rows(), right.columns());
		for ( int i = 0 ; i < left.rows() ; ++i ) {
			for ( int j = 0 ; j < right.columns() ; ++j ) {
				for ( int k = 0 ; k < left.columns() ; ++k ) {
					mat.matr[i][j] += left.matr[i][k]*right.matr[k][j];
				}
			}
		}
		left = mat;
	}
	matrix& operator= ( matrix& r ) {
		if ( this == &r )
			return r;
		try {
			if ( rows() != r.rows() )
				throw( (int)1 );
			if ( columns() != r.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < columns() ; ++j ) {
				matr[i][j] = r.matr[i][j];
			}
		}
		rowsnum = r.rowsnum;
		columnsnum = r.columnsnum;
	}
	matrix Matrix_no_ij ( matrix& Mat, int i, int j ) {
		try {
			if ( i - 1 >= columnsnum )
				throw( (int)1 );
			if ( j - 1 >= rowsnum )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": incopatible number of column for this matrix" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		matrix mat( Mat.rows() - 1, Mat.columns() - 1 );
		for ( int l = 0 ; l < Mat.rows() ; ++l ) {
			for ( int k = 0 ; k < Mat.columns() ; ++k ) {
				if ( l < i - 1 && k < j - 1 ) {
					mat.matr[l][k] = Mat.matr[l][k];
				}
				if ( l < i - 1 && k > j - 1 ) {
					mat.matr[l][k-1] = Mat.matr[l][k];
				}
				if ( l > i - 1 && k < j - 1 ) {
					mat.matr[l-1][k] = Mat.matr[l][k];
				}
				if ( l > i - 1 && k > j - 1 ) {
					mat.matr[l-1][k-1] = Mat.matr[l][k];
				}
			}
		}
		return mat;
	}
	bool operator== ( matrix Matrix ) {
		try {
			if ( rows() != Matrix.rows() )
				throw( (int)1 );
			if ( columns() != Matrix.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < columns() ; ++j ) {
				if ( matr[i][j] != Matrix.matr[i][j] ) {
					return false;
				}
			}
		}
		return true;
	}
	bool operator!= ( matrix Matrix ) {
		try {
			if ( rows() != Matrix.rows() )
				throw( (int)1 );
			if ( columns() != Matrix.columns() )
				throw( (int)2 );
		}
		catch( int x ) {
			if ( x == 1 )
				cout << "Error " << x << ": matrixes' numbers of rows don't match" << endl;
			if ( x == 2 )
				cout << "Error " << x << ": matrixes' numbers of columns don't match" << endl;
		}
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < columns() ; ++j ) {
				if ( matr[i][j] != Matrix.matr[i][j] ) {
					return true;
				}
			}
		}
		return false;
	}
	double determinant ( matrix Matrix ) {
		try {
			if ( rows() != columns() )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": incopatible size of matrix, has to be type NxN" << endl;
		}
		double result = 0.0, sign = 1.0;
		if ( Matrix.rows() == 1 ) {
			result = Matrix.matr[0][0];
		} else {
			for ( int i = 0 ; i < Matrix.rows() ; ++i, sign *= -1 ) {
				result = result + ( sign * Matrix.matr[0][i] ) * determinant( Matrix_no_ij(Matrix, 1, i + 1) );
			}
		}
		return result;
	}
	matrix& operator~ () {
		try {
			if ( rows() != columns() )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": incopatible size of matrix, has to be type NxN" << endl;
		}
		double det = 1 / determinant( *this );
		for ( int i = 1 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j <= i-1 ; ++j ) {
				matr[i][j] += matr[j][i];
				matr[j][i] = matr[i][j] - matr[j][i];
				matr[i][j] = matr[i][j] - matr[j][i];
			}
		}
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < rows() ; ++j ) {
				matr[i][j] *= det;
			}
		}
		rowsnum = rowsnum;
		columnsnum = columnsnum;
	}
	matrix operator| ( matrix& right ) {
		try {
			if ( rows() != right.rows() )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": incopatible sizes of matrixes" << endl;
		}
		const matrix mat( rows(), columns() + right.columns() );
		for ( int i = 0 ; i < rows() ; ++i ) {
			for ( int j = 0 ; j < columns() + right.columns() ; ++j ) {
				if ( j < columns() ) {
					mat.matr[i][j] = matr[i][j];
				} else {
					mat.matr[i][j] = right.matr[i][j - columns()];
				}
			}
		}
		return mat;
	}
	matrix operator/ ( matrix& right ) {
		try {
			if ( columns() != right.columns() )
				throw( (int)1 );
		}
		catch( int x ) {
			cout << "Error " << x << ": incopatible sizes of matrixes" << endl;
		}
		const matrix mat( rows() + right.rows(), columns() );
		for ( int i = 0 ; i < rows() + right.rows() ; ++i ) {
			for ( int j = 0 ; j < columns() ; ++j ) {
				if ( i < rows() ) {
					mat.matr[i][j] = matr[i][j];
				} else {
					mat.matr[i][j] = right.matr[i - rows()][j];
				}
			}
		}
		return mat;
	}/*
	~matrix() {
		for ( int i = 0 ; i < rowsnum ; ++i ) {
			delete matr[i];
		}
		delete matr;
	}*/
	friend void printmatrix( matrix );
};

void printmatrix ( matrix Matrix ) {
	cout << "rows - " << Matrix.rows() << endl;
	cout << "columns - " << Matrix.columns() << endl;
	for ( int i = 0 ; i < Matrix.rows() ; ++i ) {
		cout << "|";
		for ( int  j = 0 ; j < Matrix.columns() ; ++j ) {
			cout << Matrix.matr[i][j] << '\t';
		}
		cout << "|" << endl;
	}
}


int main() {
	double nums1[] = {12.5, 3.1415, 10.9}, nums2[] = {1.2, 12.3, 0.98123, 10.9, 0.00014};
	bool t;
//	string c;
//	cin >> c;
	matrix mat1(12, 7), mat2(2.54), mat3(nums1, 3), mat4(5, nums2), mat5 = mat5.identity(5);
	matrix mat6 = mat6.diagonal(nums1,3), mat7 = mat7.diagonal(nums2,5), mat8("{ { 1.0 , 2.0 , 3.0 } , { 4.0 , 5.0 , 6.0 } }");
	matrix mat9("{{1.0, 2 ,3.0 } ,{ 4.0, 5.0 ,.6} }"), mat10("{{-1.0, 0}, {1.0e3,0.001}}");
	printmatrix(mat1);
	printmatrix(mat2);
	printmatrix(mat3);
	printmatrix(mat4);
	printmatrix(mat5);
	printmatrix(mat6);
	printmatrix(mat7);
	printmatrix(mat8);
	printmatrix(mat9);
	printmatrix(mat10);
	matrix mat11 = mat9|mat10;
	printmatrix(mat11);
	matrix mat12 = mat8/mat9;
	printmatrix(mat12);
	matrix mat13 = mat10*mat9;
	printmatrix(mat13);
	mat10.set(2,1,0.9);
	printmatrix(mat10);
	cout << mat10.determinant(mat10) << endl;
	cout << mat6.determinant(mat6) << endl;
	cout << mat7.determinant(mat7) << endl;
	mat10 = ~mat10;
	mat10 = mat10;
	printmatrix(mat10);
	printmatrix(mat10+mat10);
	t = (mat10 == mat10);
	cout << t << endl;
	t = (mat10 != mat10);
	cout << t << endl;
	t = (mat8 == mat9);
	cout << t << endl;
	t = (mat8 != mat9);
	cout << t << endl;
	return 0;
}