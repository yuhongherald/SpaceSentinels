function sleep(ms) {
	return new Promise(function(resolve) {setTimeout(resolve, ms)});
}

exports.wait = function(hud, PObject, actions) {
	return function(seconds) {
		async function x() {
			await sleep(1005 * seconds);
		}
		actions.list.unshift(x);
		return new Promise(function(resolve) {setTimeout(resolve, 1000 * seconds)});
	}
}

exports.get_state = function(hud, PObject, actions) {
	return function() {
		return hud.GetInteractable("raft").GetState();
	}
}

exports.move = function(hud, PObject, actions) {
	return async function(objectName) {
		var object = hud.GetInteractable(objectName);
		if (object) {
				if (PObject.SetState) {
					PObject.SetState(1);
				}
				var seconds = PObject.WalkTo(object.GetActorLocation(), 500);
				await sleep(seconds);
				if (PObject.SetState) {
					if (objectName == "island") {
						PObject.SetState(2);
					} else if (objectName == "bank") {
						PObject.SetState(0);
					}
				}
		} else {
			throw "Invalid Name"
		}
		return new Promise(function(resolve) {
			resolve();
		});
	}
}

exports.embark = function(hud, PObject, actions) {
	return function() {
		var object = hud.GetInteractable("raft");
		if (object) {
			if (PObject.Near(object.GetActorLocation())) {
				object.RootPlayer(PObject);
			} else {
				throw "Too far from raft!"
			}
		} else {
			throw "Error retrieving raft object!"
		}
	}
}

exports.disembark = function(hud, PObject, actions) {
	return function() {
		var object = hud.GetInteractable("raft");
		if (object) {
			if (object.GetState() != 1) {
				object.UnrootPlayer(PObject);
			} else {
				throw "Raft is still moving!"
			}
		} else {
			throw "Error retrieving raft object!"
		}
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