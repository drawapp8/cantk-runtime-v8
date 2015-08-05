function window() {
}

window.requestAnimationFrameFuncs = [];

window.requestAnimationFrame(callback) {
	window.requestAnimationFrameFuncs.push(callback);
}

function tick() {
	var arr = window.requestAnimationFrameFuncs;
	
	var n = arr.length;
	for(var i = 0; i < n; i++) {
		var callback = arr[i];
		callback();
	}

	arr.length = 0;
}
