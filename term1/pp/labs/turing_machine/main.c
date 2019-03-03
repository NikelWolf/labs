#define _GNU_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

typedef enum turing_machine_commands_e {MOVL, MOVR, INC, DEC, PRINT, GET, PRINTC, BEGIN, END, COMMENT, ERROR} turing_machine_command;

char *read_command_from_file(FILE *file) {
    char *line = "";
    char c;
    while(fread(&c, sizeof(char), 1, file) == 1 && !feof(file) && c != '\n') {
        if(!isspace(c)) asprintf(&line, "%s%c", line, c);
    }
    if(line[0] == '*') return "*";
    return line;
}

turing_machine_command get_command(const char *string_command) {
    if(!strcmp("movl", string_command)) {
        return MOVL;
    } else if(!strcmp("movr", string_command)) {
        return MOVR;
    } else if(!strcmp("inc", string_command)) {
        return INC;
    } else if(!strcmp("dec", string_command)) {
        return DEC;
    } else if(!strcmp("print", string_command)) {
        return PRINT;
    } else if(!strcmp("get", string_command)) {
        return GET;
    } else if(!strcmp("printc", string_command)) {
        return PRINTC;
    } else if(!strcmp("begin", string_command)) {
        return BEGIN;
    } else if(!strcmp("end", string_command)) {
        return END;
    } else if(!strcmp("*", string_command)) {
        return COMMENT;
    } else {
        return ERROR;
    }
}

void check_commands_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    if(file == NULL) {
        fprintf(stderr, "can not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    unsigned long int line_number = 0;
    char *string_command;
    int has_errors = 0;
    int closed_bracers = 0;
    turing_machine_command cmd = ERROR;
    while(!feof(file)) {
        line_number++;
        string_command = read_command_from_file(file);
        if((cmd = get_command(string_command)) == ERROR) {
            has_errors = 1;
            fprintf(stderr, "error on line %ld in file %s: unknnown command '%s'\n", line_number, filename, string_command);
        }
        if(cmd == BEGIN) {
            closed_bracers++;
        }
        if(cmd == END) {
            closed_bracers--;
        }
    }
    if(closed_bracers != 0) {
        fprintf(stderr, "cycles are not right created\n");
        has_errors = 1;
    }
    if(has_errors) {
        fclose(file);
        exit(EXIT_FAILURE);
    }
}

void create_actions(FILE *file) {
    fprintf(file,
                "#include <stdio.h>\n"
                "#include <stdlib.h>\n"
                "#include <string.h>\n"
                "#define DEFAUlT_SIZE 10\n"
                "#define RESIZING_COEFFICIENT 1.5\n"
                "typedef struct turing_tape_s { unsigned char *pos_array; unsigned char *neg_array; unsigned long int pos_size; unsigned long int neg_size; int sign; unsigned long int current_element; } turing_tape;\n"
                "void init_turing_tape(turing_tape *tape) { tape->pos_array = (unsigned char *) calloc(DEFAUlT_SIZE, sizeof(unsigned char)); tape->neg_array = (unsigned char *) calloc(DEFAUlT_SIZE, sizeof(unsigned char)); tape->sign = 1; tape->pos_size = DEFAUlT_SIZE; tape->neg_size = DEFAUlT_SIZE; tape->current_element = 0; }\n"
                "turing_tape *create_turing_tape() { turing_tape *tape = (turing_tape *) malloc(sizeof(turing_tape)); init_turing_tape(tape); return tape; }\n"
                "void free_turing_tape(turing_tape *tape) { if(tape->pos_array) free(tape->pos_array); if(tape->neg_array) free(tape->neg_array); if(tape) free(tape); }\n"
                "void resize_turing_tape(turing_tape *tape, int tape_type) { if(tape_type == 1) { char *tmp_array = (unsigned char *) calloc(tape->pos_size*RESIZING_COEFFICIENT, sizeof(unsigned char)); memcpy(tmp_array, tape->pos_array, tape->pos_size); free(tape->pos_array); tape->pos_array = tmp_array; tape->pos_size = tape->pos_size*RESIZING_COEFFICIENT; } else if(tape_type == -1) { char *tmp_array = (unsigned char *) calloc(tape->neg_size*RESIZING_COEFFICIENT, sizeof(unsigned char)); memcpy(tmp_array, tape->neg_array, tape->neg_size); free(tape->neg_array); tape->neg_array = tmp_array; tape->neg_size = tape->neg_size*RESIZING_COEFFICIENT; } }\n"
                "void print_turing_tape(turing_tape *tape) { unsigned int i; for(i = tape->neg_size; i > 0; i--) { printf(\"%%3d: %%d\\t\", -i, tape->neg_array[i-1]); } printf(\"\\n\"); for(i = 0; i < tape->pos_size; i++) { printf(\"%%3d: %%d\\t\", i, tape->pos_array[i]); } printf(\"\\n\\n\"); }\n"
                "void movl(turing_tape *tape) { if(tape->sign == 1) { if(tape->current_element == 0) { tape->sign = -1; } else { tape->current_element--; } } else if(tape->sign == -1) { if(tape->current_element == tape->neg_size-1) { resize_turing_tape(tape, tape->sign); tape->current_element++; } else { tape->current_element++; } } }\n"
                "void movr(turing_tape *tape) { if(tape->sign == 1) { if(tape->current_element == tape->pos_size-1) { resize_turing_tape(tape, tape->sign); tape->current_element++; } else { tape->current_element++; } } else if(tape->sign == -1) { if(tape->current_element == 0) { tape->sign = 1; } else { tape->current_element--; } } }\n"
                "void inc(turing_tape *tape) { if(tape->sign == 1) { tape->pos_array[tape->current_element]++; } else if(tape->sign == -1) { tape->neg_array[tape->current_element]++; } }\n"
                "void dec(turing_tape *tape) { if(tape->sign == 1) { tape->pos_array[tape->current_element]--; } else if(tape->sign == -1) { tape->neg_array[tape->current_element]--; } }\n"
                "void print(turing_tape *tape) { if(tape->sign == 1) { printf(\"%%u\", tape->pos_array[tape->current_element]); } else if(tape->sign == -1) { printf(\"%%u\",tape->neg_array[tape->current_element]); } }\n"
                "void get(turing_tape *tape) { if(tape->sign == 1) { tape->pos_array[tape->current_element] = getchar(); } else if(tape->sign == -1) { tape->neg_array[tape->current_element] = getchar(); } }\n"
                "char cur(turing_tape *tape) { if(tape->sign == 1) { return tape->pos_array[tape->current_element]; } else if(tape->sign == -1) { return tape->neg_array[tape->current_element]; } }\n"
                "void printc(turing_tape *tape) { if(tape->sign == 1) { printf(\"|%%c|\", tape->pos_array[tape->current_element]); } else if(tape->sign == -1) { printf(\"|%%c|\",tape->neg_array[tape->current_element]); } }\n"
    );
}

void create_output_file(const char *source_file_name, const char *output_file_name) {
    check_commands_file(source_file_name);

    FILE *input = fopen(source_file_name, "r");
    FILE *output = fopen(output_file_name, "w");

    if(input == NULL) {
        fprintf(stderr, "can not open source file: %s\n", source_file_name);
        exit(EXIT_FAILURE);
    }
    if(output == NULL) {
        fprintf(stderr, "can not open file for output: %s\n", output_file_name);
        exit(EXIT_FAILURE);
    }

    create_actions(output);
    fprintf(output, "int main(){");
    fprintf(output, "turing_tape *tape = create_turing_tape();");
    while(!feof(input)) {
        char *string_command = read_command_from_file(input);
        switch(get_command(string_command)) {
            case MOVL: {
                fprintf(output, "movl(tape);");
            }
            break;
            case MOVR: {
                fprintf(output, "movr(tape);");
            }
            break;
            case INC: {
                fprintf(output, "inc(tape);");
            }
            break;
            case DEC: {
                fprintf(output, "dec(tape);");
            }
            break;
            case PRINT: {
                fprintf(output, "print(tape);");
            }
            break;
            case GET: {
                fprintf(output, "get(tape);");
            }
            break;
            case PRINTC: {
                fprintf(output, "printc(tape);");
            }
            break;
            case BEGIN: {
                fprintf(output, "while(cur(tape)){");
            }
            break;
            case END: {
                fprintf(output, "}");
            }
            break;
            case COMMENT: {
                continue;
            }
            break;
            case ERROR: {
                fclose(input);
                fclose(output);
                fprintf(stderr, "unchecked error\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
    fprintf(output, "free_turing_tape(tape);return 0;}");
    fprintf(output, "\n");
    fclose(input);
    fclose(output);
}

void compile_output_file(const char *file, const char *name) {
    if(!fork()) {
        execlp("gcc", "gcc", "-o", name, file, NULL);
    } else {
        int status;
        wait(&status);
    }
}

void remove_file(const char *file_name) {
    remove(file_name);
}

void exec_program_and_remove_tmp(const char *program) {
    if(!fork()) {
        execlp(program, program, NULL);
    } else {
        sleep(1);
        
        remove_file("temporaly_file_for_turing_machine.c");
        remove_file("temporaly_program_for_turing_machine");

        int status;
        wait(&status);

    }
}

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "usage: turing_machine file_with_commands\n");
        exit(EXIT_SUCCESS);
    }
    enableRawMode();

    create_output_file(argv[1], "temporaly_file_for_turing_machine.c");
    compile_output_file("temporaly_file_for_turing_machine.c", "temporaly_program_for_turing_machine");
    exec_program_and_remove_tmp("./temporaly_program_for_turing_machine");
    printf("\n");

    return 0;
}
