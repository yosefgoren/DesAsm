var elt = document.getElementById('calculator');
var calculator = Desmos.GraphingCalculator(elt);
elt.calculator = calculator
calculator.updateSettings({showGrid: "false", showXAxis: "false", showYAxis: "false"})
console.log(Object.keys(calculator));
