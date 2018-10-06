#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countLines(FILE *fp);
FILE* openFile();

typedef struct product {
    int productID;
    char type;
    float quantity;
    float cost;
    float profit;
} Product;

int main() {
    FILE *file = openFile();

    int numberLines = countLines(file);
    Product *products = malloc(sizeof(Product) * numberLines);

    char str1[50];
    char str2[50];
    char str3[50];
    char str4[50];
    char str5[50];

    for(int i = 0; i<numberLines; i++) {
        fscanf(file, " %[^;];%[^;];%[^;];%[^;];%[^;];", str1, str2, str3, str4, str5);
        products[i].productID = atoi(str1);
        products[i].type = str2[0];
        products[i].quantity = atof(str3);
        products[i].cost = atof(str4);
        products[i].profit = atof(str5);

        printf("%s %s %s %s %s\n", str1, str2, str3, str4, str5);
    }

    fclose(file);
    free(products);
}

FILE* openFile() {
	FILE *file;

    if ((file = fopen("product.txt","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

	return file;
}

int countLines(FILE *fp) {
    int count;
    char c;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count += 1;

    rewind(fp);
    return count;
}
