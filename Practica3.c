#include "stdio.h"
#include "math.h"
#include "stdlib.h"

float stack[8];
float pi = 3.14159265359;

// Imprimir la pila
void printstack(void)
{
    printf("\nPila:\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", 8 - i);
        printf(". ");
        printf("%f", stack[i]);
        printf("\n");
    }
}

// Mover los elementos de la pila hacia arriba
void moveStackUp(void)
{
    for (int i = 1; i < 8; i++)
    {
        stack[i - 1] = stack[i];
    }
}

// Mover los elementos de la pila hacia abajo
void moveStackDown(void)
{
    for (int i = 7; i > 0; i--)
    {
        stack[i] = stack[i - 1];
    }
    stack[0] = 0;
}

// Agregar un valor a la pila
void push(float value)
{
    moveStackUp();
    stack[7] = value;
}

// Borrar todos los elementos
void delete(void)
{
    for (int i = 7; i > 0; i--)
    {
        stack[i] = 0;
    }
}

// Limpiar la consola
void clear(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Realizar la operacion
void operation(char op)
{
    clear();

    float a = stack[6];
    float b = stack[7];
    float result;

    switch (op)
    {
    case '+':
        result = a + b;
        break;

    case '-':
        result = a - b;
        break;

    case '*':
        result = a * b;
        break;

    case '/':
        if (b == 0)
        {
            printf("\nError: No se puede dividir por 0.\n");
            printstack();
            return;
        }
        result = a / b;
        break;

    case '^':
        result = pow(a, b);
        break;

    case 'r':
        if (b < 0)
        {
            printf("\nError: No es posible calcular la raiz cuadrada de un numero negativo.\n");
            printstack();
            return;
        }
        result = sqrt(b);
        break;

    case 's':
        result = sin(b * (pi / 180.0));
        break;

    case 'c':
        result = cos(b * (pi / 180.0));
        break;

    case 't':
        if (fmod(fabs(b), 180.0) == 90.0)
        {
            printf("\nError: Tangente indefinida en %f grados.\n", b);
            printstack();
            return;
        }
        result = tan(b * (pi / 180.0));
        break;

    default:
        printf("\nIngrese un valor de la lista\n");
        return;
    }

    if (op == 's' || op == 'c' || op == 't')
    {
        printf("\nResultado: %.2f\n", result);
        moveStackDown();
        push(result);
    }
    else
    {
        printf("\nResultado: %.2f\n", result);
        moveStackDown();
        stack[7] = result;
    }

    printstack();
}

int main()
{
    char eleccion;
    float numero;

    printstack();

    while (1)
    {

        printf("\nQué desea hacer?\n");
        printf("(1) Agregar numero a la pila\n");
        printf("(2) Realizar operacion (+, -, *, ...)\n");
        printf("(3) Eliminar ultimo\n");
        printf("(4) Eliminar todo\n");
        printf("(5) Salir\n");
        printf("Opción: ");
        scanf(" %c", &eleccion);

        switch (eleccion)
        {
        case '1':
            printf("\nIngrese el numero: ");
            scanf("%f", &numero);
            push(numero);
            clear();
            printstack();
            break;

        case '2':
            printf("Ingrese la operacion (+ , -, *, /, ^ (potencia), r (raiz cuadrada), s (seno), c (coseno), t (tangente)): ");
            scanf(" %c", &eleccion);
            operation(eleccion);
            break;

        case '3':
            moveStackDown();
            clear();
            printstack();
            break;

        case '4':
            delete ();
            clear();
            printstack();
            break;

        case '5':
            return 0;
        default:
            printf("\nSeleccione una opcion de la lista.\n");
        }
    }
    return 0;
}
