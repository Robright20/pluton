module.exports = {
  Cell: (function() {
    const cellDefaultBg = "grey";
    const cellDefaultBorder = "";

    return function Cell(id, text) {
      this.id = id;
      this.text = {
        value: text,
        fontFamily: "",
        color: "",
        size: 0
      };
      this.bgColor = cellDefaultBg;
      this.border = cellDefaultBorder;
    }
  })(),

  User: (function() {
    let cuid = 0;
    const userColor = [
      "#00ff69",
      "#eb5757",
      "#56ccf2",
      "#f2c94c"
    ];

    return function(name, desc, size) {
      this.id = cuid++;
      this.info = {
        name,
        desc,
        size,
        color: userColor[this.id]
      };
      this.procList = [];
    }
  })(),

  Proc: (function() {
    const procColor = [
      "#9cffc5",
      "#ffd0d0",
      "#c8f2ff",
      "#fdeec1"
    ];

    return function(uid, pid) {
      this.uid = uid;
      this.id = pid;
      this.PC = 0;
      this.info = {
        carry: 0,
        color: procColor[uid],
        lives: 0
      };
    }
  })()
};