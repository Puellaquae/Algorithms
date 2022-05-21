fn repeated_n_times(nums: Vec<i32>) -> i32 {
    let mut nums = nums;
    let n = nums.len();
    nums.sort_unstable();
    if nums[n / 2] == nums[n - 1] {
        nums[n / 2]
    } else {
        nums[n / 2 - 1]
    }
}

fn main() {
    assert_eq!(3, repeated_n_times(vec![1, 2, 3, 3]));
    assert_eq!(3, repeated_n_times(vec![5, 4, 3, 3]));
    assert_eq!(2, repeated_n_times(vec![2, 1, 2, 5, 3, 2]));
    assert_eq!(5, repeated_n_times(vec![5, 1, 5, 2, 5, 3, 5, 4]));
}
