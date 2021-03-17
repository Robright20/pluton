import {User, Proc} from "./models";

const log = console.log;

export default {
	newCycle: function(...params) {log("newCycle")},
	newProcess: function(...params) {
    // new-process [userId, pid, pc]
    const [userId, pid, pc] = params;
    const user = this.users[userId];
    const proc = new Proc(user, pid, cells[pc]);
    log(`Creating process uid=[${userId}] pid=[${pid}]`);

    user.procList.push(proc);
    this.procs[pid] = proc;
    if (user.procList.length === 1) {
      user.load(this.cells, this.ctx, pc);
    }
    log(user);
    log(this.procs);
    proc.cell.draw(this.ctx);
  },
	updateProcess: function(...params) {log("updateProcess")},
	newCheck: function(...params) {log("newCheck")},
	newUser: function(...params) {
    // new-user [userId, name, desc, code, size]
    log(`Creating user [${params[0]}]...`);
    const details = params.slice(1, params.length);
    const user = new User(...details);

    this.users[params[0]] = user;
    log(this.users);
  },
	newData: function(...params) {log("newData")},
	killProcess: function(...params) {
    // delete in the user's procList and then in global's one
    log("killProcess");
  },
	live: function(...params) {log("live")}
}
