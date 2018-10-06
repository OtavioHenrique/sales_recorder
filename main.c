#include <stdio.h>
#include <stdlib.h>

int countLines(FILE *fp);

struct product {
    int productID;
    char type;
    float quantity;
    float cost;
    float profit;
};

int main() {
    FILE *file;
//    struct product input;

    if ((file = fopen("product.txt","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    int numberLines = countLines(file);

    printf("%d", numberLines);

/*    while(fread(&input, sizeof(struct product), 1, file)) {*/
        /*fscanf(file, "%d", &abc);*/
        /*printf("%d", abc);*/
        //fscanf(file, "%d;%c;%f;%f;%f", &input.productID, &input.type, &input.quantity, &input.cost, &input.profit);

    /*printf("id = %d type = %c quantity =  %f cost = %f profit = %f\n", input.productID,*/
        /*input.type, input.quantity, input.cost, input.profit);*/


    fclose(file);
}

int countLines(FILE *fp) {
    int count;
    char c;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count = count + 1;

    rewind(fp);
    return count;
}
