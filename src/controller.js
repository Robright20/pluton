import {User, Proc} from "./models";

const log = console.log;

export default {
	newCycle: function(...params) {log("newCycle")},
	newProcess: function(...params) {
    // new-process [userId, pid, pc]
    const [userId, pid, pc] = params;
    const user = this.users[userId];
    if (user.procList.length === 0) {
      user.load(this.cells, this.ctx, pc);
      // this.say("We've got a new warrior !");
    }
    log(`Creating process uid=[${userId}] pid=[${pid}]`);
    const proc = new Proc(user, pid, this.cells[pc]);
    user.procList.push(proc);
    this.procs[pid] = proc;
    proc.cell.draw(this.ctx);
  },
	updateProcess: function(...params) {
    // update-process pid [data] (data -> {pc, carry})
    const [pid, pc, carry] = params;
    const proc = this.procs[pid];

    proc.cell.reset();
    proc.PC = pc;
    proc.carry = carry;
    proc.cell = this.cells[pc];
    proc.setCell();
    proc.cell.draw(this.ctx);
  },
	newCheck: function(...params) {log("newCheck")},
	newUser: function(...params) {
    // new-user [userId, name, desc, code, size]
    log(`Creating user [${params[0]}]...`);
    const details = params.slice(1, params.length);
    const user = new User(...details);

    this.users[params[0]] = user;
  },
	newData: function(...params) {
    // new-data pid idx [data]
    const [pid, idx, ] = params;
    const user = this.procs[pid].uid;
    const cell = this.cells[idx];

    cell.user = user;
    cell.reset();
  },
	killProcess: function(...params) {
    // delete in the user's procList and then in global's one
    log("killProcess");
  },
	live: function(...params) {log("live")}
}
