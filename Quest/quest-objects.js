var Check = function() {
	this.up = 0;
	this.down = 0;
	this.left = 0;
	this.right = 0;

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