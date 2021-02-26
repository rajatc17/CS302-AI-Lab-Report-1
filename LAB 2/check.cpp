#include <iostream>
#include <set>
#include <stack>

typedef std::pair<int, int> location_t;
typedef std::pair<location_t, location_t> jump_t;

bool p_solitaire_solve( bool array[7][7], int remaining, bool reset = true );
bool sol_found( bool array[7][7] );
bool is_valid( int i, int j );
void init( bool array[7][7] );
int p_count( bool array[7][7] );
void print_board( bool array[7][7] );
unsigned long int id_board( bool array[7][7] );
void print_jump( jump_t jump );

#define ENGLISH

#define FIRST_I 3
#define FIRST_J 3

#ifdef ENGLISH
	#define POINTS 33
	int points[POINTS][2] = {
		                {0, 2}, {0, 3}, {0, 4},
		                {1, 2}, {1, 3}, {1, 4},
		{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
		{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
		{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
		                {5, 2}, {5, 3}, {5, 4},
		                {6, 2}, {6, 3}, {6, 4}
	};

	#define LAST_I 3
	#define LAST_J 3
#else
	#define POINTS 37
	int points[POINTS][2] = {
		                {0, 2}, {0, 3}, {0, 4},
		        {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
		{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
		{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
		{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
		        {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5},
		                {6, 2}, {6, 3}, {6, 4}
	};

	#define LAST_I 2
	#define LAST_J 3
#endif

int main() {
	bool array[7][7];

	init( array );

	print_board( array );

	p_solitaire_solve( array, POINTS - 1 );

	print_board( array );

	return 0;
}

bool p_solitaire_solve( bool array[7][7], int remaining, bool reset ) {
	static std::set<unsigned long int> visited;
	static std::stack<jump_t> solution_trace;

	int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	if ( reset ) {
		visited.clear();
	}

	if ( remaining == 1 ) {
		return sol_found( array );
	}

	unsigned long int id = id_board( array );
	if ( visited.count( id ) > 0 ) {
		return false;
	}

	for ( int pt = 0; pt < POINTS; ++pt ) {
		int const i = points[pt][0];
		int const j = points[pt][1];

		if ( !array[i][j] ) {
			for ( int k = 0; k < 4; ++k ) {
				int const p = i + moves[k][0];
				int const q = j + moves[k][1];

				int const m = p + moves[k][0];
				int const n = q + moves[k][1];

				if ( is_valid( m, n ) && is_valid( p, q ) && array[m][n] && array[p][q] ) {
					array[m][n] = false;
					array[p][q] = false;
					array[i][j] = true;
					if ( p_solitaire_solve( array, remaining - 1, false ) ) {
						static int count = POINTS - 2;

						solution_trace.push( jump_t(
							location_t(m, n), location_t(i, j)
						) );

						--count;

						if ( count == 0 ) {
							std::cout << "Solution:" << std::endl;

							for ( int i = 1; i <= (POINTS - 2); ++i ) {
								std::cout << " " << i << ".\t";
								print_jump( solution_trace.top() );
								std::cout << std::endl;

								solution_trace.pop();
							}
						}


						return true;
					} else {
						array[m][n] = true;
						array[p][q] = true;
						array[i][j] = false;
					}
				}
			}
		}
	}

	visited.insert( id );

	return false;
}

unsigned long int id_board( bool array[7][7] ) {
	unsigned long int symmetry[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned long int mask = 1;

	for ( int i0 = 0; i0 <= 6; ++i0 ) {
		for ( int j0 = 0; j0 <= 6; ++j0 ) {
			int i1 = 6 - i0;
			int j1 = 6 - j0;

			if ( array[i0][j0] ) symmetry[0] |= mask;
			if ( array[i1][j0] ) symmetry[1] |= mask;
			if ( array[i1][j1] ) symmetry[2] |= mask;
			if ( array[i0][j1] ) symmetry[3] |= mask;
			if ( array[j0][i0] ) symmetry[4] |= mask;
			if ( array[j1][i0] ) symmetry[5] |= mask;
			if ( array[j1][i1] ) symmetry[6] |= mask;
			if ( array[j0][i1] ) symmetry[7] |= mask;

			mask <<= 1;
		}
	}

	unsigned long int representative = symmetry[0];

	for ( int i = 1; i < 8; ++i ) {
		if ( symmetry[i] < symmetry[0] ) {
			representative = symmetry[i];
		}
	}

	return representative;
}

void print_board( bool array[7][7] ) {
	std::cout << " ---------------" << std::endl;

	for ( int i = 0; i <= 6; ++i ) {
		std::cout << "| ";

		for ( int j = 0; j <= 6; ++j ) {
			if ( array[i][j] ) {
				std::cout << "x ";
			} else if ( is_valid( i, j ) ) {
				std::cout << "o ";
			} else {
				std::cout << "  ";
			}
		}

		std::cout << "|" << std::endl;
	}

	std::cout << " ---------------" << std::endl;
}

int p_count( bool array[7][7] ) {
	int c = 0;

	for ( int i = 0; i < POINTS; ++i ) {
		if ( array[points[i][0]][points[i][1]] ) {
			++c;
		}
	}

	return c;
}


void init( bool array[7][7] ) {
	for ( int i = 0; i <= 6; ++i ) {
		for ( int j = 0; j <= 6; ++j ) {
			array[i][j] = false;
		}
	}

	for ( int i = 0; i < POINTS; ++i ) {
		array[points[i][0]][points[i][1]] = true;
	}

	array[FIRST_I][FIRST_J] = false;
}


bool sol_found( bool array[7][7] ) {
	return array[LAST_I][LAST_J];
}



bool is_valid( int i, int j ) {
	return (i >= 0 && i <= 6) && (j >= 0 && j <= 6) && (
		(i >= 2 && i <= 4) || (j >= 2 && j <= 4)
#ifndef ENGLISH
		|| ((i >= 1 && i <= 5) && (j >= 1 && j <= 5))
#endif
	);
}

void print_jump( jump_t jump ) {
	std::cout << "Jump from ("
	          << jump.first.first << ","
	          << jump.first.second << ") to ("
	          << jump.second.first << ","
	          << jump.second.second << ")";
}
