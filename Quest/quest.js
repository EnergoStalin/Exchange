var SpeedUi = null;

var Simulate = function() {
	showMessage("Assets Loaded.");
	showMessage("Poly inited.","Humans at poly: " + SimulateOptions.humans);
	Poly.init(prompt("Cols"),prompt("Rows"));
	Poly.draw();
}

var init = function() {
	showMessage("Init success!");
	var can = document.getElementById('viewport');
	DrawRef.ctx = can.getContext("2d");
	DrawRef.width = can.clientWidth | can.innerWidth;
	DrawRef.height = can.clientHeight | can.innerHeight;
	SpeedUi = document.getElementById('ui-speed');
	UpdateUi();
	loadAssets(Simulate);
}

var InputHandler = function(evt) {
	switch(evt.keyCode) {
		case 38:
			if(SimulateOptions.speed >= SimulateOptions.maxSpeed) {
				showMessage("Предупреждение","Максимальная скорость. " + SimulateOptions.maxSpeed + " Вы не можете сделать её больше.");
			} else {
				SimulateOptions.speed++;
				DrawBackground(SimulateOptions.speed-1);
				UpdateUi();
			}
		break;
		case 40:
			if(SimulateOptions.speed <= SimulateOptions.minSpeed) {
				showMessage("Предупреждение","Минимальная скорость. " + SimulateOptions.minSpeed + " Вы не можете сделать её меньше.");
			} else {
				SimulateOptions.speed--;
				DrawBackground(SimulateOptions.speed-1);
				UpdateUi();
			}
		break;
		case 32:
			Clear();
			Poly.draw();
		break;
		case 27:
			// Pause
		break;
		default:
			console.log(evt.keyCode);
		break;
	}
}

var UpdateOptions = function() {
	
}
var UpdateUi = function() {
	SpeedUi.textContent = "Speed: " + SimulateOptions.speed;
}

document.addEventListener("DOMContentLoaded",init);
document.addEventListener("keydown",InputHandler);