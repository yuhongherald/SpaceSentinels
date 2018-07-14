function sleep(ms) {
	return new Promise(function(resolve) {setTimeout(resolve, ms)});
}
exports.is_forked = function(hud, PObject, actions) {
	return function(objectName) {
		return hud.GetInteractable(objectName).getLeft() != "";
	}
}
exports.walk = function(hud, PObject, actions) {
	return function(objectName) {
		async function x() {
			var object = hud.GetInteractable(objectName);
			if (object) {
				if (PObject.Near(object.startOfRiver())) {
					object.VisitStart();
					destination = object.endOfRiver();
					var seconds = PObject.TurnTo(destination);
					await sleep(seconds);
					seconds = PObject.WalkTo(destination, 500);
					await sleep(seconds);
				} else {
					throw "Too far from start of river"
				}
			} else {
				throw "Invalid Name"
			}
			return new Promise(function(resolve) {
				resolve();
			});
		}
		actions.list[actions.list.length] = x;
	}
}
exports.retrace = function(hud, PObject, actions) {
	return function(objectName) {
		async function x() {
			var object = hud.GetInteractable(objectName);
			if (object) {
				if (PObject.Near(object.endOfRiver())) {
					object.VisitEnd();
					destination = object.startOfRiver();
					var seconds = PObject.TurnTo(destination);
					await sleep(seconds);
					seconds = PObject.WalkTo(destination, 500);
					await sleep(seconds);
				} else {
					throw "Too far from end of river"
				}
			} else {
				throw "Invalid Name"
			}
			return new Promise(function(resolve) {
				resolve();
			});
		}
		actions.list[actions.list.length] = x;
	}
}
exports.get_left = function(hud, PObject, actions) {
	return function(objectName) {
		return hud.GetInteractable(objectName).getLeft();
	}
}
exports.get_right = function(hud, PObject, actions) {
	return function(objectName) {
		return hud.GetInteractable(objectName).getRight();
	}
}
exports._advance = function(hud, PObject, actions) {
	return function() {
		async function x() {
			hud.nextLevel();
			return new Promise(function(resolve) {
				resolve();
			});
		}
		actions.list[actions.list.length] = x;
	}	
}

exports._remove = function(hud, PObject, actions) {
	async function exec(resolve) {
		if (actions.list.length === 0) {
			actions.running = false;
			resolve();
		} else {
			actions.running = true;
			try {
				await (actions.list.shift(1))();
				exec(resolve);
			} catch (e) {
				hud.Output(e + "");
				actions.running = false;
				actions.list = [];
				resolve();
			}
		}
	}
	function init() {
		return new Promise(
			function(resolve){
				exec(resolve);
			}
		);
	}
	return init;
}