var loadAssets = function(callback) {
	showMessage("Loading assets...");
	var total = 0;
	for(var i = 0; i < EnvironmentOptions.assets_url.length; i++) { 
		EnvironmentOptions.assets.push({
			name: EnvironmentOptions.assets_url[i].name,
			e: (function() {var e = new Image(); e.src = EnvironmentOptions.assets_url[i].url; return e;})()
		});
		EnvironmentOptions.assets[i].e.addEventListener("load",function() {
			if(++total == EnvironmentOptions.assets_url.length) { callback(); console.log(total);}
		});
	}
}
var fade = function() {
	var elem = this;
	element(elem,{class: "slide-up"});
	setTimeout(function() {
		elem.parentNode.removeChild(elem);
	},1300);
};
var showMessage = function(title, text) {
	var box = null;
	if(text == null) {
		box = element("p",{
			class: ["message-box","caption"],
			style: {
				"min-height": "0px"
			},
			to: document.body,
			textContent: title,
			module: {
				fade: fade
			}
		});
		setTimeout(function() {box.fade();},1000);
		return box;
	}
	box = element("div",{
		add: [
			element("p",{
				class: "caption",
				textContent: title
			}),
			element("p",{
				class: "message",
				textContent: text
			})
		],
		style: {
			opacity: 1,
		},
		height: this.clientHeight | this.innerHeight,
		to: document.body,
		class: "message-box",
		module: {
			fade: fade
		}
	});
	setTimeout(function() {box.fade();},1000);
	return box;
}
var DrawHuman = function() {

}
function Clear(dx,dy,w,h) {
	if(arguments.length == 0) {
		DrawRef.ctx.clearRect(0,0,DrawRef.width,DrawRef.height);
	} else {
		DrawRef.ctx.clearRect(dx,dy,w,h);
	}
}
function AspectRatioFit(srcWidth, srcHeight, maxWidth, maxHeight) {
	var ratio = Math.min(maxWidth / srcWidth, maxHeight / srcHeight);

	return { width: srcWidth*ratio, height: srcHeight*ratio };
}
var DrawBackground = function(i) {
	Clear();
	var ratio = AspectRatioFit(EnvironmentOptions.assets[i].e.naturalWidth,EnvironmentOptions.assets[i].e.naturalHeight,DrawRef.width,DrawRef.height);
	DrawRef.ctx.drawImage(EnvironmentOptions.assets[i].e, DrawRef.width / 2 - ratio.width / 2,DrawRef.height / 2 - ratio.height / 2,ratio.width,ratio.height);
}
Object.defineProperty(DrawRef,"line",{
	value: function(nx,ny,tx,ty,options) {
		this.ctx.save();
		this.ctx.beginPath();
		this.ctx.moveTo(nx,ny);
		for(var o in options) {
			this.ctx[o] = options[o];
		}
		this.ctx.lineTo(tx,ty);
		this.ctx.stroke();
		this.ctx.closePath();
		this.ctx.restore();
	}
});
Object.defineProperty(Poly,"draw",{
	value: function() {
		var d = this.checkSize;
		for(var i = 0; i < this.room.length; i++,d+=this.checkSize) {
			DrawRef.line(0,d,this.checkSize*this.room[0].length,d);
		}
		d = 0;
		for(var k = 0; k < this.room[0].length; k++,d+=this.checkSize) {
			DrawRef.line(d,0,d,this.checkSize*this.room.length);
		}
	}
});