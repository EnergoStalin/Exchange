var SimulateOptions = {
	speed: 1,
	maxSpeed: 5,
	minSpeed: 1,
	humans: 0
}
var EnvironmentOptions = {
	assets_url: [
		{
			name: "background1",
			url: "C:\\Users\\Alex\\Documents\\Wallpaper\\osu-hd-wallpapers.jpg"
		},
		{
			name: "background3",
			url: "C:\\Users\\Alex\\Documents\\Programming\\Js\\sc_005.png"
		},
		{
			name: "background4",
			url: "https://mdn.mozillademos.org/files/225/Canvas_drawimage.jpg"
		},
		{
			name: "background5",
			url: "https://sun9-2.userapi.com/c846123/v846123194/16ed12/9Kx9zBO6R0I.jpg"
		}
	],
	findAsset: function(name) {
		for(var i = 0; i < this.assets.length; i++) {
			if(this.assets[i].name == name) return i;
		}
		return -1; 
	},
	assets: []
}

var DrawRef = {
	ctx: null,
	width: 0,
	height: 0
};