const Cell = (function() {
  const cellDefaultBg = "grey";
  const cellDefaultBorder = "#000";

  function reset() {
    ctx = this.ctx;
    ctx.clearRect(...this.coords, ctx.scale, ctx.scale)
    this.border = cellDefaultBorder;
    if (this.user)
      this.user.setCell(this);
    else {
      const cell = new Cell(this.id, this.text.value);
      Object.assign(this, cell);
    }
    this.draw(ctx);
  }
  function drawCell(ctx) {
    const x = (this.id % ctx.idxMod) * ctx.scale;
    const y = Math.floor(this.id / ctx.idxMod) * ctx.scale;
    ctx.clearRect(x, y, ctx.scale, ctx.scale)
    if (ctx.scale >= 20) {
      ctx.font = `80% serif`;
      ctx.textBaseline = 'top';
      ctx.fillText(this.text.value, x + 1, y + 1);
    }
    ctx.fillStyle = this.bgColor;
    ctx.fillRect(x, y, ctx.scale, ctx.scale)
    ctx.strokeStyle = this.border;
    ctx.lineWidth = this.lineWidth;
    ctx.strokeRect(x, y, ctx.scale, ctx.scale)
    this.coords = [x, y];
    this.ctx = ctx;
  }
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
    this.draw = drawCell;
    this.reset = reset;
  }
})();

module.exports = {
  Cell,
  User: (function() {
    let cuid = 0;
    const userColor = [
      "#00ff69",
      "#eb5757",
      "#56ccf2",
      "#f2c94c"
    ];
    function addProc(proc) {
      this.procList.push(proc);
    }
    function removeProc(proc) {
      const i = this.procList.indexOf(proc);

      if (i >= 0)
        return this.procList.splice(i, 1);
    }
    function setCell(cell) {
      cell.bgColor = this.['info'].color;
      cell.lineWidth = 1.0;
      cell.user = this;
    }
    function loadUser(cells, ctx, position) {
      const proc = this.procList[0];
      let cell;

      // proc['info'].PC ??= position;
      this.position = position;
      for (let i = 0; i < this['info'].size; i++) {
          cell = cells[position]; //possibly cell's cleanup needed
          this.setCell(cell);
          cell.draw(ctx);
          position++;
      }
    }
    return function(name, desc, code, size) {
      this.id = cuid++;
      this.info = {
        name,
        desc,
        code,
        size,
        color: userColor[this.id]
      };
      this.procList = [];
      this.load = loadUser;
      this.setCell = setCell;
      this.removeProc = removeProc;
    }
  })(),

  Proc: (function() {
    const procColor = [
      "#9cffc5",
      "#ffd0d0",
      "#c8f2ff",
      "#fdeec1"
    ];
    function setCell() {
      this.cell.bgColor = this.['info'].color;
      this.cell.lineWidth = 2.5;
    }
    return function(uid, pid, cell) {
      this.uid = uid;
      this.id = pid;
      this.PC = cell.id;
      this.info = {
        carry: 0,
        color: procColor[
          (typeof uid === "number") ? uid : uid.id
        ],
        lives: 0
      };
      this.cell = cell;
      this.setCell = setCell;
      setCell.bind(this)();
    }
  })()
};