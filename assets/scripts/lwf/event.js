
function onPointerMove(e) {
    window.lwf.inputPoint(e.x, e.y);
}

function onPointerDown(e) {
	console.log("onPointerDown:");
    window.lwf.inputPoint(e.x, e.y);
    window.lwf.inputPress();
}

function onPointerUp(e) {
	console.log("onPointerUp");
    window.lwf.inputPoint(e.x, e.y);
    window.lwf.inputRelease();
}

document.addEventListener("pointerdown", onPointerDown);
document.addEventListener("pointermove", onPointerMove);
document.addEventListener("pointerup", onPointerUp);


