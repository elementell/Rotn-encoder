#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char *rotate(int rotAmnt, char *input) {
	char *output = malloc(strlen(input) * sizeof(char));
	
	int i;
	char o;
	for (i = 0; i < strlen(input); i++) {
		if (input[i] > 96 && input[i] < 124) {
			o = (input[i] + rotAmnt) % (26 + 'a');
			if (o < 97)
				o += 'a';
		} else if (input[i] > 64 && input[i] < 91) {
			o = (input[i] + rotAmnt) % (26 + 'A');
			if (o < 65)
				o += 'A';
		} else {
			o = input[i];
		}
		output[i] = o;
	}
	output[i] = '\0';
	return output;
}
char *readFile(char *path) {
	char *output = malloc(1000 * sizeof(char));
	_IO_FILE *infile = fopen(path, "r");
	if (infile == NULL) {
		fprintf(stderr, "Error: %s\n", strerror( errno ));
		exit(1);
	}
	int ch;
	int i = 0;
	while ((ch = getc(infile)) != EOF) {
		output[i] = ch;
		++i;
	}
	return output;

}
char *readInput() {
	char *output = malloc(100 * sizeof(char));
	char ch[1];
	int i = 0;
	while (read(STDIN_FILENO, ch, 1) > 0) {
		output[i] = ch[0];
		++i;
		if (ch[0] = 0)
			break;
	}
	return output;
}
void writeOutput(char *path, char *output) {
	_IO_FILE *outfile = fopen(path, "w");
	if (outfile == NULL) {
		fprintf(stderr, "Error: %s\n", strerror( errno ));
		exit(1);
	}
	int i;
	for(i = 0; i < strlen(output); i++) {
		putc(output[i],outfile);
	}
}
int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("%s \n", rotate(13,readInput()));
	}
	else if (argc == 2) {
		if (argv[1][0] == '-') {
			int rotAmnt;
			if (strlen(argv[1]) == 3) {
				rotAmnt = (argv[1][1] - '0') * 10;
				rotAmnt += argv[1][2] - '0';
			}
			else if (strlen(argv[1]) == 2)
				rotAmnt = argv[1][1] - '0';

			printf("%s \n", rotate(rotAmnt,readInput()));
			
		} else
			printf("%s \n", rotate(13,readFile(argv[1])));
		
	}
	else if (argc == 3) {
		if (argv[1][0] == '-') {
			int rotAmnt;
			if (strlen(argv[1]) == 3) {
				rotAmnt = argv[1][1] - '0' + 9;
				rotAmnt += argv[1][2] - '0';
			} else if (strlen(argv[1]) == 2)
				rotAmnt = argv[1][1] - '0';

			printf("%s \n", rotate(rotAmnt,readFile(argv[2])));
			
		} else {
			writeOutput(argv[2],rotate(13,readFile(argv[1])));
		}
	}
	else if (argc == 4) {
		int rotAmnt;
		if (strlen(argv[1]) == 3) {
			rotAmnt = argv[1][1] - '0' + 9;
			rotAmnt += argv[1][2] - '0';
		} else if (strlen(argv[1]) == 2)
			rotAmnt = argv[1][1] - '0';

		writeOutput(argv[3],rotate(rotAmnt,readFile(argv[2])));
	}
	else {
		printf("You used too many or too little arguments; you should try harder next time. \nRefer to the man page for rotn for more information (if this were actually a unix command)\n");
	}
	if (errno != 0)	
		fprintf(stderr, "Error: %s\n", strerror( errno ));
	return 0;
}
