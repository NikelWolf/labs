#ifndef UTILS_H
#define UTILS_H

typedef enum object_type_e { NUMBER,
                             OPERATOR,
                             ERROR,
                             END } object_type;
typedef enum operator_type_e { PLUS,
                               MINUS,
                               MULTIPLE,
                               DIVIDE,
                               EQUAL,
                               UNKNOWN } operator_type;

double get_number(const char *string, unsigned int *offset);
int is_operator(char c);
operator_type get_operator(const char *string, unsigned int *offset);
object_type get_object(const char *string, unsigned int *offset, double *operand_element, int *operator_element);

#endif
