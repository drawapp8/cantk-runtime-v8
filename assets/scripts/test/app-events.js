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

document.addEventListener("pointerdown", function(event) {
	console.log("pointerdown:" + event.x + "," + event.y);
});

document.addEventListener("pointerup", function(event) {
	console.log("pointerup:" + event.x + "," + event.y);
});

document.addEventListener("pointermove", function(event) {
	console.log("pointermove:" + event.x + "," + event.y);
});

