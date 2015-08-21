for(var i = 0; i < 1; i++) {
	fs.readAsText("app-timer.js", "", function(str) {
		console.log("content:" + str);
	});
}

var str = fs.readAsText("app-timer.js", null, null);

console.log("============sync:" + str);

