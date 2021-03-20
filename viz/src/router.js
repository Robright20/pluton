import Controller from './controller';

/* 
* new-process userId pid pc
* new-user userId [data] (data -> {name, desc, code, size})
* new-data pid idx [data]
* kill-process pid

* update-process pid [data] (data -> {pc, carry})
* live pid [data] (data -> userId)
*
*/

const router = (function() {
	const map = new Map();

	map.set("##new-cycle", Controller.newCycle);
  map.set("##new-process", Controller.newProcess);
	map.set("##update-process", Controller.updateProcess);
	map.set("##new-check", Controller.newCheck);
	map.set("##new-user", Controller.newUser);
	map.set("##new-data", Controller.newData);
  map.set("##kill-process", Controller.killProcess);
	map.set("##live", Controller.live);
	map.set("##check-client", Controller.checkClient);
	map.set("##update-c2d", Controller.cycleToDie);
	map.set("##END", Controller.end);

	return function(req) {
		let path = "";
		try {
			const reqSplit = req.split("|");
			path = reqSplit.shift();
			map.get(path).call(this, ...reqSplit); //maybe set a timeout here
		} catch (err) {
			console.log(`[${path}] Invalid Path.`);
			console.log(err);
		}
	}
})();

export default router;
