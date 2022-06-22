/**
 * @param {string} graph
 * @return {boolean}
 */
var hasCycle = function (graph) {
    const edges = graph.split(",");
    const g = {};
    for (const edge of edges) {
        const [s, e] = edge.split("->");
        if (!g[s]) {
            g[s] = [];
        }
        g[s].push(e);
    }
    const dfs = (p, v) => {
        if (v[p]) {
            return true;
        }
        v[p] = true;
        for (const e of g[p] || []) {
            if (dfs(e, v)) {
                return true;
            }
        }
        v[p] = false;
        return false;
    };
    for (const [s, _] of Object.entries(g)) {
        if (dfs(s, {})) {
            return true;
        }
    }
    return false;
};

console.log(hasCycle("1->2,2->3,3->1"));
console.log(hasCycle("1->4,2->5,3->6,3->7,4->8,5->8,5->9,6->9,6->11,7->11,8->12,9->12,9->13,10->13,10->14,11->10,11->14"));
console.log(hasCycle("1->4,2->5,3->6,3->7,4->8,5->8,5->9,6->9,6->11,7->11,8->12,9->12,9->13,10->6,10->13,10->14,11->10,11->14"));