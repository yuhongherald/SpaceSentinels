function sleep(ms) {
	return new Promise(function(resolve) {setTimeout(resolve, ms)});
}
exports.pickup = function(hud, PObject, actions) {
	return function(objectName) {
		async function x() {
			var object = hud.GetInteractable(objectName);
			if (object) {
				var seconds = PObject.TurnTo(object.GetActorLocation());
				await sleep(seconds);
				seconds = PObject.WalkTo(object.GetActorLocation(), 200);
				await sleep(seconds);
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