function onKeyDownCapture(event) {
	console.log("keydown(capture):" + event.code);
	removeEventListener("keydown", onKeyDownCapture, true);
}

document.addEventListener("keydown", onKeyDownCapture, true);

document.addEventListener("keydown", function(event) {
	console.log("keydown:" + event.code);
});


document.addEventListener("keyup", function(event) {
	console.log("keyup:" + event.code);
});

document.addEventListener("touchstart", function(event) {
	console.log("touchstart:");
});

document.addEventListener("touchend", function(event) {
	console.log("touchend:");
});

document.addEventListener("touchmove", function(event) {
	console.log("touchmove:");
});

