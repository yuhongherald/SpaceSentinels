function main() {
	//Heads Up Display of the game
	var hud = GWorld.GetPlayerController().GetHUD();
	var BasicEnv = require('BasicEnv');
	var lvl1 = require('lvl1');
	var lvl2 = require('lvl2');
	var lvl3 = require('lvl3');
	var signal = hud.getSignal();
	var StaticObjects = hud.GetStatics();

	/*
	Nullifying global variables
	*/
	var mask = {};
	for (p in this) {
		mask[p] = undefined;
	}
	/*
	Libraries
	*/
	var library = {
		BasicEnv : {},
		lvl1 : {},
		lvl2 : {},
		lvl3 : {}
	};
	for (p in BasicEnv) {
		library.BasicEnv[p] = BasicEnv[p];
	}
	for (p in lvl1) {
		library.lvl1[p] = lvl1[p];
	}
	for (p in lvl2) {
		library.lvl2[p] = lvl2[p];
	}
	for (p in lvl3) {
		library.lvl3[p] = lvl3[p];
	}
	function sleep(ms) {
		return new Promise(function(resolve) {setTimeout(resolve, ms)});
	}
	function Reset() {
		hud.Reset();
	}

	var infinite_string = 
	'async function Execute(cmd) {'+
	'	eval(infinite_string);'+
	'	try {'+
	'		if (cmd) {'+
	'			hud.Output(eval(cmd) + "");'+
	'		}'+
	'	} catch (e) {'+
	'		hud.Output(e + "");'+
	'	}'+
	'	await _remove();'+
	'	current_env = Execute;'+
	'	return new Promise(function (resolve) {'+
	'		resolve();'+
	'	});'+
	'};'

	var current_env;
	async function Execute(cmd, lib) {
		eval(infinite_string);
		if (lib) {
			for (p in mask) {
				eval("var " + p + "= undefined");
			}
			var external = {};
			(function() {
				var actions = {};
				actions.list = [];
				actions.running = false;
				try {
					for (p in lib) {
						external[p] = lib[p](hud, hud.GetPObject(), actions);
					}
				} catch (e) {
					hud.Output("Import error" + e + "");
				}
			})();
			for (p in external) {
				eval("var " + p + "= external[p]");
			}
		}
		try {
			if (cmd) {
				hud.Output(eval(cmd) + "");
			}
		} catch (e) {
			hud.Output(e + "");
		}
		await _remove();
		current_env = Execute;
		return new Promise(function (resolve) {
			resolve();
		});
	};
	Execute(undefined, {});
	
	async function run_static(obj, cmd, lib) {
		for (p in mask) {
			eval("var " + p + "= undefined");
		}
		var external = {};
		(function() {
			var actions = {};
			actions.list = [];
			actions.running = false;
			try {
				for (p in lib) {
					external[p] = lib[p](hud, obj, actions);
				}
			} catch (e) {
				hud.Output("Import error" + e + "");
			}
		})();
		for (p in external) {
			eval("var " + p + "= external[p]");
		}
		try {
			eval(cmd);
		} catch (e) {
			console.log(e);
		}
	}
	
	for (var i = 0; i < StaticObjects.length; i++) {
		run_static(StaticObjects[i], StaticObjects[i].GetCmd(), library[StaticObjects[i].GetLib()]);
	}
	
	
	async function tick() {
		var cmd = hud.GetCmd();
		var lib;
		if (cmd == "") {
			;
		} else {
			var env = hud.GetEnv();
			hud.SetCmd("", "");
			if (env == "") {
				await current_env(cmd);
			} else {
				lib = library[hud.GetLib()];
				await Execute(cmd, lib);
			}
		}
		if (signal !== hud.getSignal()){
			signal = hud.getSignal();
			lib = library[hud.GetLib()];
			await Execute("", lib);
			//Rerun
			for (StaticObject in hud.StaticObjects) {
				run_static(StaticObjects[i], StaticObject.GetCmd(), library[StaticObject.GetLib()]);
			}
		}
		process.nextTick(tick);
	}
	tick();
}

try {
    module.exports = function() {
        let cleanup = null;
        process.nextTick(function(){cleanup = main()});
        return function(){ cleanup()};
    }
}
catch (e) {
    require('bootstrap')('interpreter')
}