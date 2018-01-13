/*
  increment all but one <=> decrement one, so how many steps to decrement all to equal, minimum?
  sum(array) - length * min
 */

int minMoves(int* nums, int numsSize) {
  int min = INT_MAX;
  int sum = 0;

  for(int i = 0; i < numsSize; ++ i) {
    sum += nums[i];
    if(min > nums[i]) {
      min = nums[i];
    }
  }

  return sum - numsSize * min;
}
