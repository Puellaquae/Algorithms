/**
 * @param {string} equation
 * @return {string}
 */
var solveEquation = function (equation) {
    const [left, right] = equation.split("=");
    const reg = /[+-]?\d*x?/g;

    /**
     * @param {string} str
     * @return {[number, number]}
     */
    const parse = (str) => {
        const toks = str.match(reg).filter(x => x !== "");
        let leftX = 0;
        let leftC = 0;
        for (const tok of toks) {
            if (tok === "x" || tok === "+x") {
                leftX++;
            } else if (tok === "-x") {
                leftX--;
            } else if (tok.endsWith("x")) {
                if (tok.startsWith("+")) {
                    leftX += parseInt(tok.slice(1, tok.length - 1));
                } else if (tok.startsWith("-")) {
                    leftX -= parseInt(tok.slice(1, tok.length - 1));
                } else {
                    leftX += parseInt(tok.slice(0, tok.length - 1));
                }
            } else if (tok.startsWith("+")) {
                leftC += parseInt(tok.slice(1));
            } else if (tok.startsWith("-")) {
                leftC -= parseInt(tok.slice(1));
            } else {
                leftC += parseInt(tok);
            }
        }
        return [leftX, leftC];
    }

    let [leftX, leftC] = parse(left);
    let [rightX, rightC] = parse(right);

    leftX -= rightX;
    rightC -= leftC;
    if (leftX === 0 && rightC === 0) {
        return "Infinite solutions";
    } else if (leftX === 0) {
        return "No solution";
    } else {
        return `x=${rightC / leftX}`;
    }
};

console.log(solveEquation("x+5-3+x=6+x-2"));
console.log(solveEquation("x=x"));
console.log(solveEquation("2x=x"));
