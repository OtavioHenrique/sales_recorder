#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
void outputReport(Sale *sales, Product *products, int saleNumber, int numberLines);
Product findProduct(int productID, Product *products, int numberLines);
float finalPrice(Product product);

int monthDays = 2;

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

    Sale *sales = malloc(sizeof(Sale) * (monthDays * salesDay));
    int saleNumber = 0;

    for(int day = 1; day < monthDays; day++) {
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

    outputReport(sales, products, saleNumber, numberLines);

    fclose(file);
    free(products);
    free(sales);
}

Product findProduct(int productID, Product *products, int numberLines) {
	Product product = products[0];

	for(size_t i = 0; i <= numberLines; i++) {
	    if(product.productID == productID) {
	        return product;

		product = products[i+1];
            }
	}

	printf("Error, product %d doesn't exists on our database.\n", productID);
	product.productID = 0; //product with 0 ID is a null product
	return product;
}

void outputReport(Sale *sales, Product *products, int saleNumber, int numberLines) {
	FILE *file = fopen("final_report.csv", "w+");

	for(int day = 1; day < monthDays; day++) {
		for(int sale = 0; sale < saleNumber; sale++) {
			Product product = findProduct(sales[sale].product, products, numberLines);

			if (product.productID == 0) {
				fprintf(file, "%s %d %s\n", "Error product", sales[sale].product, "doesn't exists");
			} else {
				float price = finalPrice(product);

				fprintf(file, "%d;%d;%d;%d;%.4f;%.2f\n", sales[sale].year, sales[sale].month,
					sales[sale].day, product.productID, sales[sale].quantity, price);
			}
		}
	}

	fclose(file);
}

float finalPrice(Product product) {
	float price = product.cost * ((product.profit / 100) + 1 );

	srand(time(NULL));

	if ((rand() % 10 + 1) <= 30) {
		if ((rand() % 2 + 1) == 1) {
			price *= 1.3;
		} else {
			price -= (price * 0.3);
		}
	}

	return price;
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

    if ((file = fopen("PRODUTOS.txt","r")) == NULL) {
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
