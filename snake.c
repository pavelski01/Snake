#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define X_SIZE 70
#define Y_SIZE 22

typedef struct element {
	struct element* next;
	int Y_coord;
	int X_coord;
} new_one;

void empty_board(int board[Y_SIZE][X_SIZE]);
void display_board(int board[Y_SIZE][X_SIZE]);
new_one* create_snake(new_one* picket);
void initial_coordinates(new_one* picket, int board[Y_SIZE][X_SIZE]);
int steerage(int incoming_code, int outgoing_code, int set_of_control_codes[8]);
bool motor(new_one* picket, int board[Y_SIZE][X_SIZE], int map[Y_SIZE][X_SIZE], int* current_course, int point[2]);
void time_interval(unsigned int seconds);
int read_character();
bool punctuate(int point[2], int board[Y_SIZE][X_SIZE]);
bool check_it(int point[2]);

int main(void) {
	int bd[Y_SIZE][X_SIZE];
	int mp[Y_SIZE][X_SIZE];
	int pt_coord[2];
	new_one* pckt = (new_one*)malloc(sizeof(new_one));
	int* new_course = (int*)malloc(sizeof(int));
	int* current_course = (int*)malloc(sizeof(int));
	*current_course = 1;
	int* result = (int*)malloc(sizeof(int));
	*result = 0;
	int steerage_ascii_to_int[8] = { 65, 68, 83, 87, 97, 100, 115, 119 }; //A, D, S, W, a, d, s, w
	int counter;
	bool move = true;
	srand(time(NULL));
	empty_board(bd);
	empty_board(mp);
	szp = create_snake(pckt);  
	initial_coordinates(pckt, bd);
	punctuate(pt_coord, bd);
	display_board(bd);
	printf("Steerage: W - up, S - down, A - left, D - right\n");
	system("PAUSE");
	do {
		if (kbhit()) *new_course = read_character();           
		*current_course = steerage(*new_course, *current_course, steerage_ascii_to_int);
		if ( (*result) < 1000) sleep(750);
		empty_board(bd);
		move = motor(pckt, bd, mp, current_course, pt_coord);
		if ( !check_it(pt_coord) ) {
			while( !punctuate(pt_coord, bd) );
			*result += 1000;
		}
		system("CLS");
		display_board(bd);
		printf("scoring: %d", *result);
	} while (move);
	system("CLS");
	printf("\n\n\n\n\n\n\t\t\t\tGAME OVER\n\n\n\n\n\n\n\n\n\n\n");
	system("PAUSE");      
	exit(0);
}

void empty_board(int board[Y_SIZE][X_SIZE]) {   
	int i, j;
	for (j = 0; j < Y_SIZE; j++) for (i = 0; i < X_SIZE; i++) {
		if ( ( i == 0 ) || ( i == (X_SIZE-1) ) || ( j == 0 ) || ( j == (Y_SIZE-1) ) ) board[j][i] = 1;
		else board[j][i] = 0;
	}
}

void display_board(int board[Y_SIZE][X_SIZE]) {
	int i, j;
	char board_to_char[Y_SIZE][X_SIZE];
	for (j = 0; j < Y_SIZE; j++) for (i = 0; i < X_SIZE; i++) {
		if (board[j][i] == 0) {
			board_to_char[j][i] = ' ';
			printf("%c", board_to_char[j][i]);
		} 
		else if (board[j][i] == 1) {
			board_to_char[j][i] = 'X';
			printf("%c", board_to_char[j][i]);
		}
		else if (board[j][i] == 2) {
			board_to_char[j][i] = '@';
			printf("%c", board_to_char[j][i]);
		}
		else if (board[j][i] == 3) {
			board_to_char[j][i] = 'O';
			printf("%c", board_to_char[j][i]);
		}
		else if (board[j][i] == 4) {
			board_to_char[j][i] = '*';
			printf("%c", board_to_char[j][i]);
		}
	}
	printf("\n");   
}

new_one* create_snake(new_one* picket) {
	new_one* following;
	int counter;
	picket -> Y_coord = Y_SIZE/2;
	picket -> X_coord = X_SIZE/4;           
	following = picket;
	for (counter = 1; counter < 6; counter++) {
		following -> next = (new_one*)malloc(sizeof(new_one));
		following = following -> next;
		following -> X_coord = (X_SIZE/4 - counter);
		following -> Y_coord = Y_SIZE/2;
	}
	following -> next = NULL;
	return picket;
}

void initial_coordinates(new_one* picket, int board[Y_SIZE][X_SIZE]) {
	new_one* following = picket;
	board[picket -> Y_coord][picket -> X_coord] = 2;
	following = picket -> next;
	board[picket -> Y_coord][following -> X_coord] = 3;
	board[picket -> Y_coord][following -> next -> X_coord] = 3;
	board[picket -> Y_coord][following -> next -> next -> X_coord] = 3;
	board[picket -> Y_coord][following -> next -> next -> next -> X_coord] = 3;
	board[picket -> Y_coord][following -> next -> next -> next -> next -> X_coord] = 3;
	following -> next -> next -> next -> next -> next = NULL;     
}

int steerage(int incoming_code, int outgoing_code, int set_of_control_codes[8]) {
	int counter;
	for (counter = 0; counter <= 8; counter++) {
		if ( incoming_code == set_of_control_codes[counter] ) {
			if ( ( ( incoming_code == 65 ) || ( incoming_code == 97 ) ) ) {
				if ( (outgoing_code != 1) ) {
					outgoing_code = 0;
					break;
				}
				else {
					outgoing_code = 1;
					break;
				}
			}
			else if ( ( incoming_code == 68 ) || ( incoming_code == 100 ) ) {
				if ( (outgoing_code != 0) ) {
					outgoing_code = 1;
					break;
				}
				else {
					outgoing_code = 0;
					break;
				}
			}
			else if ( ( incoming_code == 83 ) || ( incoming_code == 115 ) ) {
				if ( (outgoing_code != 3) ) {
					outgoing_code = 2;
					break;
				}
				else {
					outgoing_code = 3;
					break;
				};
			}
			else if ( ( incoming_code == 87 ) || ( incoming_code == 119 ) ) {
				if ( (outgoing_code != 2) ) {
					outgoing_code = 3;
					break;
				}
				else {
					outgoing_code = 2;
					break;
				};
			}
		}         
	}
	return outgoing_code;
}

bool motor(new_one* picket, int board[Y_SIZE][X_SIZE], int map[Y_SIZE][X_SIZE], int* current_course, int point[2]) {
	new_one* following = picket;
	new_one* attach = NULL;
	int scanner = 0;
	int old_coords[2];
	int new_coords[2]; 
	int i, j;
	board[ (1 + point[0]) ][ (1 + point[1]) ] = 4;
	switch (*current_course) {
		case 0:
			{
				if ( map[picket -> Y_coord][(picket -> X_coord) - 1] == 4 ) attach = (new_one*)malloc(sizeof(new_one));
				else if ( !( ( map[picket -> Y_coord][(picket -> X_coord) - 1] == 0 ) || ( map[picket -> Y_coord][(picket -> X_coord) - 1] == 4 ) ) ) scanner = (-1);
				new_coords[0] = picket -> Y_coord;
				new_coords[1] = picket -> X_coord;
				picket -> Y_coord = picket -> Y_coord;
				picket -> X_coord = (picket -> X_coord) - 1;
				board[picket -> Y_coord][picket -> X_coord] = 2;
				following = picket;
				while ( following -> next != NULL ) {
					following = following -> next;
					old_coords[0] = following -> Y_coord;
					old_coords[1] = following -> X_coord;
					following -> Y_coord = new_coords[0];
					following -> X_coord = new_coords[1];
					board[following -> Y_coord][following -> X_coord] = 3;
					new_coords[0] = old_coords[0];
					new_coords[1] = old_coords[1];
				}
				if (attach != NULL) {
					following -> next = attach;
					attach -> Y_coord = new_coords[0];
					attach -> X_coord = new_coords[1];
					board[attach -> Y_coord][attach -> X_coord] = 3;
					following = attach;
					following -> next = NULL;
					point[0] = (-1);
					point[1] = (-1);
				}
				break;
			}
		case 1:
			{
				if ( map[picket -> Y_coord][(picket -> X_coord) + 1] == 4 ) attach = (new_one *)malloc(sizeof(new_one));         
				else if ( !( ( map[picket -> Y_coord][(picket -> X_coord) + 1] == 0 ) || ( map[picket -> Y_coord][(picket -> X_coord) + 1] == 4 ) ) ) scanner = (-1);
				new_coords[0] = picket -> Y_coord;
				new_coords[1] = picket -> X_coord;
				picket -> Y_coord = picket -> Y_coord;
				picket -> X_coord = (picket -> X_coord) + 1;
				board[picket -> Y_coord][picket -> X_coord] = 2;
				following = picket;
				while ( following -> next != NULL ) {
					following = following -> next;
					old_coords[0] = following -> Y_coord;
					old_coords[1] = following -> X_coord;
					following -> Y_coord = new_coords[0];
					following -> X_coord = new_coords[1];
					board[following -> Y_coord][following -> X_coord] = 3;
					new_coords[0] = old_coords[0];
					new_coords[1] = old_coords[1]; 
				}
				if (attach != NULL) {
					following -> next = attach;
					attach -> Y_coord = new_coords[0];
					attach -> X_coord = new_coords[1];
					board[attach -> Y_coord][attach -> X_coord] = 3;
					following = attach;
					following -> next = NULL;
					point[0] = (-1);
					point[1] = (-1);
				}
				break;
			}     
		case 2:
			{
				if ( map[(picket -> Y_coord) + 1][picket -> X_coord] == 4 ) attach = (new_one*)malloc(sizeof(new_one));
				else if ( !( ( map[(picket -> Y_coord) + 1][picket -> X_coord] == 0 ) || ( map[(picket -> Y_coord) + 1][picket -> X_coord] == 4 ) ) ) scanner = (-1);
				new_coords[0] = picket -> Y_coord;
				new_coords[1] = picket -> X_coord;
				picket -> Y_coord = (picket -> Y_coord) + 1;
				picket -> X_coord = picket -> X_coord;
				board[picket -> Y_coord][picket -> X_coord] = 2;
				following = picket;
				while ( following -> next != NULL ) {
					following = following -> next;
					old_coords[0] = following -> Y_coord;
					old_coords[1] = following -> X_coord;
					following -> Y_coord = new_coords[0];
					following -> X_coord = new_coords[1];
					board[following -> Y_coord][following -> X_coord] = 3;
					new_coords[0] = old_coords[0];
					new_coords[1] = old_coords[1];
				}
				if (attach != NULL) {
					following -> next = attach;
					attach -> Y_coord = new_coords[0];
					attach -> X_coord = new_coords[1];
					board[attach -> Y_coord][attach -> X_coord] = 3;
					following = attach;
					following -> next = NULL;
					point[0] = (-1);
					point[1] = (-1);
				}
				break;
			}
		case 3:
			{
				if ( map[(picket -> Y_coord) - 1][picket -> X_coord] == 4 ) attach = (new_one*)malloc(sizeof(new_one));          
				else if ( !( ( map[(picket -> Y_coord) - 1][picket -> X_coord] == 0 ) || ( map[(picket -> Y_coord) - 1][picket -> X_coord] == 4 ) ) ) scanner = (-1);
				new_coords[0] = picket -> Y_coord;
				new_coords[1] = picket -> X_coord;             
				picket -> Y_coord = (picket -> Y_coord) - 1;
				picket -> X_coord = picket -> X_coord;
				board[picket -> Y_coord][picket -> X_coord] = 2;              
				following = picket;         
				while ( following -> next != NULL ) {
					following = following -> next;
					old_coords[0] = following -> Y_coord;
					old_coords[1] = following -> X_coord;
					following -> Y_coord = new_coords[0];
					following -> X_coord = new_coords[1];
					board[following -> Y_coord][following -> X_coord] = 3;
					new_coords[0] = old_coords[0];
					new_coords[1] = old_coords[1];                     
				}               
				if (attach != NULL) {
					following -> next = attach;
					attach -> Y_coord = new_coords[0];
					attach -> X_coord = new_coords[1];
					board[attach -> Y_coord][attach -> X_coord] = 3;
					following = attach;
					following -> next = NULL;
					point[0] = (-1);
					point[1] = (-1);
				}
				break;
			}
		}
	for (j = 0; j < Y_SIZE; j++) for (i = 0; i < X_SIZE; i++) map[j][i] = 0;
	for (j = 0; j < Y_SIZE; j++) for (i = 0; i < X_SIZE; i++) map[j][i] = board[j][i];
	following = picket;
	while (following -> next != NULL) following = following -> next;
	map[ following -> Y_coord ][ following -> X_coord ] = 0;     
	if (scanner != 0) return false;
	else return true;
}

void time_interval(unsigned int seconds) {
	int specified_time;
	specified_time = time(0) + seconds;
	while (time(0) < specified_time);
}

int read_character() {
	int outgoing_code = getch();
	return outgoing_code;
}

bool punctuate(int point[2], int board[Y_SIZE][X_SIZE]) {           
	int Y_coord = rand() % (Y_SIZE - 2);
	int X_coord = rand() % (X_SIZE - 2);
	if (board[1 + Y_coord][1 + X_coord] != 0) return false;
	else {
		point[0] = Y_coord;
		point[1] = X_coord;
		board[ (1 + point[0]) ][ (1 + point[1]) ] = 4;
		return true;
	}
}

bool check_it(int point[2]) {
	if ( (point[0] == (-1) ) || (point[1] == (-1) ) ) return false;
	else return true;
}
