#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void generate_random_numbers(int n) {
  FILE *fp;
  fp = fopen("random_numbers.txt", "w"); // open the random_numbers.txt file for writing
  
  if (fp != NULL) { // if file failed to open
    // loop n times, each time generating a random number between 0 and 99 and writing them to the random_numbers.txt file
    for (int i = 0; i < n; i++) { 
      int random_num = rand()%100;

      if (random_num >= 10) { // write 10's digit first if existing
	fputc((random_num/10)+'0', fp);
      }
      
      fputc((random_num % 10) + '0', fp); // write ones digit
      fputc('\n', fp); // write a new line
    }
    fclose(fp); // release file when finished
  } else { // error if file could not be opened
    printf("Error, file could not be opened.\n");
  }
}

void read_numbers(int *arr, int n) {
  FILE *fp;
  fp = fopen("random_numbers.txt", "r"); // open random_numbers.txt to read

  if (fp != NULL) {
    int ch; 
    int current_number=0;
    int count = 0;
    bool is_reading_number = false;
    // loop while there are numbers to read
    while ((ch = fgetc(fp)) != EOF && count < n) {
      if (ch >= '0' && ch <= '9') { // if current character is a digit, multiply current character by 10 and convert to integer
	current_number = (current_number*10) + (ch - '0');
	is_reading_number = true;
      } else if (ch == '\n') {
	if (is_reading_number) { // if last loop was a digit, that means it was a 10's column digit and this is single, so after multiplying current number by 10, add to count and go to next number
	  arr[count] = current_number;
	  count++;
	  current_number = 0;
	  is_reading_number = false;
	}
      }
    }
    // ensure all numbers have been read 
    if (is_reading_number && count < n) {
      arr[count] = current_number;
      count++;
    }
  } else {
    printf("Error, file could not be opened.\n");
  }
  fclose(fp); // release file from memory
}

double calculate_mean(int *arr, int n) {
  float sum=0;
  // sum all the numbers in the array
  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }
  // return sum / n for average (mean)
  return sum/n;
}

double calculate_median(int *arr, int n) {
  // Sort the numbers (using selection sort)
  for (int i = 0; i < n; i++) {
    int smallest_int = i;
    for (int j = i; j < n; j++) {
      if (arr[j] > arr[smallest_int]) {
	smallest_int = j;
      }
    }
    int temp = arr[smallest_int];
    arr[smallest_int] = arr[i];
    arr[i] = temp;
  }

  // for median, if n is even, take 2 middle numbers and return their mean
  if (n%2 == 0) {
    return (arr[(n/2)-1] + arr[n/2])/2.0;
  } else {
    // if n is odd, return middle number
    return arr[n/2];
  }
}

int calculate_mode(int *arr, int n) {
  int maxValue = 0, maxCount = 0;

  // using the now sorted array from calculating median, we can make a max count and count variable, and if two numbers are equal next to each other, then we increment the count by 1
  for (int i = 0; i < n; i++) {
    int count = 0;
    for (int j = 0; j < n; j++) {
      if (arr[j] == arr[i]) {
	count++;
      }
    }
    // if the current count is greater than the max count, replace the max count with current count
    if (count > maxCount) {
      maxCount = count;
      maxValue = arr[i];
    }
  }

  return maxValue;
}

void main(int argc, char *argv[]) {

  int n;
  // if the user entered an argument, then convert that to n and continue
  if (argc == 2) {
    n = atoi(argv[1]);
  } else if (argc > 2) { // if the user entered more than 2 arguments, error
    print("Must enter 1 or no arguments.");
    return;
  } else { // if the user entered in no arguments, prompt the user for n
    printf("Enter the number of random integers to generate: ");
    scanf("%d", &n);
  }
  
  // n must be within a reasonable range so 1-100, else error
  if (n <= 0 || n > 100) {
    printf("Amount of numbers must be between 1 and 100.\n");
    return;
  }

  // seed the random number generator using time
  srand(time(NULL));

  // generate the random numbers and the file first
  generate_random_numbers(n);
  // allocate memory for every n in the array
  int *arr = (int *) malloc(n * sizeof(int));
  // read back the generated numbers into the array
  read_numbers(arr, n);
  // calculate mean, median and mode using functions above
  double mean = calculate_mean(arr, n);
  double median = calculate_median(arr, n);
  int mode = calculate_mode(arr, n);

  // output mean, median and mode from function calls above
  printf("Mean: %.2f\n", mean);
  printf("Median: %.2f\n", median);
  printf("Mode: %d\n", mode);
  // free the reserved memory in the array for later usage
  free(arr);
}

