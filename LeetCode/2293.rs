pub fn min_max_game(nums: Vec<i32>) -> i32 {
    let mut nums = nums;
    while nums.len() > 1 {
        nums = nums
            .chunks(2)
            .enumerate()
            .map(|(idx, vs)| {
                if idx % 2 == 0 {
                    vs[0].min(vs[1])
                } else {
                    vs[0].max(vs[1])
                }
            })
            .collect();
    }
    nums[0]
}