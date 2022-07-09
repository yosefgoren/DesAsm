dragElement(document.getElementById("calculator"));
dragElement(document.getElementById("mydiv"));

function runCompile(box){
	script = box.script_box.value;
	// asm = compile(script)
	asm = script
	calculator.setExpression({latex: asm});
	box.script_box.value = "";
}

var oShell = new ActiveXObject("Shell.Application");  
function compile(script){
	var commandtoRun = "code a"; 
	oShell.ShellExecute(commandtoRun,"","","open","1");
	return script
}