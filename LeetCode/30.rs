use std::collections::HashMap;

pub fn find_substring(s: String, words: Vec<String>) -> Vec<i32> {
    let mut map = HashMap::new();
    let word_len = words[0].len();
    let words_cnt = words.len();
    for word in words {
        map.entry(word).and_modify(|e| *e += 1).or_insert(1);
    }
    let mut res = vec![];
    for (idx, win) in s
        .chars()
        .collect::<Vec<char>>()
        .as_slice()
        .windows(word_len * words_cnt)
        .enumerate()
    {
        let mut cur_map = map.clone();
        for word in win.chunks(word_len) {
            cur_map
                .entry(word.iter().collect::<String>())
                .and_modify(|e| *e -= 1);
        }
        if !cur_map.into_iter().any(|(_, v)| v != 0) {
            res.push(idx as i32);
        }
    }
    res
}

fn main() {
    println!(
        "{:?}",
        find_substring("barfoothefoobarman".to_string(), {
            let v = vec!["foo", "bar"];
            v.into_iter().map(|s| s.to_string()).collect()
        })
    );
    println!(
        "{:?}",
        find_substring("wordgoodgoodgoodbestword".to_string(), {
            let v = vec!["word","good","best","word"];
            v.into_iter().map(|s| s.to_string()).collect()
        })
    );
    println!(
        "{:?}",
        find_substring("barfoofoobarthefoobarman".to_string(), {
            let v = vec!["bar","foo","the"];
            v.into_iter().map(|s| s.to_string()).collect()
        })
    );
}
