#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Retorna raiz inteira se for perfeita, senao -1
int raiz_perfeita(int n) {
    for (int i = 0; i*i <= n; i++) {
        if (i*i == n) return i;
    }
    return -1;
}

void extrair_coeficientes(char *entrada, int *a, int *b, int *c) {
    *a = 0; *b = 0; *c = 0;
    char *ptr = entrada;

    while (*ptr && *ptr != '=') {
        int sinal = 1;
        while (*ptr == ' ') ptr++;
        if (*ptr == '+') {
            sinal = 1;
            ptr++;
        } else if (*ptr == '-') {
            sinal = -1;
            ptr++;
        }

        while (*ptr == ' ') ptr++;

        int valor = 0;
        int tem_numero = 0;
        while (isdigit(*ptr)) {
            valor = valor * 10 + (*ptr - '0');
            ptr++;
            tem_numero = 1;
        }

        if (*ptr == 'x') {
            ptr++;
            if (*ptr == '^') {
                ptr++;
                if (*ptr == '2') {
                    *a = (tem_numero ? valor : 1) * sinal;
                    ptr++;
                }
            } else {
                *b = (tem_numero ? valor : 1) * sinal;
            }
        } else {
            *c += (tem_numero ? valor : 0) * sinal;
        }

        while (*ptr == ' ') ptr++;
    }
}

int main() {
    char entrada[100];
    int a = 0, b = 0, c = 0;

    printf("Digite a equacao no formato: ax^2 + bx + c = 0\n");
    fgets(entrada, sizeof(entrada), stdin);

    extrair_coeficientes(entrada, &a, &b, &c);

    if (a == 0 && b == 0) {
        printf("Grau: indeterminado | Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        system("pause");
        return 0;
    }

    if (a == 0) {
        printf("Grau: 1o grau | ");
        if (b != 0) {
            printf("Possui Solucao Real: Sim | Solucao: x=%d/%d\n", -c, b);
        } else {
            printf("Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        }
    } else {
        int delta = b * b - 4 * a * c;
        printf("Grau: 2o grau | ");
        if (delta < 0) {
            printf("Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        } else {
            int raiz = raiz_perfeita(delta);
            int divisor = 2 * a;
            printf("Possui Solucao Real: Sim | ");
            if (raiz != -1) {
                int x1 = (-b - raiz) / divisor;
                int x2 = (-b + raiz) / divisor;
                if (x1 == x2) {
                    printf("Solucao: x=%d\n", x1);
                } else {
                    printf("Solucao: x=%d, x=%d\n", x1, x2);
                }
            } else {
                printf("Solucao: x=(%d - sqrt(%d))/%d, x=(%d + sqrt(%d))/%d\n",
                       -b, delta, divisor, -b, delta, divisor);
            }
        }
    }

    system("pause");
    return 0;
}
 
