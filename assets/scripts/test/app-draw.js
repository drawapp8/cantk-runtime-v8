var canvas = document.createElement('canvas');
var ctx = canvas.getContext("2d");

canvas.init(1);

console.log(canvas.width + "x" + canvas.height);

var image = new Image();

image.onload = function(message) {
	console.log(message + ": w=" + this.width + " h=" + this.height + " id=" + this.id + " src=" + this.src);
}

image.onerror = function(message) {
	console.log(message + ": w=" + this.width + " h=" + this.height + " id=" + this.id + " src=" + this.src);
}

image.src = "images/ball.png";

var imageGround = new Image();
imageGround.src = "images/ground.png";

function draw() {
	var ctx = canvas.getContext("2d");
	ctx.fillStyle = "Green";
	ctx.save();
	ctx.translate(150, 150);
	ctx.rotate(tick.time);
	ctx.translate(-150, -150);
	ctx.fillRect(100, 100, 100, 100);
	ctx.restore();

	ctx.beginPath();
	ctx.moveTo(200, 200);
	ctx.lineTo(300, 300);
	ctx.lineTo(300, 400);
	ctx.lineJson = 'round';
	ctx.lineWidth = 2;
	ctx.strokeStyle = "Red";
	ctx.stroke();

	ctx.drawImage(image, 0, 0);
	ctx.drawImage(image, 100, 100, 50, 50);
	ctx.drawImage(image, 10, 10, 50, 50, 200, 200, 50, 50);

	ctx.drawImage(imageGround, 0, canvas.height-60, canvas.width, 60);

	ctx.font = "sans 36px";
	ctx.fillStyle = "Gold";
	ctx.fillText("Hello", 200, 200);

	ctx.beginPath();
	ctx.arc(470, 90,60, 0, Math.PI * 2);
	ctx.closePath();

	ctx.fillStyle = "Green";
	ctx.fill();
	ctx.stroke();

	window.requestAnimationFrame(draw);
}

window.requestAnimationFrame(draw);

