/*
  suppose at index of i, m refers to array[i], n is last index of array
  1. if i + m exceeds n, return 1
  2. search in M(index from (i+1) to (i+m)), the largest (index + jump_length), call it j
  3. recursive call f(array, j, n)

  Need to be careful of array with size of 1
 */


int recur_sol(int *nums, int i, int n) {
  int m = nums[i];
  if(i + m >= n) {
    return 1;
  }

  int max = -1;
  int max_index = -1;
  int j;
  for(j = i+1; j <= i+m; ++ j) {
    if(max < j + nums[j]) {
      max_index = j;
      max = nums[j] + j;
    }
  }

  return 1 + recur_sol(nums, max_index, n);
}

int jump(int* nums, int numsSize) {
  if(numsSize == 1) {
    return 0;
  }
  return recur_sol(nums, 0, numsSize-1);
}
