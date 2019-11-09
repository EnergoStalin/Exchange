var hasClass = function(node,clas) {
	for (var i = 0; i < node.classList.length; i++) {
		if(node.classList[i] === clas) return true;
	} return false;
}
var element = function(tag,option) {
	var elem = null;
	if(tag instanceof Node) elem = tag;
	else elem = document.createElement(tag);
	for(var o in option) {
		switch(o) {
			case "remove":
				tag.parentNode.removeChild(tag);
			break;
			case "class":
				if(option[o] instanceof Array) {
					for(var k = 0; k < option[o].length; k++) {
						if(hasClass(elem,option[o][k])) {
							elem.classList.remove(option[o][k]);
							if(elem.classList.length == 0) elem.removeAttribute("class");
						} else elem.classList.add(option[o][k]);
					}
				} else {
					if(hasClass(elem,option[o])) {
						elem.classList.remove(option[o]);
						if(elem.classList.length === 0) elem.removeAttribute("class");
					}
					else elem.classList.add(option[o]);
				}
			break;
			case "add":
				if(option[o] instanceof Array) for(var j = 0; j < option[o].length; j++) elem.appendChild(option[o][j]);
				else elem.appendChild(option[o]);
			break;
			case "module":
				for(var b in option[o])
					Object.defineProperty(elem,b,{
						value : option[o][b]
					});
			break;
			case "style":
				for(var d in option[o])
					elem.style[d] = option[o][d];
			break;
			case "to":
				option[o].appendChild(elem);
			break;
			case "listen":
				if(option[o] instanceof Array) {
					for (var i = 0; i < option[o].length; i++) {
						elem.addEventListener(option[o][i].event,option[o][i].funct);
					}
				} else {
					elem.addEventListener(option[o].event,option[o].funct);
				}
			break;
			default:
				elem[o] = option[o];
		}
	}
	return elem;
}
var nthParent = function(node,count) {
	for(var i = 0; i < count; i++) node = node.parentNode;
	return node;
}
var reverseString = function(str) {
	var newStr = "";
	for(var i = str.length - 1; i >= 0; i--) {
		newStr += str[i];
	}  return newStr;
}
var getName = function(path) {
	return path.replace(/^.*[\\\/]/, ''); //Очень важно
}