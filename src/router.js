import Controller from './controller';

/* 
*  userId pid pc
* 
*  userId
*  pid idx [data]
*  pid
*/

const router = (function() {
	const map = new Map();

	map.set("#new-cycle", Controller.newCycle);
	map.set("#new-process", Controller.newProcess);
	map.set("#new-check", Controller.newCheck);
	map.set("#new-user", Controller.newUser);
	map.set("#new-data", Controller.newData);
	map.set("#kill-process", Controller.killProcess);

	return function(req) {
		try {
			const reqSplit = req.split(" ");
			const path = reqSplit.shift();
			map.get(path).call(this, ...reqSplit);	
		} catch (err) {
			console.log("no path found");
		}
	}
})();

export default router;
