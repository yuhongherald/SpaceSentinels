function sleep(ms) {
	return new Promise(function(resolve) {setTimeout(resolve, ms)});
}
exports.display = function(hud, PObject, actions) {
	return function(x) {
		hud.Output(x+"");
	}
}
exports._move = function(hud, PObject, actions) {
	return function(x, y, z, speed) {
		PObject.MoveCharacter(x, y, z, speed)
	}
}
exports._turn = function(hud, PObject, actions) {
	return function(angle) {
		PObject.Turn(angle);
	}
}
exports.turn_left = function(hud, PObject, actions) {
	return function(angle) {
		async function x() {
			PObject.Turn(-Math.PI/2);
			await sleep(500);
			return new Promise(function(resolve) {
				resolve();
			});
		}
		if (actions.running) {
			actions.list.unshift(x);
		} else {
			actions.list[actions.list.length] = x;
		}
	}
}
exports.turn_right = function(hud, PObject, actions) {
	return function(angle) {
		async function x() {
			PObject.Turn(Math.PI/2);
			await sleep(500);
			return new Promise(function(resolve) {
				resolve();
			});
		}
		if (actions.running) {
			actions.list.unshift(x);
		} else {
			actions.list[actions.list.length] = x;
		}
	}
}
exports._walk = function(hud, PObject, actions) {
	return function(distance, speed) {
		PObject.Walk(distance, speed);
	}
}
exports.walk = function(hud, PObject, actions) {
	return function(distance) {
		async function x() {
			PObject.Walk(distance, 100);
			await sleep(distance * 10);
			return new Promise(function(resolve) {
				resolve();
			});
		}
		if (actions.running) {
			actions.list.unshift(x);
		} else {
			actions.list[actions.list.length] = x;
		}
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