import {User, Proc} from "./models";

const log = console.log;

export default {
	newCycle: (function() {
    let cycle = 0;
    return function(...params) {
      cycle++;
      this.dispatch("cycle", cycle);
      this.dispatch("users", this.users);
      this.dispatch("status", "RUNNING...");
      log("newCycle");
    }
  })(),
	newProcess: function(...params) {
    // new-process [userId, pid, pc]
    const [userId, pid, pc] = params;
    const user = this.users[userId];
    if (user.procList.length === 0) {
      user.load(this.cells, this.ctx, pc);
      // this.say("Leave the cluster right now !");
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

    if (proc.PC == pc)
      return ;
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
    let [pid, idx, ] = params;
    const user = this.procs[pid].uid;
    const ctx = this.ctx;
    let cell;

    for (let i = 0; i < 4; i++) {
      cell = this.cells[idx];
      cell.user = user;
      cell.reset();
      idx++;
    }
  },
	killProcess: function(...params) {
    // delete in the user's procList and then in global's one
    // kill-process pid
    const [pid] = params;
    const proc = this.procs[pid];
    const user = proc.uid;

    log(`killProcess ${pid}`);
    proc.cell.reset();
    user.removeProc(proc);
    delete this.procs[pid];
    log(`[killProcess]`, user, this.procs);
  },
	live: function(...params) {
    log("live");
  },
  checkClient: function(...params) {
    log("checkClient");
  },
  cycleToDie: function(...params) {
      this.dispatch("cycleToDie", params[0]);
  },
  end: function(...params) {
    this.dispatch("status", "FIN");
  }
}
