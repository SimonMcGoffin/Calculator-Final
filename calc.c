#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

double degrees_to_radians(double degrees) {
    return degrees * (PI / 180.0);
}

double handle_unary(double num, char operator[]) {
    if (strcmp(operator, "sin") == 0) return sin(degrees_to_radians(num));
    if (strcmp(operator, "cos") == 0) return cos(degrees_to_radians(num));
    if (strcmp(operator, "tan") == 0) return tan(degrees_to_radians(num));
    if (strcmp(operator, "log") == 0) {
        if (num <= 0) {
            printf("Error: log undefined for non-positive values.\n");
            return NAN;
        }
        return log(num);
    }
    if (strcmp(operator, "log10") == 0) {
        if (num <= 0) {
            printf("Error: log10 undefined for non-positive values.\n");
            return NAN;
        }
        return log10(num);
    }

    printf("Error: Unsupported unary operation '%s'.\n", operator);
    return NAN;
}

double handle_binary(double num1, double num2, char operator[]) {
    if (strcmp(operator, "+") == 0) return num1 + num2;
    if (strcmp(operator, "-") == 0) return num1 - num2;
    if (strcmp(operator, "*") == 0) return num1 * num2;
    if (strcmp(operator, "/") == 0) {
        if (num2 == 0) {
            printf("Error: Division by zero.\n");
            return NAN;
        }
        return num1 / num2;
    }

    printf("Error: Unsupported binary operation '%s'.\n", operator);
    return NAN;
}

int main() {
    char line[100], operator[10], again;
    double num1, num2, result;

    printf("Welcome to the Final Command-Line Calculator!\n");
    printf("Supported binary ops: +, -, *, /\n");
    printf("Supported unary ops: sin, cos, tan, log, log10 (input in degrees)\n");

    do {
        printf("\nEnter expression (e.g., 5 + 3 or 45 sin): ");
        fgets(line, sizeof(line), stdin);

        int parsed = sscanf(line, "%lf %s %lf", &num1, operator, &num2);

        if (parsed == 3) {
            result = handle_binary(num1, num2, operator);
        } else if (parsed == 2) {
            result = handle_unary(num1, operator);
        } else {
            printf("Invalid input format. Use 'num1 op num2' or 'num op'.\n");
            continue;
        }

        if (!isnan(result)) {
            printf("Result: %.4lf\n", result);
        }

        printf("Another calculation? (y/n): ");
        again = getchar();
        while (getchar() != '\n'); // flush newline

    } while (again == 'y' || again == 'Y');

    printf("Goodbye!\n");
    return 0;
}
