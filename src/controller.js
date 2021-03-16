const log = console.log;

export default {
	newCycle: function(...params) {log("newCycle")},
	newProcess: function(...params) {log("newProcess")},
	updateProcess: function(...params) {log("updateProcess")},
	newCheck: function(...params) {log("newCheck")},
	newUser: function(...params) {log("newUser")},
	newData: function(...params) {log("newData")},
	killProcess: function(...params) {log("killProcess")}
}
