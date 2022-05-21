struct CQueue {
    stack_in: Vec<i32>,
    stack_out: Vec<i32>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl CQueue {
    fn new() -> Self {
        CQueue {
            stack_in: Vec::new(),
            stack_out: Vec::new(),
        }
    }

    fn append_tail(&mut self, value: i32) {
        self.stack_in.push(value);
    }

    fn delete_head(&mut self) -> i32 {
        if (self.stack_out.is_empty()) {
            while let Some(n) = self.stack_in.pop() {
                self.stack_out.push(n)
            }
        }
        self.stack_out.pop().unwrap_or(-1)
    }
}

fn main() {
    let mut queue = CQueue::new();
    queue.append_tail(1);
    println!("{:?}", queue.delete_head());
}
