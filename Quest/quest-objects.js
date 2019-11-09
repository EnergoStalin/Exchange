var Human = function() {
	this.keys = Math.round(Math.random()*5);
}

var Check = function() {
	this.up = Math.round(Math.random()*2);
	this.down = Math.round(Math.random()*2);
	this.left = Math.round(Math.random()*2);
	this.right = Math.round(Math.random()*2);
	this.human = (Math.round(Math.random()) == 1) ? new Human() : null;

	return this;
}
var Coord = function(x,y) {
	this.x = x;
	this.y = y;
}
var Poly = {
	room: [],
	checkSize: 0,
	init: function(r,c) {
		this.checkSize = Math.min(DrawRef.width/c,DrawRef.height/r);
		for(var i = 0; i < r; i++) {
			var col = [];
			for(var k = 0; k < c; k++) {
				col.push(new Check());
			}
			this.room.push(col);
		}
		console.log(this.room);
	},
	reinit: function() {
		this.room = [];
		this.init();
	}
};