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
	var w = canvas.width;
	var h = canvas.height;

	ctx.beginPath();
	ctx.moveTo(200, 200);
	ctx.lineTo(300, 300);
	ctx.lineTo(300, 400);
	ctx.closePath();

	ctx.lineJson = 'round';
	ctx.lineWidth = 2;
	ctx.strokeStyle = "Red";
	ctx.stroke();
	
	ctx.beginPath();
	ctx.arc(300, 300,60, 0, Math.PI * 2);
	ctx.closePath();

	ctx.fillStyle = "Gold";
	ctx.fill();
	ctx.stroke();

	ctx.fillStyle = "Green";

	var row = 20;
	var col = 20;
	var iw = w / col;
	var ih = h / row;
	for(var i = 0; i < col; i++) {
		for(var k = 0; k < row; k++) {
			var x = i * iw;
			var y = k * ih;
			var cx = (iw >> 1);
			var cy = (ih >> 1);

			ctx.save();
			ctx.translate(x, y);
			ctx.translate(cx, cy);
			ctx.rotate(tick.time);
			ctx.translate(-cx, -cy);

			ctx.fillRect(0, 0, iw, ih);
			ctx.restore();
		}
	}

	ctx.drawImage(image, 0, 0);
	ctx.drawImage(image, 100, 100, 50, 50);
	ctx.drawImage(image, 10, 10, 50, 50, 200, 200, 50, 50);

	ctx.font = "sans 36px";
	ctx.fillStyle = "Gold";
	ctx.fillText("Hello CanTK Runtime", 200, 200);

	window.requestAnimationFrame(draw);
}

window.requestAnimationFrame(draw);

