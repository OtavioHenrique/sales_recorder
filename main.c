#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sale {
	int year;
	int month;
	int day;
	int product;
	float quantity;
} Sale;

typedef struct product {
    int productID;
    char type;
    float quantity;
    float cost;
    float profit;
} Product;

int countLines(FILE *fp);
FILE* openFile();
void populateProducts(FILE *file,int numberLines, Product *products);
void printStructs();
void registrySale(Sale *sales, int saleNumber,int year, int month, int day, int product, float quantity);

int main() {
    FILE *file = openFile();

    int numberLines = countLines(file);
    Product *products = malloc(sizeof(Product) * numberLines);
	populateProducts(file, numberLines, products);

	int year = 0, month = 0, salesDay = 0;

	printf("Please, enter with report year: ");
	while(year <= 2016)
		scanf("%d", &year);

	printf("Please, enter with report month: ");
	while(month > 12 || month <= 0)
		scanf("%d", &month);

	printf("Please, enter with sales/day quantity: ");
	scanf("%d", &salesDay);

	Sale *sales = malloc(sizeof(Sale) * (30 * salesDay));
	int saleNumber = 0;

	for(int day = 1; day < 30; day++) {
		printf("Sales of %d/%d/%d\n\n", year, month, day);

		for(int sale = 0; sale < salesDay; sale++) {
			int product;
			float quantity;

			printf("Sale n %d\n", sale+1);

			printf("Product ID: ");
			scanf("%d", &product);

			printf("Quantity: ");
			scanf("%f", &quantity);

			registrySale(sales, saleNumber, year, month, day, product, quantity);
			saleNumber++;
		}
	}

	printStructs(products);

    fclose(file);
    free(products);
	free(sales);
}

void registrySale(Sale *sales, int saleNumber, int year, int month, int day, int product, float quantity) {
	sales[saleNumber].product = product;
	sales[saleNumber].quantity = quantity;
    sales[saleNumber].year = year;
	sales[saleNumber].month = month;
	sales[saleNumber].day = day;
}

void printStructs(Product *products) {
	for(int i=0; i<4; i++) {
		printf("%d | ", products[i].productID);
		printf("%c | ", products[i].type);
		printf("%f | ", products[i].quantity);
		printf("%f | ", products[i].cost);
		printf("%f | \n", products[i].profit);
	}
}

FILE* openFile() {
	FILE *file;

    if ((file = fopen("product.txt","r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

	return file;
}

int countLines(FILE *fp) {
    int count = 0;
    char c;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count += 1;

    rewind(fp);
    return count;
}

void populateProducts(FILE *file, int numberLines, Product *products) {
	char str1[50];
    char str2[50];
    char str3[50];
    char str4[50];
    char str5[50];

    for(int i = 0; i < numberLines-1; i++) {
        fscanf(file, " %[^;];%[^;];%[^;];%[^;];%[^;];", str1, str2, str3, str4, str5);
        products[i].productID = atoi(str1);
        products[i].type = str2[0];
        products[i].quantity = atof(str3);
        products[i].cost = atof(str4);
        products[i].profit = atof(str5);
    }
}

