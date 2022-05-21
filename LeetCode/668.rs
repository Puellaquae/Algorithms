fn find_kth_number(m: i32, n: i32, k: i32) -> i32 {
    let mut left = 1;
    let mut right = m * n;
    while left < right {
        let mid = left + (right - left) / 2;
        let mut count = mid / n * n;
        for i in (mid / n + 1)..=m {
            count += mid / i
        }
        if count >= k {
            right = mid;
        } else {
            left = mid + 1;
        }   
    }
    left
}

fn main() {
    assert_eq!(3, find_kth_number(3, 3, 5));
    assert_eq!(6, find_kth_number(2, 3, 6));
    println!("{}", find_kth_number(9895, 28405, 100787757));
}