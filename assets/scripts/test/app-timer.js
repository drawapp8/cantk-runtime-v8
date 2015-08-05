var index = 0;

function print3() {
	console.log("print3");
	window.setTimeout(print3, 3000);
}

function print1() {
	console.log("print1:" + index++);
}

setTimeout(print3, 3000);
setInterval(print1, 1000);

