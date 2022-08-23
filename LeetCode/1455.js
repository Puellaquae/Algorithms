/**
 * @param {string} sentence
 * @param {string} searchWord
 * @return {number}
 */
 var isPrefixOfWord = function(sentence, searchWord) {
    const res = sentence.split(' ').findIndex(x => x.startsWith(searchWord));
    return res === -1 ? -1 : res + 1;
};