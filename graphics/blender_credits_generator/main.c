/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: Ludo
 */


/*
 * main.c
 *
 *  Created on: 31 oct. 2021
 *      Author: Ludo
 */

#include "locale.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "wchar.h"

/*** MAIN macros ***/

#define BLENDER_TEXT_OBJECT_MAX_LENGTH			512
#define BLENDER_CREDIT_LINE_LENGTH				24
#define BLENDER_NUMBER_OF_LINE_PER_TEXT_OBJECT	(BLENDER_TEXT_OBJECT_MAX_LENGTH / BLENDER_CREDIT_LINE_LENGTH)
#define LINE_BUFFER_LENGTH						32
//#define DEBUG

/*** MAIN functions ***/

/* MAIN FUNCTION.
 * @param:	None.
 * @return:	None.
 */
int main(void) {
	// Set encoding.
	setlocale(LC_CTYPE, "fr_FR.utf8");
	// Local variables.
	wchar_t credit_line[LINE_BUFFER_LENGTH] = {0x00};
	unsigned int credit_line_idx = 0;
	unsigned int credit_line_char_idx = 0;
	unsigned int credit_line_length = 0;
	wchar_t blender_line[BLENDER_TEXT_OBJECT_MAX_LENGTH] = {0x00};
	unsigned int blender_subline_idx = 0;
	// Open files.
	FILE* credits_in = fopen("./credits.txt", "r");
	FILE* credits_out = fopen("./blender_lines.txt", "w+");
	// Check file pointers.
	if ((credits_in == NULL) || (credits_out == NULL)) {
		wprintf(L"Open files : error.\n");
	}
	else {
		wprintf(L"Open files : success.\n");
	}
	// Read input file.
	while (fgetws(credit_line, LINE_BUFFER_LENGTH, credits_in) != NULL) {
		// Get credit line.
		credit_line_idx++;
		// Check line length
		credit_line_length = wcslen(credit_line) - 1;
#ifdef DEBUG
		wprintf(L"%ls", credit_line);
		wprintf(L"[");
		unsigned int idx = 0;
		for (idx=0 ; idx<LINE_BUFFER_LENGTH ; idx++) {
			wprintf(L"%d ", (int) credit_line[idx]);
		}
		wprintf(L"]\n");
		wprintf(L"length = %d\n\n", credit_line_length);
#endif
		if (credit_line_length > (BLENDER_CREDIT_LINE_LENGTH - 1)) {
			wprintf(L"Error at line %d : length overflow\n", credit_line_idx);
			//goto errors;
		}
		// Replace cariage return and pad with spaces.
		for (credit_line_char_idx=0 ; credit_line_char_idx<LINE_BUFFER_LENGTH ; credit_line_char_idx++) {
			if ((credit_line[credit_line_char_idx] == '\n') || (credit_line[credit_line_char_idx] == '\r') || (credit_line[credit_line_char_idx] == '\0')) {
				credit_line[credit_line_char_idx] = ' ';
			}
			if (credit_line_char_idx > credit_line_length) {
				credit_line[credit_line_char_idx] = ' ';
			}
		}
		// Extract the line.
		for (credit_line_char_idx=0 ; credit_line_char_idx<(BLENDER_CREDIT_LINE_LENGTH) ; credit_line_char_idx++) {
			blender_line[(blender_subline_idx * BLENDER_CREDIT_LINE_LENGTH) + credit_line_char_idx] = credit_line[credit_line_char_idx];
		}
		// Manage sub-line index.
		blender_subline_idx++;
		if (blender_subline_idx >= BLENDER_NUMBER_OF_LINE_PER_TEXT_OBJECT) {
			// Write line in output file.
			wprintf(L"blender_line = %ls\n", blender_line);
			fputws(blender_line, credits_out);
			fputws(L"\n\n", credits_out);
			// Reset index.
			blender_subline_idx = 0;
		}
	}
errors:
	// Return
	return 0;
}
