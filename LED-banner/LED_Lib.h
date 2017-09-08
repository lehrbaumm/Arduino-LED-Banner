#pragma once
#ifndef LED_LIB_H
#define LED_LIN_H

#include "Alphabet.h"
#include "Numbers.h"
#include "Color.h"
#include "Specials.h"

void order(int Screen[7][60], int Ordered[7][60]) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 60; j++) {
			if (i % 2 == 0) {
				Ordered[i][j] = Screen[i][j];
			}
			else {
				Ordered[i][59 - j] = Screen[i][j];
			}
		}
	}
}

void set_segment(int* breite, int Screen[7][60], const int sign[7][5]) {
	for (int j = 0; j < 7; j++) {
		int k = 0;
		for (k = 0; k < 5; k++) {
			if (sign[j][k] == -1) {
				break;
			}
			int row = k + (*breite);
			Screen[j][row] = sign[j][k];
		}
		if (j == 6) {
			*breite += k + 1;
		}
	}

}

void special(int* breite, int Screen[7][60], char character) {
	int index = 4;
	switch (character)
	{
	case '!':
		index = 0;
		break;
	case '?':
		index = 1;
		break;
	case '.':
		index = 2;
		break;
	case ':':
		index = 3;
		break;
	case ' ':
		index = 4;
		break;
	case '"':
		index = 5;
		break;
	case '-':
		index = 6;
		break;
	case ']':
		index = 7;
		break;
	case '[':
		index = 8;
		break;
	case '(':
		index = 9;
		break;
	case ')':
		index = 10;
		break;
	case '+':
		index = 11;
		break;
	case '=':
		index = 12;
		break;
	case '^':
		index = 13;
		break;
	case '_':
		index = 14;
		break;
	default:
		break;
	}
	set_segment(breite, Screen, Specials[index]);
}

void generate_from_string(int Screen[7][60], char Output[10]) {
	int breite = 0;
	for (int i = 0; breite < 60; i++) {
		if (Output[i] == 0) {
      special(&breite, Screen, ' ');
      break;
		}
		if ((91 > Output[i] && 64 < Output[i]) || (123 > Output[i] && 96 < Output[i])) {
			int Char = -1;
			if (91 > Output[i] && 64 < Output[i]) {
				Char = Output[i] - 65;
			}
			if (123 > Output[i] && 96 < Output[i]) {
				Char = Output[i] - 97;
			}
			set_segment(&breite, Screen, Alphabet[Char]);
		}
		else if (58 > Output[i] && 47 < Output[i]) {
			int Number = Output[i] - 48;
			set_segment(&breite, Screen, Numbers[Number]);
		}
		else {
			special(&breite, Screen, Output[i]);
		}
	}
}


void move_right(int Screen[7][60]) {
	for (int i = 0; i < 7; i++) {
		int buffer = -1;
		int buffer2 = -1;
		for (int j = 0; j < 60; j++) {
			if (buffer == -1) {
				buffer = Screen[i][j + 1];
				Screen[i][j + 1] = Screen[i][j];
				j++;
			}
			else {
				buffer2 = Screen[i][j];
				Screen[i][j] = buffer;
				buffer = buffer2;
			}
		}
		Screen[i][0] = buffer;
	}
}

void move_left(int Screen[7][60]) {
	for (int i = 0; i < 7; i++) {
		int buffer = -1;
		int buffer2 = -1;
		for (int j = 59; j > -1; j--) {
			if (buffer == -1) {
				buffer = Screen[i][j - 1];
				Screen[i][j - 1] = Screen[i][j];
				j--;
			}
			else {
				buffer2 = Screen[i][j];
				Screen[i][j] = buffer;
				buffer = buffer2;
			}
		}
		Screen[i][59] = buffer;
	}
}
#endif // !LED_LIB_H

