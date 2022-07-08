/**
 * @param {string[]} dictionary
 * @param {string} sentence
 * @return {string}
 */
var replaceWords = function (dictionary, sentence) {
    let words = sentence.split(" ");
    words = words.map(w => {
        let rd = undefined;
        dictionary.forEach(d => {
            if (w.startsWith(d)) {
                if (!rd || rd.length > d.length) {
                    rd = d;
                }
            }
        })
        return rd || w;
    });
    return words.join(" ");
};

console.log(replaceWords(["cat", "bat", "rat"], "the cattle was rattled by the battery"));
console.log(replaceWords(["catt", "cat", "bat", "rat"], "the cattle was rattled by the battery"));
console.log(replaceWords(["a", "b", "c"], "aadsfasf absbs bbab cadsfafs"));