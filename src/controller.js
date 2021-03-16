const log = console.log;
function newCycle() {log("newCycle")}
function newProcess() {log("newProcess")}
function newCheck() {log("newCheck")}
function newUser() {log("newUser")}
function newData() {log("newData")}
function killProcess() {log("killProcess#")}

export default {
	newCycle,
	newProcess,
	newCheck,
	newUser,
	newData,
	killProcess
}