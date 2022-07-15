struct WordFilter {
    words: Vec<String>,
}

impl WordFilter {
    fn new(words: Vec<String>) -> Self {
        WordFilter { words }
    }

    fn f(&self, pref: String, suff: String) -> i32 {
        self.words
            .iter()
            .enumerate()
            .rev()
            .find(|(_, words)| words.starts_with(&pref) && words.ends_with(&suff))
            .map(|(idx, _)| idx as i32)
            .unwrap_or(-1)
    }
}

fn main() {
    let w = WordFilter::new(vec!["apple".into()]);
    println!("{}", w.f("a".into(), "e".into()))
}