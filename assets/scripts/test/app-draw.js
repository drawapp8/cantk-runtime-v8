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

	ctx.lineJoin = 'round';
	ctx.lineWidth = 2;
	ctx.strokeStyle = "Red";
	ctx.stroke();
	
	ctx.beginPath();
	ctx.arc(300, 300,60, 0, Math.PI * 2, true);
	ctx.closePath();

	ctx.fillStyle = "Gold";
	ctx.fill();
	ctx.stroke();
	
	ctx.strokeStyle = "Blue";
	ctx.beginPath();
	ctx.arc(200, 500, 80, 0 , Math.PI * 2);
	ctx.closePath();
	ctx.stroke();
	ctx.clip();
	ctx.beginPath();
	ctx.arc(400, 400, 100, 0 , Math.PI * 2);
	ctx.closePath();
    ctx.stroke();
	ctx.clip();
  	
    ctx.save();	
	ctx.beginPath();
	ctx.rect(200,400,200,300);
	ctx.closePath();
	ctx.strokeStyle = "Green";
	ctx.stroke();
	ctx.fillStyle = "Red";
	ctx.clipRect(200,400,500,600);
	
	ctx.beginPath();
	ctx.rect(200,400,200,300);
	ctx.closePath();
	ctx.fillStyle = "Green";
	ctx.stroke();
	
    ctx.save();	
	ctx.clipRect(450,400,200,200);
		
	ctx.beginPath();
	ctx.rect(300,200,500,500);
	ctx.closePath();
	ctx.fillStyle = "Blue";
	ctx.strokeStyle = "Blue";
	ctx.stroke();
	ctx.fill();
	ctx.restore();

	ctx.stroke();
	ctx.restore();
	ctx.clipRect(0,0,2000,2000);
	ctx.fillStyle = "Red";
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
			ctx.scale(0.5, 0.5);
			ctx.translate(-cx, -cy);
			ctx.fillRect(0, 0, iw, ih);
			ctx.restore();
		}
	}
    
	var screenwd = screen.width;	
    var screenht = screen.height;
	var x = (screenwd - image.width) / 2;
	var y = (screenht - image.height) / 2;
	var cx = x + image.width / 2;
	var cy = y + image.height / 2;
	ctx.save();
	ctx.translate(cx, cy);
	ctx.rotate(tick.time);
	//ctx.scale(1.2, 1.2);
	ctx.translate(-cx, -cy);
	ctx.translate(x, y);
	ctx.drawImage(image, 0, 0);
	ctx.restore();
	ctx.drawImage(image, (screenwd - 50)/2, (screenht - 50), 50, 50);
	ctx.drawImage(image, 10, 10, 50, 50, 200, 200, 50, 50);

	ctx.font = "sans 36px";
	ctx.fillStyle = "Gold";
	ctx.fillText("Hello CanTK Runtime", 200, 200);

	window.requestAnimationFrame(draw);
}

window.requestAnimationFrame(draw);

