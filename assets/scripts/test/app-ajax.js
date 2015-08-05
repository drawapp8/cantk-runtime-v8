
var xhr = new XMLHttpRequest();
xhr.onreadystatechange = function() {
	console.log(this.readyState);
	if(this.readyState === XMLHttpRequest.Loaded) {
		console.log(this.responseText);
		console.log("Content-Length:" + this.getResponseHeader("Content-Length"));
	}
}

xhr.open("GET", "http://www.baidu.com");
xhr.setRequestHeader("Accept", "*/*");
xhr.setRequestHeader("Origin", "anonymous");

xhr.send("Hello");

