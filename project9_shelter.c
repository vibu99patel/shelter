/*
Vaibhavi Patel
this program reads animals from a data file (animals.txt)
it uses quick sort to sort the animals array by species and age 
prints it in the new (results.txt) file 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_animals (const void *a, const void *b);

// creating a structure 
struct animal_data {
    char name[101];
    char species[101];
    char gender[101];
    int age;
    double weight;
};

int main () {

    // declaring the variables 
    FILE *fp, *fp2;
    struct animal_data animal[200];
    int count = 0;
    
    // opening the file for reading the data 
    fp = fopen("animals.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file");
        return 1;
    }
    // reading from the file and storing it in the array 
    while (!feof(fp) && !ferror(fp)) {
        if ((fscanf(fp, "%s %s %s %d %lf", 
                    animal[count].name,
                    animal[count].species,
                    animal[count].gender,
                    &animal[count].age,
                    &animal[count].weight)) == 5) {
                        count++;
                    }
    }
    // closing the file 
    fclose(fp);

    // calling the qsort function to sort the array of animals 
    qsort(animal, count, sizeof(struct animal_data), compare_animals);

    // opening the new file to write the data
    fp2 = fopen("results.txt", "w");
    if (fp2 == NULL) {
        printf("Error opening the file");
        return 1;
    }

    // printing the sorted animals list in the output file 
    for (int i = 0; i < count; i++) {
        fprintf(fp2, "%s %d %s %.2lf %s\n", 
                animal[i].species,
                animal[i].age,
                animal[i].name,
                animal[i].weight,
                animal[i].gender);
    }

    // closing the file
    fclose(fp2);
    
    // display the message 
    printf("Output file name: results.txt");

    return 0;
}

// function definition 
int compare_animals (const void *a, const void *b) {
    // declaring the pointers 
    const struct animal_data *a1 = (const struct animal_data *)a;
    const struct animal_data *b1 = (const struct animal_data *)b;
    // comparing the species 
    int result = strcmp(a1->species, b1->species);
    if (result != 0) {
        return result;
    }
    // if species are same, comapring their age to sort the list 
    if (a1->age < b1->age) {
        return -1;
    }
    else if (a1->age > b1->age) {
        return 1;
    }
    else {
        return 0; 
    }
}
