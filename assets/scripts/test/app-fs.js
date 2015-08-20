for(var i = 0; i < 100; i++) {
	fs.readAsText("app-timer.js", "", function(str) {
		console.log("content:" + str);
	});
}

var str = fs.readAsText("app-timer.js");

console.log("============sync:" + str);

