#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int main() {
  unsigned char buffer[10];

  FILE *prt;

  prt = fopen("test.bin", "rb");

  //fread(buffer, sizeof(buffer), 1, prt);
  fread(buffer, sizeof(char), sizeof(buffer)/sizeof(char), prt);

  char temp;
  for(int i = 0; i < 10; i ++) {
    //fread(&temp, sizeof(char), 1, prt);
    //printf("%x ", buffer[i]);
    printf("%x ", buffer[i]);
  }

  /* prt = fopen("test.bin", "wb"); */

  /* fwrite (buffer, sizeof(char), sizeof(buffer), prt); */

  /* fclose(prt); */

  /* return 0; */
}

//#include <iostream>
//#include <cstring>


// using std::cin;
// using std::string;

// bool have_all_char(string &S, string & T) {
//   bool fall[26];
//   for(int i = 0; i < 26; ++ i) {
//     fall[i] = false;
//   }
//   for(int i = 0; i < S.size(); ++ i) {
//     fall[S[i] - 'A'] = true;
//   }
//   for(int i = 0; i < T.size(); ++ i) {
//     if(!fall[T[i] - 'A']) return false;
//   }
//   return true;
// }

// int find_right(string & S, string & T) {
//   int i = 0;
//   while(i < S.size()) {
//     string temp = S.substr(0, i);
//     if(have_all_char(temp, T)) {
//       return i;
//     }
//     ++i;
//   }
//   return -1;
// }

// int find_left(string &S, string &T) {
//   int i = 0;
//   while(i < S.size()) {
//     string temp = S.substr(i, S.size() - 1);
//     if(!have_all_char(temp, T)) {
//       return i-1;
//     }
//     ++i;
//   }
// }

// int main() {
//   string S, T;

//   cin >> S >> T;

//   int right = find_right(S, T);
//   int left;
//   if(right == -1) {
//     printf("%s", "No");
//   }
//   else {
//     string s_r = S.substr(0, right);
//     left = find_left(S, T);
//     printf("%s", (S.substr(left, right)).c_str());
//   }
// }


//#include <stack>
//#include <queue>



// int gcd(int a, int b) {
//   if(a < b) {
//     return gcd(b, a);
//   }
//   else if(a > b) {
//     return gcd(a - b, b);
//   }
//   else {
//     return a;
//   }
// }

// int main() {
//   int a, b;
//   scanf("%d %d", &a, &b);

//   printf("%d", gcd(a, b));
// }

// bool check(int *a, int * b, int N) {
//   for(int i = 0; i < N; ++ i) {
//     if(a[i] != b[i]) {
//       return false;
//     }
//   }
//   return true;
// }

// int main() {
//   int N;

//   scanf("%d", &N);

//   int *array_before = (int*)malloc(sizeof(int)*N);
//   int *array_after = (int*)malloc(sizeof(int)*N);
//   int *temp = (int*)malloc(sizeof(int)*N);
//   std::stack<int> temp1;
//   std::queue<int> temp2;

//   for(int i = 0; i < N; ++ i) {
//     scanf("%d", array_before+i);
//   }
//   for(int i = 0; i < N; ++ i) {
//     scanf("%d", array_after+i);
//   }

//   for(int i = 0; i < N; ++ i) {
//     temp1.push(array_before[i]);
//   }

//   {
//     int i = 0;
//     while(!temp1.empty()) {
//       temp[i] = temp1.top();
//       temp1.pop();
//       ++i;
//     }
//   }

//   bool is_stack = false, is_queue = false;

//   is_stack = (check(temp, array_after, N));
//   is_queue = (check(array_after, array_before, N));

//   if(is_stack && is_queue) {
//     printf("both");
//   }
//   else if(is_stack) {
//     printf("stack");
//   }
//   else if(is_queue) {
//     printf("queue");
//   }
//   else {
//     printf("neither");
//   }

// }



/* int hash_list[100000000 + 1000]; */

/* int main() { */
/*   int N; */
/*   scanf("%d", &N); */

/*   int temp; */
/*   int max = INT_MIN; */
/*   for(int i = 0; i < N; ++ i) { */
/*     scanf("%d", &temp); */
/*     if(temp > max) { */
/*       max = temp; */
/*     } */
/*     hash_list[temp]++; */
/*   } */

/*   for(int i = 1; i < max; ++ i) { */
/*     if(hash_list[i] * 2 > N) { */
/*       printf("%d", i); */
/*     } */
/*   } */
/* } */

/* bool binary_searchable(int *array, int N, int index) {// array[index] binary_searchable? */
/*   int num = array[index]; */
/*   for(int i = 0; i < index; ++ i) { */
/*     if(num < array[i]) { */
/*       return false; */
/*     } */
/*   } */

/*   for(int i = index + 1; i < N; ++ i) { */
/*     if(num > array[i]) { */
/*       return false; */
/*     } */
/*   } */
/* } */

/* void solve(int *array, int N) { */
/*   int count = 0; */
/*   for(int i = 0; i < N; ++ i) { */
/*     if(binary_searchable(array, N, i)) { */
/*       count += 1; */
/*     } */
/*   } */

/*   printf("%d", count); */
/* } */

/* int main() { */
/*   int N; */
/*   int *array; */

/*   scanf("%d", &N); */
/*   array = (int*)malloc(sizeof(int)*N); */
/*   for(int i = 0; i < N; ++ i) { */
/*     scanf("%d", array+i); */
/*   } */

/*   solve(array, N); */
/* } */


/* int main() { */
/*   int *array, *sum; */
/*   int n; */
/*   scanf("%d", &n); */

/*   array = (int *)malloc(sizeof(int)*n); */
/*   sum = (int*)malloc(sizeof(int)*n); // sum from index 0 to i */

/*   for(int i = 0; i < n; ++ i) { */
/*     scanf("%d", array+i); */
/*   } */

/*   sum[0] = array[0]; */
/*   //printf("%d ", sum[0]); */
/*   for(int i = 1; i < n; ++ i) { */
/*     sum[i] = sum[i-1] + array[i]; */
/*     //printf("%d ", sum[i]); */
/*   } */

/*   int max = sum[0]; */
/*   for(int i = 0; i < n; ++ i) { */
/*     for(int j = i + 1; j < n; ++ j) { */
/*       if(sum[j] - sum[i] > max) { */
/*         max = sum[j] - sum[i]; */
/*       } */
/*     } */
/*   } */

/*   printf("%d", max); */
/* } */
