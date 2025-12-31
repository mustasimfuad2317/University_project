#include <stdio.h>



void convard(){
    int choice;
    float value, result;

    printf("1. Meter to Centimeter        2. Centimeter to Meter\n");
    printf("3. Celsius to Fahrenheit      4. Fahrenheit to Celsius\n");
    printf("5. Kilogram to Gram           6. Gram to Kilogram\n");
    printf("7. Hour to Minute             8. Minute to Hour\n");
    printf("9. Km/hr to m/sec             10. m/sec to Km/hr\n\n");

    printf("Enter your choice (1-10): ");
    scanf("%d", &choice);

    printf("Enter the value: ");
    scanf("%f", &value);

    switch (choice) {
        case 1:
            result = value * 100;
            printf("Result = %.2f Centimeter\n", result);
            break;

        case 2:
            result = value / 100;
            printf("Result = %.2f Meter\n", result);
            break;

        case 3:
            result = (value * 9 / 5) + 32;
            printf("Result = %.2f Fahrenheit\n", result);
            break;

        case 4:
            result = (value - 32) * 5 / 9;
            printf("Result = %.2f Celsius\n", result);
            break;

        case 5:
            result = value * 1000;
            printf("Result = %.2f Gram\n", result);
            break;

        case 6:
            result = value / 1000;
            printf("Result = %.2f Kilogram\n", result);
            break;

        case 7:
            result = value * 60;
            printf("Result = %.2f Minute\n", result);
            break;

        case 8:
            result = value / 60;
            printf("Result = %.2f Hour\n", result);
            break;

        case 9:
            result = value * 1000 / 3600;
            printf("Result = %.2f m/sec\n", result);
            break;

        case 10:
            result = value * 3600 / 1000;
            printf("Result = %.2f Km/hr\n", result);
            break;

        default:
            printf("Invalid Choice!\n");
    }

}





// int main() {
//     int choice;
//     float value, result;

//     printf("1. Meter to Centimeter        2. Centimeter to Meter\n");
//     printf("3. Celsius to Fahrenheit      4. Fahrenheit to Celsius\n");
//     printf("5. Kilogram to Gram           6. Gram to Kilogram\n");
//     printf("7. Hour to Minute             8. Minute to Hour\n");
//     printf("9. Km/hr to m/sec             10. m/sec to Km/hr\n\n");

//     printf("Enter your choice (1-10): ");
//     scanf("%d", &choice);

//     printf("Enter the value: ");
//     scanf("%f", &value);

//     switch (choice) {
//         case 1:
//             result = value * 100;
//             printf("Result = %.2f Centimeter\n", result);
//             break;

//         case 2:
//             result = value / 100;
//             printf("Result = %.2f Meter\n", result);
//             break;

//         case 3:
//             result = (value * 9 / 5) + 32;
//             printf("Result = %.2f Fahrenheit\n", result);
//             break;

//         case 4:
//             result = (value - 32) * 5 / 9;
//             printf("Result = %.2f Celsius\n", result);
//             break;

//         case 5:
//             result = value * 1000;
//             printf("Result = %.2f Gram\n", result);
//             break;

//         case 6:
//             result = value / 1000;
//             printf("Result = %.2f Kilogram\n", result);
//             break;

//         case 7:
//             result = value * 60;
//             printf("Result = %.2f Minute\n", result);
//             break;

//         case 8:
//             result = value / 60;
//             printf("Result = %.2f Hour\n", result);
//             break;

//         case 9:
//             result = value * 1000 / 3600;
//             printf("Result = %.2f m/sec\n", result);
//             break;

//         case 10:
//             result = value * 3600 / 1000;
//             printf("Result = %.2f Km/hr\n", result);
//             break;

//         default:
//             printf("Invalid Choice!\n");
//     }

//     return 0;
// }
