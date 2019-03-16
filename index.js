const addon = require('./build/Release/addon');
// js
console.time('c++')
//console.log(Fib.fib(40)); // 'world
var idGen = new addon.DistributedID(10);
console.log("id: ", idGen.generateId());

console.log("id: ", idGen.generateId());
console.log("id: ", idGen.generateId());
for (var i=0; i<3; ++i) {
  console.log("id: ", idGen.generateId());
}
console.timeEnd('c++')

/*
function fib(n) {
  if (n === 1 || n === 2) {
    return 1
  }
  return fib(n - 1) + fib(n - 2)
}

function fib2(n) { 
    if (n < 2) { 
        return 1; 
    } 
    var a = 1, b = 1; 
    for (var i = 2; i < n - 1 ;i++ ) { 
        b = a + b; 
        a = b - a; 
    } 
    return a + b; 
}


// js
console.time('node')
console.log(fib(40))
console.timeEnd('node')
*/

console.log(process.memoryUsage());

