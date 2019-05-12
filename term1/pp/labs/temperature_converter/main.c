#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum degrees_systems { CESL,
                       FAHR,
                       KELV,
                       NONE };

int is_number(const char *string) {
    while (*string) {
        if (!isdigit(*string) && *string != '.' && *string != '-') {
            return 0;
        } else {
            string++;
        }
    }
    return 1;
}

int iscfksys(const char *string) {
    if (strlen(string) > 1 || (tolower(*string) != 'c' && tolower(*string) != 'k' && tolower(*string) != 'f')) {
        return 0;
    } else {
        return 1;
    }
}

double parse_double(const char *string) {
    return strtod(string, (char **)NULL);
}

double convctof(double degrees_cels) {
    return degrees_cels * (9.0 / 5.0) + 32;
}

double convctok(double degrees_cels) {
    return degrees_cels + 273.15;
}

double convftoc(double degrees_fahr) {
    return (degrees_fahr - 32) * (5.0 / 9.0);
}

double convftok(double degrees_fahr) {
    return convctok(convftoc(degrees_fahr));
}

double convktoc(double degrees_kelv) {
    return degrees_kelv - 273.15;
}

double convktof(double degrees_kelv) {
    return convctof(convktoc(degrees_kelv));
}

int is_less_than_kelvin_zero(const char *string, enum degrees_systems type) {
    double value = parse_double(string);
    switch (type) {
    case CESL:
        value = convctok(value);
        break;
    case FAHR:
        value = convftok(value);
        break;
    case KELV:
        break;
    default:
        value = convctok(value);
        break;
    }

    return value < 0 ? 1 : 0;
}

void print_degrees(double degrees, enum degrees_systems type) {
    switch (type) {
    case CESL: {
        printf("%.2f F\n%.2f K\n", convctof(degrees), convctok(degrees));
        break;
    }
    case FAHR: {
        printf("%.2f C\n%.2f K\n", convftoc(degrees), convftok(degrees));
        break;
    }
    case KELV: {
        printf("%.2f C\n%.2f F\n", convktoc(degrees), convktof(degrees));
        break;
    }
    default: {
        printf("%.2f C\n%.2f F\n%.2f K\n", degrees, convctof(degrees), convctok(degrees));
        break;
    }
    }
}

enum degrees_systems get_degrees_type(const char *cmdarg) {
    return tolower(cmdarg[0]) == 'c' ? CESL : tolower(cmdarg[0]) == 'f' ? FAHR : tolower(cmdarg[0]) == 'k' ? KELV : NONE;
}

int main(int argc, char *argv[]) {
    switch (argc) {
    case 2: {
        if (!is_number(argv[1])) {
            fprintf(stderr, "invalid not number argument: %s\n", argv[1]);
            return 2;
        } else if (is_less_than_kelvin_zero(argv[1], get_degrees_type("c"))) {
            fprintf(stderr, "invalid number less that zero in Kelvin system: %s C\n", argv[1]);
            return 3;
        } else {
            print_degrees(parse_double(argv[1]), NONE);
        }
    } break;
    case 3: {
        if (!is_number(argv[1])) {
            fprintf(stderr, "invalid not number argument: %s\n", argv[1]);
            return 2;
        } else if (is_less_than_kelvin_zero(argv[1], get_degrees_type(argv[2]))) {
            fprintf(stderr, "invalid number less that zero in Kelvin system: %s %c\n", argv[1], toupper(argv[2][0]));
            return 3;
        } else if (!iscfksys(argv[2])) {
            fprintf(stderr, "invalid system type argument: %s\n", argv[2]);
            return 4;
        } else {
            print_degrees(parse_double(argv[1]), get_degrees_type(argv[2]));
        }
    } break;
    default: {
        fprintf(stderr, "usage: tconvert degrees [type]\n");
        return 1;
    } break;
    }

    return 0;
}
